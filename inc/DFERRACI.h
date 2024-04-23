/*!
	@file	DFERRACI.h
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-09-01
*/

#pragma once

#include "DFShellAPI.h"

//	DFERRACI
//******************************************************************************
#define	DFERRACI											2

//	DFERRACI_CLEARERROR
//******************************************************************************
#define	DFERRACI_CLEARERROR_PROCNAME						_T("DFERRACI.ClearError")
struct DFERRACI_CLEARERROR_PARAM{
};

//	DFERRACI_GETLASTERROR
//******************************************************************************
#define	DFERRACI_GETLASTERROR_PROCNAME						_T("DFERRACI.GetLastError")
struct DFERRACI_GETLASTERROR_PARAM{
	DWORD							dwErrCode;				//!< [out]: error code
};

//	DFERRACI_GETERRORMSG
//******************************************************************************
#define	DFERRACI_GETERRORMSG_PROCNAME						_T("DFERRACI.GetErrorMsg")
struct DFERRACI_GETERRORMSG_PARAM{
	DWORD							dwErrCode;				//!< [in]: error code
	DFAPI_TEXT1024_TYPE				szErrMsg;				//!< [out]: error message
};
