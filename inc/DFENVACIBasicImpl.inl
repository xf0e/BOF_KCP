/*!
	@file	DFENVACIBasicImpl.inl
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-09-01
*/

#pragma once

#include "DFENVACIBasicImpl.inl"

//	CDFENVACIBasicImpl
//******************************************************************************
inline CDFENVACIBasicImpl::CDFENVACIBasicImpl()
{
	//initialize text variables
	m_nTextVariableCount = 0;
	m_pTextVariables = NULL;
	m_pTextVariablesFlags = NULL;

	//initialize data variables
	m_nDataVariableCount = 0;
	m_pDataVariables = NULL;
	m_pDataVariablesFlags = NULL;

	//initialize helper window
	m_hHelperWindowHandle = NULL;
}

inline CDFENVACIBasicImpl::~CDFENVACIBasicImpl()
{
	//clean up text variables
	CleanupTextVariables();

	//clean up data variables
	CleanupDataVariables();
}

//	text variables
//------------------------------------------------------------------------------
inline void CDFENVACIBasicImpl::InitializeTextVariables(int nCount)
{
	//clean up
	CleanupTextVariables();

	//initialize
	if (nCount > 0){
		m_pTextVariables = new DFAPI_TEXT4096_TYPE[nCount];
		m_pTextVariablesFlags = new BYTE[nCount];
		if (m_pTextVariables && m_pTextVariablesFlags){
			for (int i=0;i<nCount;i++)
			{	::memset(&m_pTextVariables[i], 0, sizeof(DFAPI_TEXT4096_TYPE));
				m_pTextVariablesFlags[i] = 0;
			}
			m_nTextVariableCount = nCount;
		}
		else{
			CleanupTextVariables();
		}
	}
}

inline BOOL CDFENVACIBasicImpl::SetTextVariable(int nIndex, DFAPI_TEXT4096_TYPE& szValue)
{
	if (nIndex < 0 || nIndex >= m_nTextVariableCount) return FALSE;
	if (m_pTextVariables == NULL) return FALSE;
	m_pTextVariables[nIndex] = szValue;
	return TRUE;
}

inline BOOL CDFENVACIBasicImpl::SetTextVariable(int nIndex, LPCTSTR lpszValue)
{
	DFAPI_TEXT4096_TYPE v;
	if (!v.SetEx(lpszValue)) return FALSE;
	return SetTextVariable(nIndex, v);
}

inline BOOL CDFENVACIBasicImpl::GetTextVariable(int nIndex, DFAPI_TEXT4096_TYPE& szValue)
{
	if (nIndex < 0 || nIndex >= m_nTextVariableCount) return FALSE;
	if (m_pTextVariables == NULL) return FALSE;
	szValue = m_pTextVariables[nIndex];
	return TRUE;
}

inline BOOL CDFENVACIBasicImpl::GetTextVariable(int nIndex, CString& strValue)
{
	DFAPI_TEXT4096_TYPE v;
	if (!GetTextVariable(nIndex, v)) return FALSE;
	strValue = v;
	return TRUE;
}

inline BOOL CDFENVACIBasicImpl::SetTextVariableReadOnly(int nIndex, BOOL bReadOnly)
{
	if (nIndex < 0 || nIndex >= m_nTextVariableCount) return FALSE;
	if (m_pTextVariablesFlags == NULL) return FALSE;
	if (bReadOnly){
		m_pTextVariablesFlags[nIndex] |= flag_mask_readonly;
	}
	else{
		m_pTextVariablesFlags[nIndex] &= (~flag_mask_readonly);
	}
	return TRUE;
}

inline BOOL CDFENVACIBasicImpl::GetTextVariableReadOnly(int nIndex, BOOL& bReadOnly)
{
	if (nIndex < 0 || nIndex >= m_nTextVariableCount) return FALSE;
	if (m_pTextVariablesFlags == NULL) return FALSE;
	bReadOnly = ((m_pTextVariablesFlags[nIndex] & flag_mask_readonly) != 0);
	return TRUE;
}

inline void CDFENVACIBasicImpl::CleanupTextVariables()
{
	if (m_pTextVariables) delete [] m_pTextVariables;
	if (m_pTextVariablesFlags) delete [] m_pTextVariablesFlags;
	m_nTextVariableCount = 0;
	m_pTextVariables = NULL;
	m_pTextVariablesFlags = NULL;
}

//	data variables
//------------------------------------------------------------------------------
inline void CDFENVACIBasicImpl::InitializeDataVariables(int nCount)
{
	//clean up
	CleanupDataVariables();

	//initialize
	if (nCount > 0){
		m_pDataVariables = new DWORD64[nCount];
		m_pDataVariablesFlags = new BYTE[nCount];
		if (m_pDataVariables && m_pDataVariablesFlags){
			for (int i=0;i<nCount;i++)
			{
				m_pDataVariables[i] = 0;
				m_pDataVariablesFlags[i] = 0;
			}
			m_nDataVariableCount = nCount;
		}
		else{
			CleanupDataVariables();
		}
	}
}

inline BOOL CDFENVACIBasicImpl::SetDataVariable(int nIndex, DWORD64 dwValue)
{
	if (nIndex < 0 || nIndex >= m_nDataVariableCount) return FALSE;
	if (m_pDataVariables == NULL) return FALSE;
	m_pDataVariables[nIndex] = dwValue;
	return TRUE;
}

inline BOOL CDFENVACIBasicImpl::GetDataVariable(int nIndex, DWORD64& dwValue)
{
	if (nIndex < 0 || nIndex >= m_nDataVariableCount) return FALSE;
	if (m_pDataVariables == NULL) return FALSE;
	dwValue = m_pDataVariables[nIndex];
	return TRUE;
}

inline BOOL CDFENVACIBasicImpl::SetDataVariableReadOnly(int nIndex, BOOL bReadOnly)
{
	if (nIndex < 0 || nIndex >= m_nDataVariableCount) return FALSE;
	if (m_pDataVariablesFlags == NULL) return FALSE;
	if (bReadOnly){
		m_pDataVariablesFlags[nIndex] |= flag_mask_readonly;
	}
	else{
		m_pDataVariablesFlags[nIndex] &= (~flag_mask_readonly);
	}
	return TRUE;
}

inline BOOL CDFENVACIBasicImpl::GetDataVariableReadOnly(int nIndex, BOOL& bReadOnly)
{
	if (nIndex < 0 || nIndex >= m_nDataVariableCount) return FALSE;
	if (m_pDataVariablesFlags == NULL) return FALSE;
	bReadOnly = ((m_pDataVariablesFlags[nIndex] & flag_mask_readonly) != 0);
	return TRUE;
}

inline void CDFENVACIBasicImpl::CleanupDataVariables()
{
	if (m_pDataVariables) delete [] m_pDataVariables;
	if (m_pDataVariablesFlags) delete [] m_pDataVariablesFlags;
	m_nDataVariableCount = 0;
	m_pDataVariables = NULL;
	m_pDataVariablesFlags = NULL;
}

//	helper window handle
//------------------------------------------------------------------------------
inline void CDFENVACIBasicImpl::SetHelperWindowHandle(HWND hWnd)
{
	m_hHelperWindowHandle = hWnd;
}

inline  HWND CDFENVACIBasicImpl::GetHelperWindowHandle()
{
	return m_hHelperWindowHandle;
}

//	ENVACI
//------------------------------------------------------------------------------
DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFENVACIBasicImpl, ENVACI_SetProxyLanguage)
{
	DFENVACI_SETPROXYLANGUAGE_PARAM* p = (DFENVACI_SETPROXYLANGUAGE_PARAM*) param;
	if (p == NULL) return FALSE;

	//set proxy language
	DFSHELLAPI_PROXY_INFO* pProxyInfo = ACI_GetProxyInfo(session);
	if (pProxyInfo == NULL) return FALSE;
	pProxyInfo->m_Language = p->szLanguage;

	//
	return TRUE;
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFENVACIBasicImpl, ENVACI_SetAppRootPath)
{
	DFENVACI_SETAPPROOTPATH_PARAM* p = (DFENVACI_SETAPPROOTPATH_PARAM*) param;
	if (p == NULL) return FALSE;

	//set application root path
	DFSHELLAPI_PROXY_INFO* pProxyInfo = ACI_GetProxyInfo(session);
	if (pProxyInfo == NULL) return FALSE;
	pProxyInfo->m_AppRootPath = p->szAppRootPath;

	//
	return TRUE;
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFENVACIBasicImpl, ENVACI_SetPluginsSharedPath)
{
	DFENVACI_SETPLUGINSSHAREDPATH_PARAM* p = (DFENVACI_SETPLUGINSSHAREDPATH_PARAM*) param;
	if (p == NULL) return FALSE;

	//set plugins shared path
	DFSHELLAPI_PROXY_INFO* pProxyInfo = ACI_GetProxyInfo(session);
	if (pProxyInfo == NULL) return FALSE;
	pProxyInfo->m_PluginsSharedPath = p->szPluginsSharedPath;

	//
	return TRUE;
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFENVACIBasicImpl, ENVACI_SetTextVariable)
{
	DFENVACI_SETTEXTVARIABLE_PARAM* p = (DFENVACI_SETTEXTVARIABLE_PARAM*) param;
	if (p == NULL) return FALSE;

	//check read only
	BOOL bReadOnly = FALSE;
	if (!GetTextVariableReadOnly(p->nIndex, bReadOnly)) return FALSE;
	if (bReadOnly) return TRUE;

	//set text variable
	return SetTextVariable(p->nIndex, p->szValue);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFENVACIBasicImpl, ENVACI_GetTextVariable)
{
	DFENVACI_GETTEXTVARIABLE_PARAM* p = (DFENVACI_GETTEXTVARIABLE_PARAM*) param;
	if (p == NULL) return FALSE;

	//get text variable
	return GetTextVariable(p->nIndex, p->szValue);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFENVACIBasicImpl, ENVACI_SetDataVariable)
{
	DFENVACI_SETDATAVARIABLE_PARAM* p = (DFENVACI_SETDATAVARIABLE_PARAM*) param;
	if (p == NULL) return FALSE;

	//check read only
	BOOL bReadOnly = FALSE;
	if (!GetDataVariableReadOnly(p->nIndex, bReadOnly)) return FALSE;
	if (bReadOnly) return TRUE;

	//set data variable
	return SetDataVariable(p->nIndex, p->dwValue);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFENVACIBasicImpl, ENVACI_GetDataVariable)
{
	DFENVACI_GETDATAVARIABLE_PARAM* p = (DFENVACI_GETDATAVARIABLE_PARAM*) param;
	if (p == NULL) return FALSE;

	//get data variable
	return GetDataVariable(p->nIndex, p->dwValue);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFENVACIBasicImpl, ENVACI_SetHelperWindowHandle)
{
	DFENVACI_SETHELPERWINDOWHANDLE_PARAM* p = (DFENVACI_SETHELPERWINDOWHANDLE_PARAM*) param;
	if (p == NULL) return FALSE;

	//set helper window handle
	SetHelperWindowHandle(p->hWnd);

	//
	return TRUE;
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFENVACIBasicImpl, ENVACI_GetHelperWindowHandle)
{
	DFENVACI_GETHELPERWINDOWHANDLE_PARAM* p = (DFENVACI_GETHELPERWINDOWHANDLE_PARAM*) param;
	if (p == NULL) return FALSE;

	//set helper window handle
	p->hWnd = GetHelperWindowHandle();

	//
	return TRUE;
}
