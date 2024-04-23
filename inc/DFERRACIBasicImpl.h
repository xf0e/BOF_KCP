/*!
	@file	DFERRACIBasicImpl.h
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-09-01
*/

#pragma once

#include "DFERRACIImpl.h"

//	CDFERRACIBasicImpl
//******************************************************************************
class CDFERRACIBasicImpl:public CDFERRACIImpl{
protected:
	CDFERRACIBasicImpl();

	//!	@name	error engine
	//@{
protected:
	DWORD							m_dwLastErrCode;		//!< last error code
	void SetLastError(DWORD dwErrCode = 0);
	virtual BOOL GetErrorMsg(LPCTSTR lpszLanguage, DWORD dwErrCode, CString& strMsg);
	//@}

	//!	@name	ERRACI
	//@{
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(ERRACI_ClearError)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(ERRACI_GetLastError)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(ERRACI_GetErrorMsg)
	//@}
};

//******************************************************************************
#include "DFERRACIBasicImpl.inl"
