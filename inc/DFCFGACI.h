/*!
	@file	DFCFGACI.h
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-09-01
*/

#pragma once

#include "DFShellAPI.h"

//	DFCFGACI
//******************************************************************************
#define	DFCFGACI											3

//	DFCFGACI_GETDEFAULTCONFIG
//******************************************************************************
#define	DFCFGACI_GETDEFAULTCONFIG_PROCNAME					_T("DFCFGACI.GetDefaultConfig")
struct DFCFGACI_GETDEFAULTCONFIG_PARAM{
	DFAPI_DATA_TYPE					config;					//!< [out]: config data
};

//	DFCFGACI_VALIDATECONFIG
//******************************************************************************
#define	DFCFGACI_VALIDATECONFIG_PROCNAME					_T("DFCFGACI.ValidateConfig")
struct DFCFGACI_VALIDATECONFIG_PARAM{
	DFAPI_DATA_TYPE					config;					//!< [in]: config data
};

//	DFCFGACI_SAVECONFIG
//******************************************************************************
#define	DFCFGACI_SAVECONFIG_PROCNAME						_T("DFCFGACI.SaveConfig")
struct DFCFGACI_SAVECONFIG_PARAM{
	DFAPI_TEXTPATH_TYPE				szFilePath;				//!< [in]: file path
	DFAPI_DATA_TYPE					config;					//!< [in]: config data
};

//	DFCFGACI_LOADCONFIG
//******************************************************************************
#define	DFCFGACI_LOADCONFIG_PROCNAME						_T("DFCFGACI.LoadConfig")
struct DFCFGACI_LOADCONFIG_PARAM{
	DFAPI_TEXTPATH_TYPE				szFilePath;				//!< [in]: file path
	DFAPI_DATA_TYPE					config;					//!< [out]: config data
};

//	DFCFGACI_SETCURRENTCONFIG
//******************************************************************************
#define	DFCFGACI_SETCURRENTCONFIG_PROCNAME					_T("DFCFGACI.SetCurrentConfig")
struct DFCFGACI_SETCURRENTCONFIG_PARAM{
	DFAPI_DATA_TYPE					config;					//!< [in]: config data
};

//	DFCFGACI_GETCURRENTCONFIG
//******************************************************************************
#define	DFCFGACI_GETCURRENTCONFIG_PROCNAME					_T("DFCFGACI.GetCurrentConfig")
struct DFCFGACI_GETCURRENTCONFIG_PARAM{
	DFAPI_DATA_TYPE					config;					//!< [out]: config data
};

//	DFCFGACI_VALIDATECURRENTCONFIG
//******************************************************************************
#define	DFCFGACI_VALIDATECURRENTCONFIG_PROCNAME				_T("DFCFGACI.ValidateCurrentConfig")
struct DFCFGACI_VALIDATECURRENTCONFIG_PARAM{
};

//	DFCFGACI_SAVECURRENTCONFIG
//******************************************************************************
#define	DFCFGACI_SAVECURRENTCONFIG_PROCNAME					_T("DFCFGACI.SaveCurrentConfig")
struct DFCFGACI_SAVECURRENTCONFIG_PARAM{
	DFAPI_TEXTPATH_TYPE				szFilePath;				//!< [in]: file path
};

//	DFCFGACI_LOADCURRENTCONFIG
//******************************************************************************
#define	DFCFGACI_LOADCURRENTCONFIG_PROCNAME					_T("DFCFGACI.LoadCurrentConfig")
struct DFCFGACI_LOADCURRENTCONFIG_PARAM{
	DFAPI_TEXTPATH_TYPE				szFilePath;				//!< [in]: file path
};

//	DFCFGACI_GETSUPPORTEDUIMODE
//******************************************************************************
#define	DFCFGACI_GETSUPPORTEDUIMODE_PROCNAME				_T("DFCFGACI.GetSupportedUIMode")
struct DFCFGACI_GETSUPPORTEDUIMODE_PARAM{
	BOOL							bSupportUI;				//!< [out]: standard UI mode
	BOOL							bSupportModalUI;		//!< [out]: modal UI mode
};

//	DFCFGACI_GETUISIZE
//******************************************************************************
#define	DFCFGACI_GETUISIZE_PROCNAME							_T("DFCFGACI.GetUISize")
struct DFCFGACI_GETUISIZE_PARAM{
	__int32							nWidth;					//!< [out]: standard UI width, -1 will be auto
	__int32							nHeight;				//!< [out]: standard UI height, -1 will be auto
};

//	DFCFGACI_BEGINUI
//******************************************************************************
#define	DFCFGACI_BEGINUI_PROCNAME							_T("DFCFGACI.BeginUI")
struct DFCFGACI_BEGINUI_PARAM{
	DFAPI_DATA_TYPE					config;					//!< [in]: config data
	HWND							hParentWnd;				//!< [in]: parent window handle
};

//	DFCFGACI_MOVEUI
//******************************************************************************
#define	DFCFGACI_MOVEUI_PROCNAME							_T("DFCFGACI.MoveUI")
struct DFCFGACI_MOVEUI_PARAM{
	__int32							nLeft;					//!< [in]: left
	__int32							nTop;					//!< [in]: top
	__int32							nRight;					//!< [in]: right
	__int32							nBottom;				//!< [in]: bottom
};

//	DFCFGACI_UPDATEUI
//******************************************************************************
#define	DFCFGACI_UPDATEUI_PROCNAME							_T("DFCFGACI.UpdateUI")
struct DFCFGACI_UPDATEUI_PARAM{
	BOOL							bShow;					//!< [in]: show window
	BOOL							bEnable;				//!< [in]: enable window
};

//	DFCFGACI_SETUICONFIG
//******************************************************************************
#define	DFCFGACI_SETUICONFIG_PROCNAME						_T("DFCFGACI.SetUIConfig")
struct DFCFGACI_SETUICONFIG_PARAM{
	DFAPI_DATA_TYPE					config;					//!< [in]: config data
};

//	DFCFGACI_GETUICONFIG
//******************************************************************************
#define	DFCFGACI_GETUICONFIG_PROCNAME						_T("DFCFGACI.GetUIConfig")
struct DFCFGACI_GETUICONFIG_PARAM{
	DFAPI_DATA_TYPE					config;					//!< [out]: config data
};

//	DFCFGACI_VALIDATEUICONFIG
//******************************************************************************
#define	DFCFGACI_VALIDATEUICONFIG_PROCNAME					_T("DFCFGACI.ValidateUIConfig")
struct DFCFGACI_VALIDATEUICONFIG_PARAM{
};

//	DFCFGACI_SAVEUICONFIG
//******************************************************************************
#define	DFCFGACI_SAVEUICONFIG_PROCNAME						_T("DFCFGACI.SaveUIConfig")
struct DFCFGACI_SAVEUICONFIG_PARAM{
	DFAPI_TEXTPATH_TYPE				szFilePath;				//!< [in]: file path
};

//	DFCFGACI_LOADUICONFIG
//******************************************************************************
#define	DFCFGACI_LOADUICONFIG_PROCNAME						_T("DFCFGACI.LoadUIConfig")
struct DFCFGACI_LOADUICONFIG_PARAM{
	DFAPI_TEXTPATH_TYPE				szFilePath;				//!< [in]: file path
};

//	DFCFGACI_ENDUI
//******************************************************************************
#define	DFCFGACI_ENDUI_PROCNAME								_T("DFCFGACI.EndUI")
struct DFCFGACI_ENDUI_PARAM{
	DFAPI_DATA_TYPE					config;					//!< [out]: config data
};

//	DFCFGACI_SHOWMODALUI
//******************************************************************************
#define	DFCFGACI_SHOWMODALUI_PROCNAME						_T("DFCFGACI.ShowModalUI")
struct DFCFGACI_SHOWMODALUI_PARAM{
	DFAPI_DATA_TYPE					config;					//!< [in/out]: config data
	HWND							hParentWnd;				//!< [in]: parent window handle
};

//	DFCFGACI_HELP
//******************************************************************************
#define	DFCFGACI_HELP_PROCNAME								_T("DFCFGACI.Help")
struct DFCFGACI_HELP_PARAM{
	HWND							hParentWnd;				//!< [in]: parent window handle
};
