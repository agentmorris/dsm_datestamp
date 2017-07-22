/**************

----------------------------------
Dan Morris
dmorris@cs.stanford.edu
http://cs.stanford.edu/~dmorris
----------------------------------

Built from the shell extension tutorial by Michael Dunn:

http://www.codeproject.com/shell/shellextguide1.asp

Released under the dmorris license:

You can do anything you want with this file as long as my name stays
somehwere on top of it and I'm credited where it's appropriate.  I'd
also really like it if you sent me a granola bar.

**************/

#include "winuser.h"
#include "stdafx.h"
#include "Dsm_datestamp.h"
#include "dsm_datestamp_ext.h"
#include <conio.h>
#include <atlconv.h>


// Called when the initial right-click event happens to open the context menu
HRESULT Cdsm_datestamp_ext::Initialize(LPCITEMIDLIST pidlFolder, LPDATAOBJECT pDataObj, HKEY hProgID) 
{

#ifdef _DEBUG
	// Allocate a console in debug mode only
	// if (m_console_allocated == 0) AllocConsole();
#endif

	FORMATETC fmt = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	STGMEDIUM stg = { TYMED_HGLOBAL };
	HDROP     hDrop;

	// Look for CF_HDROP data in the data object
	if (FAILED(pDataObj->GetData(&fmt, &stg))) 
	{
		return E_INVALIDARG;
	}

	// Get a pointer to the actual data
	hDrop = (HDROP)GlobalLock(stg.hGlobal);

	// Make sure it worked
	if (NULL == hDrop) 
	{
		return E_INVALIDARG;
	}


	// Sanity check : make sure there is at least one filename
	UINT uNumFiles = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);

	if (0 == uNumFiles) 
	{
		GlobalUnlock(stg.hGlobal);
		ReleaseStgMedium(&stg);
		return E_INVALIDARG;
	}

	HRESULT hr = S_OK;

	// For each file we're supposed to rename...
	for (unsigned int curfile = 0; curfile < uNumFiles; curfile++) 
	{

		char filename[_MAX_PATH];

		// Get the name of the first file and store it in our member variable m_szFile
		if (0 == DragQueryFile(hDrop, curfile, filename, MAX_PATH)) {
			hr = E_INVALIDARG;
		}

		// This copies the filename, not the pointer
		m_filenames.push_back(filename);

	} // ...for each filename

	GlobalUnlock(stg.hGlobal);
	ReleaseStgMedium(&stg);

	return hr;

} // HRESULT Cdsm_datestamp_ext::Initialize(LPCITEMIDLIST pidlFolder, LPDATAOBJECT pDataObj, HKEY hProgID) 


// Called when a context menu is opening for a right-click event; this is where we insert an
// item into the context menu.
HRESULT Cdsm_datestamp_ext::QueryContextMenu(HMENU hmenu, UINT  uMenuIndex, UINT  uidFirstCmd, UINT  uidLastCmd, UINT  uFlags) 
{

	// If the flags include CMF_DEFAULTONLY then we shouldn't do anything.
	if (uFlags & CMF_DEFAULTONLY) {
		return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, 0);
	}

	InsertMenu(hmenu, uMenuIndex, MF_BYPOSITION, uidFirstCmd, _T("dsm_datestamp"));

	return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, 1);
}


// Called when Windows wants a help/info string about our shell extension
HRESULT Cdsm_datestamp_ext::GetCommandString(UINT_PTR  idCmd, UINT  uFlags, UINT* pwReserved, LPSTR pszName, UINT  cchMax) 
{

	USES_CONVERSION;

	// Check idCmd, it must be 0 since we have only one menu item.
	if (0 != idCmd) return E_INVALIDARG;

	// If Explorer is asking for a help string, copy our string into the
	// supplied buffer.
	if (uFlags & GCS_HELPTEXT) {

		LPCTSTR szText = _T("Rename bob.txt to bob.04.02.05.2133.txt");

		if (uFlags & GCS_UNICODE) {
			// We need to cast pszName to a Unicode string, and then use the
			// Unicode string copy API.
			lstrcpynW((LPWSTR)pszName, T2CW(szText), cchMax);
		}

		else {
			// Use the ANSI string copy API to return the help string.
			lstrcpynA(pszName, T2CA(szText), cchMax);
		}

		return S_OK;
	}

	return E_INVALIDARG;

} // HRESULT Cdsm_datestamp_ext::GetCommandString(...) 


// Called when our menu item is selected and it's time to rename files
HRESULT Cdsm_datestamp_ext::InvokeCommand(LPCMINVOKECOMMANDINFO pCmdInfo) 
{

	// If lpVerb really points to a string, ignore this function call and bail out.
	if (0 != HIWORD(pCmdInfo->lpVerb)) return E_INVALIDARG;

	// Get the command index - the only valid one is 0.
	switch (LOWORD(pCmdInfo->lpVerb))
	{

	case 0:

		{

		std::list<string>::iterator iter = m_filenames.begin();

		for (; iter != m_filenames.end(); iter++) {

			char undatestampedFilename[_MAX_PATH];
			char dest[_MAX_PATH];
			const char* name = (*iter).c_str();

			// If this is already a datestamped filename, remove the datestamp
			bool result = RemoveTimeDateStr(undatestampedFilename, name);
			MakeTimeDateStr(dest, undatestampedFilename);
			MoveFile(name, dest);
		}

		// Force a refresh by synthesizing ctrl-f5
		INPUT i;
		i.type = INPUT_KEYBOARD;
		i.ki.dwFlags = 0;

		// Key down events
		i.ki.wVk = VK_CONTROL;
		SendInput(1, &i, sizeof(INPUT));
		i.ki.wVk = VK_F5;
		SendInput(1, &i, sizeof(INPUT));

		i.ki.dwFlags = KEYEVENTF_KEYUP;

		// Key up events
		i.ki.wVk = VK_F5;
		SendInput(1, &i, sizeof(INPUT));
		i.ki.wVk = VK_CONTROL;
		SendInput(1, &i, sizeof(INPUT));

		break;

		}

	default:

		return E_INVALIDARG;
		break;

	} // switch (LOWORD(pCmdInfo->lpVerb)) 

	m_filenames.clear();

	return S_OK;

} // HRESULT Cdsm_datestamp_ext::InvokeCommand(LPCMINVOKECOMMANDINFO pCmdInfo) 


// Removes an existing time/date string from the string in [source], if
// and only if it's the last thing before the extension.  If there's no extension
// or no time/date string, just returns the original string.
bool RemoveTimeDateStr(char* dest, const char* source)
{
	// We always copy source to dest; we'll blow away the datestamp in 'dest' later
	// if we find it
	strcpy(dest, source);

	// Find the beginning of the extension in the source string.  The
	// start of the extension is defined to be the character following the
	// last period in the source string.
	char* last_period = strrchr((char*)source, '.');

	// If there was no extension, just copy the output
	if (last_period == 0)  return false;

	// At some point, make a second pass through this function to handle a datestamp with
	// no extension, where we'd start the search like this...
	// if (last_period == 0) last_period = (char*)source + strlen(source);

	char* curChar = last_period - 1;
	bool foundDatestamp = true;
	int index = 0;

	//                             s     s     .      m     m     .      h     h     .      D     D     .      M     M     .      Y     Y
	bool datestampHasNumeric[] = { true, true, false, true, true, false, true, true, false, true, true, false, true, true, false, true, true };
	int nCharsInDatestamp = sizeof(datestampHasNumeric) / sizeof(datestampHasNumeric[0]);

	while (curChar > source)
	{
		if (datestampHasNumeric[index])
		{
			if (*curChar < '0' || *curChar > '9')
			{
				foundDatestamp = false;
				break;
			}
		}
		else
		{
			if (*curChar != '.')
			{
				foundDatestamp = false;
				break;
			}
		}

		index++;
		curChar--;

		// If we've read an entire datestamp
		if (index == nCharsInDatestamp) break;

	} // while there are still characters to process

	// If we got all the way to the beginning of the string...
	if (curChar == source) foundDatestamp = false;

	if (!foundDatestamp) return false;
	
	int finalOffset = (int)(curChar - source);
	char* datestamp = dest + finalOffset;
	strcpy(datestamp, last_period);
	return true;

} // bool RemoveTimeDateStr(char* dest, const char* source)


/*
   Appends the current date and time to the string "source",
   placing it between the filename and the extension if an
   extension exists.  Places the resulting string in "dest".

   In other words, it turns :

   bob.txt

   ...into...

   bob.02.12.28.14.55.44.txt

   (2:55.44 pm, Dec 28 2002)
*/
void MakeTimeDateStr(char* dest, const char* source, const SYSTEMTIME* sys_time) 
{

	SYSTEMTIME local_sys_time;
	if (sys_time == 0) {
		GetLocalTime(&local_sys_time);
		sys_time = &local_sys_time;
	}

	// Make the string for the time and date alone
	char timeDateStr[_MAX_PATH];

	sprintf(timeDateStr, "%02d.%02d.%02d.%02d.%02d.%02d",
		sys_time->wYear % 100, sys_time->wMonth, sys_time->wDay,
		sys_time->wHour, sys_time->wMinute, sys_time->wSecond);

	char tmp[_MAX_PATH];

	strcpy(tmp, source);

	// Find the beginning of the extension in the source string.  The
	// start of the extension is defined to be the character following the
	// last period in the source string.
	char* last_period = strrchr(tmp, '.');

	// If there was no extension, just concatenate the source and time/date strings
	if (last_period == 0) 
	{
		sprintf(dest, "%s.%s", tmp, timeDateStr);
	}

	// Otherwise stick the time/date string between the main source string and its extension
	else 
	{
		*last_period = 0;
		sprintf(dest, "%s.%s.%s", tmp, timeDateStr, (last_period + 1));
	}

} // MakeTimeDateStr
