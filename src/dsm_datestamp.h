

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sat Jul 22 16:41:36 2017
 */
/* Compiler settings for dsm_datestamp.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __dsm_datestamp_h__
#define __dsm_datestamp_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __Idsm_datestamp_ext_FWD_DEFINED__
#define __Idsm_datestamp_ext_FWD_DEFINED__
typedef interface Idsm_datestamp_ext Idsm_datestamp_ext;

#endif 	/* __Idsm_datestamp_ext_FWD_DEFINED__ */


#ifndef __dsm_datestamp_ext_FWD_DEFINED__
#define __dsm_datestamp_ext_FWD_DEFINED__

#ifdef __cplusplus
typedef class dsm_datestamp_ext dsm_datestamp_ext;
#else
typedef struct dsm_datestamp_ext dsm_datestamp_ext;
#endif /* __cplusplus */

#endif 	/* __dsm_datestamp_ext_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __Idsm_datestamp_ext_INTERFACE_DEFINED__
#define __Idsm_datestamp_ext_INTERFACE_DEFINED__

/* interface Idsm_datestamp_ext */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_Idsm_datestamp_ext;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B187DDCC-1398-47CD-A83C-61CD030A670F")
    Idsm_datestamp_ext : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct Idsm_datestamp_extVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            Idsm_datestamp_ext * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            Idsm_datestamp_ext * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            Idsm_datestamp_ext * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            Idsm_datestamp_ext * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            Idsm_datestamp_ext * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            Idsm_datestamp_ext * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            Idsm_datestamp_ext * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } Idsm_datestamp_extVtbl;

    interface Idsm_datestamp_ext
    {
        CONST_VTBL struct Idsm_datestamp_extVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Idsm_datestamp_ext_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define Idsm_datestamp_ext_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define Idsm_datestamp_ext_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define Idsm_datestamp_ext_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define Idsm_datestamp_ext_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define Idsm_datestamp_ext_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define Idsm_datestamp_ext_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __Idsm_datestamp_ext_INTERFACE_DEFINED__ */



#ifndef __DSM_DATESTAMPLib_LIBRARY_DEFINED__
#define __DSM_DATESTAMPLib_LIBRARY_DEFINED__

/* library DSM_DATESTAMPLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_DSM_DATESTAMPLib;

EXTERN_C const CLSID CLSID_dsm_datestamp_ext;

#ifdef __cplusplus

class DECLSPEC_UUID("607361BA-AFA1-42E7-B0AD-04BB50E8DCB1")
dsm_datestamp_ext;
#endif
#endif /* __DSM_DATESTAMPLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


