
dsm_datestampps.dll: dlldata.obj dsm_datestamp_p.obj dsm_datestamp_i.obj
	link /dll /out:dsm_datestampps.dll /def:dsm_datestampps.def /entry:DllMain dlldata.obj dsm_datestamp_p.obj dsm_datestamp_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del dsm_datestampps.dll
	@del dsm_datestampps.lib
	@del dsm_datestampps.exp
	@del dlldata.obj
	@del dsm_datestamp_p.obj
	@del dsm_datestamp_i.obj
