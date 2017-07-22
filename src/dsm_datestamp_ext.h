// dsm_datestamp_ext.h : Declaration of the Cdsm_datestamp_ext

#ifndef __DSM_DATESTAMP_EXT_H_
#define __DSM_DATESTAMP_EXT_H_

#include "resource.h"
#include <shlobj.h>
#include <comdef.h>
#include <list>
#include <string>
using std::list;
using std::string;

void MakeTimeDateStr(char* dest, const char* source, const SYSTEMTIME* sys_time = 0);
bool RemoveTimeDateStr(char* dest, const char* source);

// Cdsm_datestamp_ext
class ATL_NO_VTABLE Cdsm_datestamp_ext :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<Cdsm_datestamp_ext, &CLSID_dsm_datestamp_ext>,
	public IDispatchImpl<Idsm_datestamp_ext, &IID_Idsm_datestamp_ext, &LIBID_DSM_DATESTAMPLib>,
	public IShellExtInit,
	public IContextMenu
{
public:
	Cdsm_datestamp_ext()
	{
		m_console_allocated = 0;
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_DSM_DATESTAMP_EXT)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(Cdsm_datestamp_ext)
		COM_INTERFACE_ENTRY(Idsm_datestamp_ext)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IShellExtInit)
		COM_INTERFACE_ENTRY(IContextMenu)
	END_COM_MAP()

	// Idsm_datestamp_ext
protected:
	list<string> m_filenames;
public:
	// IShellExtInit
	STDMETHOD(Initialize)(LPCITEMIDLIST, LPDATAOBJECT, HKEY);

	// IContextMenu
	STDMETHOD(GetCommandString)(UINT_PTR, UINT, UINT*, LPSTR, UINT);
	STDMETHOD(InvokeCommand)(LPCMINVOKECOMMANDINFO);
	STDMETHOD(QueryContextMenu)(HMENU, UINT, UINT, UINT, UINT);

	int m_console_allocated;
};

#endif //__DSM_DATESTAMP_EXT_H_
