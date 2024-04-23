/*!
	@file	DFENVACI.h
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-09-01
*/

#pragma once

#include "DFShellAPI.h"

//	DFENVACI
//******************************************************************************
#define	DFENVACI											1

//	DFENVACI_SETPROXYLANGUAGE
//******************************************************************************
#define	DFENVACI_SETPROXYLANGUAGE_PROCNAME					_T("DFENVACI.SetProxyLanguage")
struct DFENVACI_SETPROXYLANGUAGE_PARAM{
	DFAPI_TEXT128_TYPE				szLanguage;				//!< [in]: language
};

//	DFENVACI_SETAPPROOTPATH
//******************************************************************************
#define	DFENVACI_SETAPPROOTPATH_PROCNAME					_T("DFENVACI.SetAppRootPath")
struct DFENVACI_SETAPPROOTPATH_PARAM{
	DFAPI_TEXTPATH_TYPE				szAppRootPath;			//!< [in]: application root path
};

//	DFENVACI_SETPLUGINSSHAREDPATH
//******************************************************************************
#define	DFENVACI_SETPLUGINSSHAREDPATH_PROCNAME				_T("DFENVACI.SetPluginsSharedPath")
struct DFENVACI_SETPLUGINSSHAREDPATH_PARAM{
	DFAPI_TEXTPATH_TYPE				szPluginsSharedPath;	//!< [in]: plugins shared path
};

//	DFENVACI_SETTEXTVARIABLE
//******************************************************************************
#define	DFENVACI_SETTEXTVARIABLE_PROCNAME					_T("DFENVACI.SetTextVariable")
struct DFENVACI_SETTEXTVARIABLE_PARAM{
	int								nIndex;					//!< [in]: index of variable
	DFAPI_TEXT4096_TYPE				szValue;				//!< [in]: value of text variable
};

//	DFENVACI_GETTEXTVARIABLE
//******************************************************************************
#define	DFENVACI_GETTEXTVARIABLE_PROCNAME					_T("DFENVACI.GetTextVariable")
struct DFENVACI_GETTEXTVARIABLE_PARAM{
	int								nIndex;					//!< [in]: index of variable
	DFAPI_TEXT4096_TYPE				szValue;				//!< [out]: value of text variable
};

//	DFENVACI_SETDATAVARIABLE
//******************************************************************************
#define	DFENVACI_SETDATAVARIABLE_PROCNAME					_T("DFENVACI.SetDataVariable")
struct DFENVACI_SETDATAVARIABLE_PARAM{
	int								nIndex;					//!< [in]: index of variable
	DWORD64							dwValue;				//!< [in]: value of data variable
};

//	DFENVACI_GETDATAVARIABLE
//******************************************************************************
#define	DFENVACI_GETDATAVARIABLE_PROCNAME					_T("DFENVACI.GetDataVariable")
struct DFENVACI_GETDATAVARIABLE_PARAM{
	int								nIndex;					//!< [in]: index of variable
	DWORD64							dwValue;				//!< [out]: value of data variable
};

//	DFENVACI_SETHELPERWINDOWHANDLE
//******************************************************************************
#define DFENVACI_SETHELPERWINDOWHANDLE_PROCNAME				_T("DFENVACI.SetHelperWindowHandle")
struct DFENVACI_SETHELPERWINDOWHANDLE_PARAM{
	HWND							hWnd;					//!< [in]: helper window handle
};

//	DFENVACI_GETHELPERWINDOWHANDLE
//******************************************************************************
#define	DFENVACI_GETHELPERWINDOWHANDLE_PROCNAME				_T("DFENVACI.GetHelplerWindowHandle")
struct DFENVACI_GETHELPERWINDOWHANDLE_PARAM{
	HWND							hWnd;					//!< [out]: helper window handle
};

//	DFENVACI_SETDATA
//******************************************************************************
