/*!
	@file	DFERRACIImpl.h
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-09-01
*/

#pragma once

#include "DFERRACI.h"
#include "DFACIImpl.h"

//	CDFERRACIImpl
//******************************************************************************
class CDFERRACIImpl:public SDFACIImpl{
	//!	@name	session
	//@{
protected:
	void OnOpenSession(DFAPI_SESSION session){
		ACI_UpdateSession(session, DFERRACI, this);
	}

	static CDFERRACIImpl* ACI_CheckSession(DFAPI_SESSION session){
		return (CDFERRACIImpl*) SDFACIImpl::ACI_CheckSession(session, DFERRACI);
	}

	static BOOL GetProcAddress(LPCTSTR lpszProcName, LPVOID* lpProcAddress){
		DFAPI_PLUGIN_BEGIN_GPA()
			DFAPI_PLUGIN_GPA(DFERRACI_CLEARERROR_PROCNAME, ERRACI_ClearError)
			DFAPI_PLUGIN_GPA(DFERRACI_GETLASTERROR_PROCNAME, ERRACI_GetLastError)
			DFAPI_PLUGIN_GPA(DFERRACI_GETERRORMSG_PROCNAME, ERRACI_GetErrorMsg)
		DFAPI_PLUGIN_END_GPA()
	}
	//@}

	//!	@name	ERRACI
	//@{
	DFAPI_PLUGIN_STD_INTERFACE_ACI(CDFERRACIImpl, ERRACI_ClearError)
	DFAPI_PLUGIN_STD_INTERFACE_ACI(CDFERRACIImpl, ERRACI_GetLastError)
	DFAPI_PLUGIN_STD_INTERFACE_ACI(CDFERRACIImpl, ERRACI_GetErrorMsg)
	//@}
};
