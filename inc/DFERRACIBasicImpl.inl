/*!
	@file	DFERRACIBasicImpl.inl
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-09-01
*/

#pragma once

#include "DFERRACIBasicImpl.h"

//	CDFERRACIBasicImpl
//******************************************************************************
inline CDFERRACIBasicImpl::CDFERRACIBasicImpl()
{
	//initialize error engine
	m_dwLastErrCode = 0;
}

//	error engine
//------------------------------------------------------------------------------
inline void CDFERRACIBasicImpl::SetLastError(DWORD dwErrCode)
{
	m_dwLastErrCode = dwErrCode;
}

inline BOOL CDFERRACIBasicImpl::GetErrorMsg(LPCTSTR lpszLanguage, DWORD dwErrCode, CString& strMsg)
{
	strMsg.Format(_T("Error Code: %d"), dwErrCode);
	return TRUE;
}

//	ERRACI
//------------------------------------------------------------------------------
DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFERRACIBasicImpl, ERRACI_ClearError)
{
	DFERRACI_CLEARERROR_PARAM* p = (DFERRACI_CLEARERROR_PARAM*) param;

	//clear error
	m_dwLastErrCode = 0;
	
	//
	return TRUE;
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFERRACIBasicImpl, ERRACI_GetLastError)
{
	DFERRACI_GETLASTERROR_PARAM* p = (DFERRACI_GETLASTERROR_PARAM*) param;
	if (p == NULL) return FALSE;

	//get last error
	p->dwErrCode = m_dwLastErrCode;

	//
	return TRUE;
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFERRACIBasicImpl, ERRACI_GetErrorMsg)
{
	DFERRACI_GETERRORMSG_PARAM* p = (DFERRACI_GETERRORMSG_PARAM*) param;
	if (p == NULL) return FALSE;

	//get language
	DFAPI_TEXT128_TYPE szLanguage;
	if (!ACI_GetProxyLanguage(session, szLanguage)) return FALSE;

	//get error message
	CString strErrMsg;
	if (!GetErrorMsg(szLanguage, p->dwErrCode, strErrMsg)) return FALSE;
	p->szErrMsg = (LPCTSTR) strErrMsg;

	//
	return TRUE;
}
