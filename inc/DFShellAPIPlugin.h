/*!
	@file	DFShellAPIPlugin.h
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-09-01
*/

#pragma once

#include <afxwin.h>
#include "DFShellAPI.h"

//	TDFShellAPIPluginSession
//******************************************************************************
template <class PLUGINCLASS>
class TDFShellAPIPluginSession:public DFSHELLAPI_SESSION_INFO{
public:
	TDFShellAPIPluginSession();
	virtual ~TDFShellAPIPluginSession();

	//!	@name	session
	//@{
public:
	virtual void OnOpenSession();
	virtual void OnCloseSession();
	//@}
};

//	TDFShellAPIPlugin
//******************************************************************************
/*!
	Following static members should be defined in this class, derived classes or derived templates:

	//To be defined in TDFShellAPIPlugin.
	static DFAPI_VERSION_TYPE		g_ShellAPIVersion;		//shell API version

	//To be defined in TDFXXXAPIPlugin which is the template class of XXX API.
	static DFAPI_TYPEID_TYPE		g_Type;					//API type ID
	static DFAPI_VERSION_TYPE		g_APIVersion;			//API version

	//To be defined in CPlugin which is the implementation of one plugin.
	static DFAPI_VERSION_TYPE		g_Version;				//plugin version
	static DFAPI_BUILDVERSION_TYPE	g_BuildVersion;			//plugin build version
*/
template <class SESSIONCLASS, class PLUGINCLASS>
class TDFShellAPIPlugin{
	//!	@name	signature
	//@{
protected:
	static DWORD64 GetSignature();
	//@}

	//!	@name	plugin information
	//@{
public:
	static DFAPI_VERSION_TYPE		g_ShellAPIVersion;		//!< shell API version
protected:
	virtual void GetPluginInfoEx(LPCTSTR lpszLanguage, CString& strName, CString& strDesc, CString& strCopyright);
	//@}

	//!	@name	session
	//@{
protected:
	virtual BOOL OnPreOpenSession(DFAPI_SESSION session){return TRUE;}
	virtual void OnOpenSession(DFAPI_SESSION session){}
	virtual void OnCloseSession(DFAPI_SESSION session){}
	static DFSHELLAPI_SESSION_INFO* GetSession(DFAPI_SESSION session);
	static PLUGINCLASS* CheckSession(DFAPI_SESSION session, BOOL bAllowUnknownProxy = FALSE);
	//@}

	//!	@name	shell API
	//@{
public:
	static BOOL __GetInfo(DFSHELLAPI_PLUGIN_INFO* pPluginInfo, DWORD* pSize);
	static DFAPI_SESSION __OpenSession(DFSHELLAPI_PROXY_INFO* pProxyInfo);
	static BOOL __GetInfoEx(DFAPI_SESSION session, DFSHELLAPI_PLUGIN_INFOEX* pPluginInfoEx, DWORD* pSize);
	static BOOL __GetProcAddress(DFAPI_SESSION session, LPCTSTR lpszProcName, LPVOID* lpProcAddress);
	static BOOL __CloseSession(DFAPI_SESSION session);
public:
	virtual BOOL GetInfoEx(DFAPI_SESSION session, DFSHELLAPI_PLUGIN_INFOEX* pPlugin, DWORD* pSize);
	virtual BOOL GetProcAddress(DFAPI_SESSION session, LPCTSTR lpszProcName, LPVOID* lpProcAddress) = 0;
	virtual void CloseSession(DFAPI_SESSION session){}
	//@}
};

//******************************************************************************
#include "DFShellAPIPlugin.inl"