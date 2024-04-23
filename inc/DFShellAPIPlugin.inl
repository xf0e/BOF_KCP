/*!
	@file	DFShellAPIPlugin.inl
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-09-01
*/

#pragma once

#include "DFShellAPIPlugin.h"

//	TDFShellAPIPluginSession
//******************************************************************************
template <class PLUGINCLASS>
TDFShellAPIPluginSession<PLUGINCLASS>::TDFShellAPIPluginSession()
{
	m_dwSize = sizeof(TDFShellAPIPluginSession);
	m_Reserved[0] = new PLUGINCLASS;
}

template <class PLUGINCLASS>
TDFShellAPIPluginSession<PLUGINCLASS>::~TDFShellAPIPluginSession()
{
	if (m_Reserved[0]){
		delete (PLUGINCLASS*) m_Reserved[0];
		m_Reserved[0] = NULL;
	}
}

//	session
//------------------------------------------------------------------------------
template <class PLUGINCLASS>
void TDFShellAPIPluginSession<PLUGINCLASS>::OnOpenSession()
{
}

template <class PLUGINCLASS>
void TDFShellAPIPluginSession<PLUGINCLASS>::OnCloseSession()
{
}

//	TDFShellAPIPlugin
//******************************************************************************
//	signature
//------------------------------------------------------------------------------
template <class SESSIONCLASS, class PLUGINCLASS>
DWORD64 TDFShellAPIPlugin<SESSIONCLASS, PLUGINCLASS>::GetSignature()
{
	return (DWORD64) GetSignature;
}

//	plugin information
//------------------------------------------------------------------------------
template <class SESSIONCLASS, class PLUGINCLASS>
DFAPI_VERSION_TYPE TDFShellAPIPlugin<SESSIONCLASS, PLUGINCLASS>::g_ShellAPIVersion(DFSHELLAPI_VERSION);

template <class SESSIONCLASS, class PLUGINCLASS>
void TDFShellAPIPlugin<SESSIONCLASS, PLUGINCLASS>::GetPluginInfoEx(LPCTSTR lpszLanguage, CString& strName, CString& strDesc, CString& strCopyright)
{
	strName =_T("DFSHELLAPI Plugin");
	strDesc = _T("This is a plugin created with DFSHELLAPI.");
	strCopyright = _T("Copyright (C) 1998-2008 Eastman Kodak Company.  All rights reserved.");
}

//	session
//------------------------------------------------------------------------------
template <class SESSIONCLASS, class PLUGINCLASS>
DFSHELLAPI_SESSION_INFO* TDFShellAPIPlugin<SESSIONCLASS, PLUGINCLASS>::GetSession(DFAPI_SESSION session)
{
	SESSIONCLASS* pSession = (SESSIONCLASS*) session;
	if (pSession == NULL) return NULL;
	if (pSession->m_dwSize != sizeof(SESSIONCLASS)) return NULL;
	if (pSession->m_dwCreatorSignature != GetSignature()) return NULL;
	return pSession;
}

template <class SESSIONCLASS, class PLUGINCLASS>
PLUGINCLASS* TDFShellAPIPlugin<SESSIONCLASS, PLUGINCLASS>::CheckSession(DFAPI_SESSION session, BOOL bAllowUnknownProxy)
{
	SESSIONCLASS* pSession = (SESSIONCLASS*) GetSession(session);
	if (pSession == NULL) return NULL;

	//check proxy
	DFSHELLAPI_PROXY_INFO* pProxyInfo = pSession->m_pProxyInfo;
	if (pProxyInfo == NULL) return NULL;
	if (!pProxyInfo->m_Type.IsType(PLUGINCLASS::g_Type, bAllowUnknownProxy)) return NULL;

	//check plugin
	PLUGINCLASS* pPlugin = (PLUGINCLASS*) pSession->m_Reserved[0];
	if (pPlugin == NULL) return NULL;

	//
	return pPlugin;
}

//	shell API
//------------------------------------------------------------------------------
template <class SESSIONCLASS, class PLUGINCLASS>
BOOL TDFShellAPIPlugin<SESSIONCLASS, PLUGINCLASS>::__GetInfo(DFSHELLAPI_PLUGIN_INFO* pPluginInfo, DWORD* pSize)
{
	//check size
	if (pSize == NULL) return FALSE;

	//get plugin information size
	if (pPluginInfo == NULL){
		*pSize = sizeof(DFSHELLAPI_PLUGIN_INFO);
		return TRUE;
	}

	//get plugin information
	if (*pSize < sizeof(DFSHELLAPI_PLUGIN_INFO)) return FALSE;
	pPluginInfo->m_dwSize = sizeof(DFSHELLAPI_PLUGIN_INFO);
	pPluginInfo->m_ShellAPIVersion = PLUGINCLASS::g_ShellAPIVersion;
	pPluginInfo->m_Type = PLUGINCLASS::g_Type;
	pPluginInfo->m_APIVersion = PLUGINCLASS::g_APIVersion;
	pPluginInfo->m_Version = PLUGINCLASS::g_Version;
	pPluginInfo->m_BuildVersion = PLUGINCLASS::g_BuildVersion;
#ifdef	_DEBUG
	pPluginInfo->m_bIsDebug = TRUE;
#else
	pPluginInfo->m_bIsDebug = FALSE;
#endif	//_DEBUG

	//
	return TRUE;
}

template <class SESSIONCLASS, class PLUGINCLASS>
DFAPI_SESSION TDFShellAPIPlugin<SESSIONCLASS, PLUGINCLASS>::__OpenSession(DFSHELLAPI_PROXY_INFO* pProxyInfo)
{
	//check proxy
	if (pProxyInfo == NULL) return NULL;
	if (pProxyInfo->m_dwSize < sizeof(DFSHELLAPI_PROXY_INFO)) return NULL;
	if (!pProxyInfo->m_ShellAPIVersion.IsCompatible(PLUGINCLASS::g_ShellAPIVersion)) return NULL;
	if (!pProxyInfo->m_Type.IsType(PLUGINCLASS::g_Type, TRUE)) return NULL;

	//create session
	SESSIONCLASS* pSession = new SESSIONCLASS;
	if (pSession == NULL) return NULL;
	PLUGINCLASS* pPlugin = (PLUGINCLASS*) pSession->m_Reserved[0];
	if (pPlugin == NULL){
		delete pSession;
		return NULL;
	}
	pSession->m_dwCreatorSignature = GetSignature();
	if (!pSession->SetProxyInfo(pProxyInfo)){
		delete pSession;
		return NULL;
	}
	DFAPI_SESSION session = (DFAPI_SESSION) pSession;

	//open session event
	pSession->OnOpenSession();
	if (!pPlugin->OnPreOpenSession(session)){
		delete pSession;
		return NULL;
	}
	pPlugin->OnOpenSession(session);

	//
	return session;
}

template <class SESSIONCLASS, class PLUGINCLASS>
BOOL TDFShellAPIPlugin<SESSIONCLASS, PLUGINCLASS>::__GetInfoEx(DFAPI_SESSION session, DFSHELLAPI_PLUGIN_INFOEX* pPluginInfoEx, DWORD* pSize)
{
	PLUGINCLASS* pPlugin = CheckSession(session, TRUE);
	if (pPlugin == NULL) return FALSE;
	return pPlugin->GetInfoEx(session, pPluginInfoEx, pSize);
}

template <class SESSIONCLASS, class PLUGINCLASS>
BOOL TDFShellAPIPlugin<SESSIONCLASS, PLUGINCLASS>::__GetProcAddress(DFAPI_SESSION session, LPCTSTR lpszProcName, LPVOID* lpProcAddress)
{
	PLUGINCLASS* pPlugin = CheckSession(session, TRUE);
	if (pPlugin == NULL) return FALSE;
	return pPlugin->GetProcAddress(session, lpszProcName, lpProcAddress);
}

template <class SESSIONCLASS, class PLUGINCLASS>
BOOL TDFShellAPIPlugin<SESSIONCLASS, PLUGINCLASS>::__CloseSession(DFAPI_SESSION session)
{
	SESSIONCLASS* pSession = (SESSIONCLASS*) session;

	//close session
	PLUGINCLASS* pPlugin = CheckSession(session, TRUE);
	if (pPlugin == NULL) return FALSE;
	ASSERT(pSession);
	pPlugin->CloseSession(session);

	//close session event
	pPlugin->OnCloseSession(session);
	pSession->OnCloseSession();

	//delete session
	delete pSession;

	//
	return TRUE;
}

template <class SESSIONCLASS, class PLUGINCLASS>
BOOL TDFShellAPIPlugin<SESSIONCLASS, PLUGINCLASS>::GetInfoEx(DFAPI_SESSION session, DFSHELLAPI_PLUGIN_INFOEX* pPluginInfoEx, DWORD* pSize)
{
	SESSIONCLASS* pSession = (SESSIONCLASS*) session;
	ASSERT(pSession);

	//check size
	if (pSize == NULL) return FALSE;

	//get plugin extended information size
	if (pPluginInfoEx == NULL){
		*pSize = sizeof(DFSHELLAPI_PLUGIN_INFOEX);
		return TRUE;
	}

	//get plugin information
	if (*pSize < sizeof(DFSHELLAPI_PLUGIN_INFOEX)) return FALSE;
	pPluginInfoEx->m_dwSize = sizeof(DFSHELLAPI_PLUGIN_INFOEX);
	pPluginInfoEx->m_ShellAPIVersion = PLUGINCLASS::g_ShellAPIVersion;
	pPluginInfoEx->m_Type = PLUGINCLASS::g_Type;
	pPluginInfoEx->m_APIVersion = PLUGINCLASS::g_APIVersion;
	pPluginInfoEx->m_Version = PLUGINCLASS::g_Version;
	pPluginInfoEx->m_BuildVersion = PLUGINCLASS::g_BuildVersion;

	//get plugin extended information
	CString strLanguage;
	if (pSession->m_pProxyInfo == NULL) return FALSE;
	strLanguage = pSession->m_pProxyInfo->m_Language;
	CString strName, strDesc, strCopyright;
	GetPluginInfoEx(strLanguage, strName, strDesc, strCopyright);
	pPluginInfoEx->m_Name = (LPCTSTR) strName;
	pPluginInfoEx->m_Description = (LPCTSTR) strDesc;
	pPluginInfoEx->m_Copyright = (LPCTSTR) strCopyright;

	//
	return TRUE;
}

