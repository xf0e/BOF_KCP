/*!
	@file	DFACIImpl.inl
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-09-01
*/

#pragma once

#include "DFACIImpl.h"

//	SDFACIImpl
//******************************************************************************

//	session
//------------------------------------------------------------------------------
inline DFSHELLAPI_SESSION_INFO* SDFACIImpl::ACI_GetSession(DFAPI_SESSION session)
{
	DFSHELLAPI_SESSION_INFO* pSession = (DFSHELLAPI_SESSION_INFO*) session;
	if (pSession == NULL) return NULL;
	if (pSession->m_dwSize < sizeof(DFSHELLAPI_SESSION_INFO)) return NULL;
	return pSession;
}

inline void SDFACIImpl::ACI_UpdateSession(DFAPI_SESSION session, int nACIType, LPVOID pACI)
{
	DFSHELLAPI_SESSION_INFO* pSession = ACI_GetSession(session);
	if (pSession == NULL) return;
	if (nACIType < 1 || nACIType >= 64) return;
	pSession->m_Reserved[nACIType] = pACI;
}

inline LPVOID SDFACIImpl::ACI_CheckSession(DFAPI_SESSION session, int nACIType)
{
	DFSHELLAPI_SESSION_INFO* pSession = ACI_GetSession(session);
	if (pSession == NULL) return NULL;
	if (nACIType < 0 || nACIType >= 64) return NULL;
	return pSession->m_Reserved[nACIType];
}

//	proxy environment
//------------------------------------------------------------------------------
inline DFSHELLAPI_PROXY_INFO* SDFACIImpl::ACI_GetProxyInfo(DFAPI_SESSION session)
{
	DFSHELLAPI_SESSION_INFO* pSession = ACI_GetSession(session);
	if (pSession == NULL) return NULL;
	return pSession->m_pProxyInfo;
}

inline BOOL SDFACIImpl::ACI_GetProxyLanguage(DFAPI_SESSION session, DFAPI_TEXT128_TYPE& szLanguage)
{
	DFSHELLAPI_PROXY_INFO* pProxyInfo = ACI_GetProxyInfo(session);
	if (pProxyInfo == NULL) return FALSE;
	szLanguage = pProxyInfo->m_Language;
	return TRUE;
}

inline BOOL SDFACIImpl::ACI_GetAppRootPath(DFAPI_SESSION session, DFAPI_TEXTPATH_TYPE& szPath)
{
	DFSHELLAPI_PROXY_INFO* pProxyInfo = ACI_GetProxyInfo(session);
	if (pProxyInfo == NULL) return FALSE;
	szPath = pProxyInfo->m_AppRootPath;
	return TRUE;
}

inline BOOL SDFACIImpl::ACI_GetPluginsSharedPath(DFAPI_SESSION session, DFAPI_TEXTPATH_TYPE& szPath)
{
	DFSHELLAPI_PROXY_INFO* pProxyInfo = ACI_GetProxyInfo(session);
	if (pProxyInfo == NULL) return FALSE;
	szPath = pProxyInfo->m_PluginsSharedPath;
	return TRUE;
}

inline BOOL SDFACIImpl::ACI_GetReservedData(DFAPI_SESSION session, int nIndex, DWORD& dwData)
{
	DFSHELLAPI_PROXY_INFO* pProxyInfo = ACI_GetProxyInfo(session);
	if (pProxyInfo == NULL) return FALSE;
	int nCount = sizeof(pProxyInfo->m_dwReserved)/sizeof(DWORD);
	if (nIndex > nCount-1) return FALSE;
	
	dwData = pProxyInfo->m_dwReserved[nIndex];
	return TRUE;
}
