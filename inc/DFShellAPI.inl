/*!
	@file	DFShellAPI.inl
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-09-01
*/

#pragma once

#include "DFShellAPI.h"

//	DFSHELLAPI_PLUGIN_INFO
//******************************************************************************
inline DFSHELLAPI_PLUGIN_INFO::DFSHELLAPI_PLUGIN_INFO()
{
	m_dwSize = sizeof(DFSHELLAPI_PLUGIN_INFO);
	m_ShellAPIVersion = DFSHELLAPI_VERSION;
	m_bIsDebug = FALSE;
}

//	DFSHELLAPI_PLUGIN_INFOEX
//******************************************************************************
inline DFSHELLAPI_PLUGIN_INFOEX::DFSHELLAPI_PLUGIN_INFOEX()
{
	m_dwSize = sizeof(DFSHELLAPI_PLUGIN_INFOEX);
}

//	DFSHELLAPI_PROXY_INFO
//******************************************************************************
inline DFSHELLAPI_PROXY_INFO::DFSHELLAPI_PROXY_INFO()
{
	m_dwSize = sizeof(DFSHELLAPI_PROXY_INFO);
	m_ShellAPIVersion = DFSHELLAPI_VERSION;
}

//	DFSHELLAPI_SESSION_INFO
//******************************************************************************
inline DFSHELLAPI_SESSION_INFO::DFSHELLAPI_SESSION_INFO()
{
	m_dwSize = sizeof(DFSHELLAPI_SESSION_INFO);
	m_pProxyInfo = NULL;
	m_dwCreatorSignature = 0;
	memset(m_Reserved, 0, sizeof(LPVOID) * 64);
}

inline DFSHELLAPI_SESSION_INFO::~DFSHELLAPI_SESSION_INFO()
{
	ResetProxyInfo();
}

//	methods
//------------------------------------------------------------------------------
inline void DFSHELLAPI_SESSION_INFO::ResetProxyInfo()
{
	if (m_pProxyInfo == NULL) return;
	delete [] ((LPBYTE) m_pProxyInfo);
	m_pProxyInfo = NULL;
}

inline BOOL DFSHELLAPI_SESSION_INFO::SetProxyInfo(DFSHELLAPI_PROXY_INFO* pProxyInfo)
{
	//reset
	ResetProxyInfo();

	//check size
	if (pProxyInfo == NULL) return TRUE;
	DWORD dwSize = pProxyInfo->m_dwSize;
	if (dwSize < sizeof(DFSHELLAPI_PROXY_INFO)) return FALSE;

	//copy proxy information
	m_pProxyInfo = (DFSHELLAPI_PROXY_INFO*) new BYTE[dwSize];
	if (m_pProxyInfo == NULL) return FALSE;
	memcpy(m_pProxyInfo, pProxyInfo, dwSize);
	
	//
	return TRUE;
}
