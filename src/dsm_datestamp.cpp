/**************
*
* dsm_datestamp
*
* Windows shell extension to add a date/time stamp to filenames, before the extension.  For example, I
* might right-click on a file named:
*
* hello.txt
*
* ...and select dsm_datestamp, and the file would be renamed to:
*
* hello.05.04.13.12.38.11.txt
*
* ...if you ran it at 12.38.11pm on Apr 13 2005.
*
* If you run it on a file that already looks like it's been datestamped, it will update the datestamp.  It can operate on multiple
* files.
*
* Dan Morris
* dmorris@cs.stanford.edu
* http://dmorris.net
*
* Based on this shell extension tutorial by Michael Dunn:
*
* http://www.codeproject.com/shell/shellextguide1.asp
*
* Released under the granola bar license: if you find this code useful, please bring me a granola bar.

**************/

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "dsm_datestamp.h"
#include "dsm_datestamp_i.c"
#include "dsm_datestamp_ext.h"

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_dsm_datestamp_ext, Cdsm_datestamp_ext)
END_OBJECT_MAP()

// Main DLL entry point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		_Module.Init(ObjectMap, hInstance, &LIBID_DSM_DATESTAMPLib);
		DisableThreadLibraryCalls(hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
		_Module.Term();
	return TRUE;
}


// Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow(void)
{
	return (_Module.GetLockCount() == 0) ? S_OK : S_FALSE;
}


// Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return _Module.GetClassObject(rclsid, riid, ppv);
}


// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer(void)
{
	// Registers object, typelib and all interfaces in typelib
	return _Module.RegisterServer(TRUE);
}

// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void)
{
	return _Module.UnregisterServer(TRUE);
}


