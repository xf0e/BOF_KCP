/*!
	@file	DFAPIPluginHelper.h
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-09-01
*/

#pragma once

//	DFAPI_IMPLEMENT_PLUGIN_DLLMAIN
//******************************************************************************
#define	DFAPI_IMPLEMENT_PLUGIN_DLLMAIN()										\
static AFX_EXTENSION_MODULE __s_extmodule__ = {NULL, NULL};						\
HINSTANCE __g_instance__ = NULL;												\
extern "C" int APIENTRY DllMain(HINSTANCE hInstance,							\
								DWORD dwReason, LPVOID lpReserved)				\
{																				\
	switch (dwReason){															\
		case DLL_PROCESS_ATTACH:												\
			if (!AfxInitExtensionModule(__s_extmodule__, hInstance)) return 0;	\
			new CDynLinkLibrary(__s_extmodule__);								\
			__g_instance__ = hInstance;											\
			break;																\
		case DLL_PROCESS_DETACH:												\
			AfxTermExtensionModule(__s_extmodule__);							\
			__g_instance__ = NULL;												\
			break;																\
	}																			\
	return 1;																	\
}

//	DFAPI_IMPLEMENT_PLUGIN_ENTRYPOINTS
//******************************************************************************
#define	DFAPI_IMPLEMENT_PLUGIN_ENTRYPOINTS(classname)							\
extern "C" __declspec(dllexport)												\
BOOL DFSHELLAPI_GETINFO(DFSHELLAPI_PLUGIN_INFO* pPluginInfo, DWORD* pSize)		\
{																				\
	return classname::__GetInfo(pPluginInfo, pSize);							\
}																				\
extern "C" __declspec(dllexport)												\
DFAPI_SESSION DFSHELLAPI_OPENSESSION(DFSHELLAPI_PROXY_INFO* pProxyInfo)			\
{																				\
	return classname::__OpenSession(pProxyInfo);								\
}																				\
extern "C" __declspec(dllexport)												\
BOOL DFSHELLAPI_GETINFOEX(DFAPI_SESSION session, DFSHELLAPI_PLUGIN_INFOEX* pPluginInfoEx, DWORD* pSize)	\
{																				\
	return classname::__GetInfoEx(session, pPluginInfoEx, pSize);				\
}																				\
extern "C" __declspec(dllexport)												\
BOOL DFSHELLAPI_GETPROCADDRESS(DFAPI_SESSION session, LPCTSTR lpszProcName, LPVOID* lpProcAddress)		\
{																				\
	return classname::__GetProcAddress(session, lpszProcName, lpProcAddress);	\
}																				\
extern "C" __declspec(dllexport)												\
BOOL DFSHELLAPI_CLOSESESSION(DFAPI_SESSION session)								\
{																				\
	return classname::__CloseSession(session);									\
}

//	DFAPI_PLUGIN_STD_INTERFACE
//******************************************************************************
#define	DFAPI_PLUGIN_STD_INTERFACE(classname, procname)							\
public:																			\
	static BOOL __##procname(DFAPI_SESSION session, LPVOID param){				\
		classname* pThis = (classname*) CheckSession(session);					\
		if (pThis == NULL) return FALSE;										\
		return pThis->procname(session, param);									\
	}																			\
protected:																		\
	virtual BOOL procname(DFAPI_SESSION session, LPVOID param) = 0;

#define	DFAPI_PLUGIN_INTERFACE(classname, procname)						    	\
public:																			\
	static BOOL __##procname(DFAPI_SESSION session, LPVOID param){				\
		classname* pThis = (classname*) CheckSession(session);					\
		if (pThis == NULL) return FALSE;										\
		return pThis->procname(session, param);									\
	}																			\
protected:																		\
	virtual BOOL procname(DFAPI_SESSION session, LPVOID param);

#define	DFAPI_PLUGIN_STD_INTERFACE_ACI(classname, procname)						\
public:																			\
	static BOOL __##procname(DFAPI_SESSION session, LPVOID param){				\
		classname* pThis = (classname*) ACI_CheckSession(session);				\
		if (pThis == NULL) return FALSE;										\
		return pThis->procname(session, param);									\
	}																			\
protected:																		\
	virtual BOOL procname(DFAPI_SESSION session, LPVOID param) = 0;

#define DFAPI_PLUGIN_DECLARE_STD_INTERFACE(procname)							\
public:																			\
	virtual BOOL procname(DFAPI_SESSION session, LPVOID param);

#define DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(classname, procname)		\
BOOL inline classname::procname(DFAPI_SESSION session, LPVOID param)

#define	DFAPI_PLUGIN_IMPLEMENT_STD_INTERFACE(classname, procname)				\
BOOL classname::procname(DFAPI_SESSION session, LPVOID param)

//	DFAPI_PLUGIN_GPA
//******************************************************************************
#define	DFAPI_PLUGIN_BEGIN_GPA()												\
	if (lpszProcName == NULL || lpProcAddress == NULL) return FALSE;

#define	DFAPI_PLUGIN_GPA(name, procname)										\
	if (lstrcmpi(lpszProcName, name) == 0){										\
		*lpProcAddress = __##procname;											\
		return TRUE;															\
	}

#define	DFAPI_PLUGIN_END_GPA()													\
	return FALSE;
