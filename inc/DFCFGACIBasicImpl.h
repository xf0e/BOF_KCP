/*!
	@file	DFCFGACIBasicImpl.h
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-09-01
*/

#pragma once

#include "DFCFGACIImpl.h"
class CDFCFGACIBasicUI;

//	CDFCFGACIBasicImpl
//******************************************************************************
class CDFCFGACIBasicImpl:public CDFCFGACIImpl{
	friend class CDFCFGACIBasicUI;
protected:
	CDFCFGACIBasicImpl();
	virtual ~CDFCFGACIBasicImpl();

	//!	@name	UI helper
	//@{
protected:
	CDFCFGACIBasicUI*				m_pUI;
	virtual CDFCFGACIBasicUI* CreateUI();
	virtual void DeleteUI(CDFCFGACIBasicUI*& pUI);
	//@}

	//!	@name	config engine
	//@{
protected:
	virtual BOOL CFGACI_GetDefaultConfig(DFAPI_DATA_TYPE& config);
	virtual BOOL CFGACI_ValidateConfig(DFAPI_DATA_TYPE& config);
	virtual BOOL CFGACI_SaveConfig(LPCTSTR lpszFilePath, DFAPI_DATA_TYPE& config);
	virtual BOOL CFGACI_LoadConfig(LPCTSTR lpszFilePath, DFAPI_DATA_TYPE& config);
	virtual BOOL CFGACI_SetCurrentConfig(DFAPI_DATA_TYPE& config);
	virtual BOOL CFGACI_GetCurrentConfig(DFAPI_DATA_TYPE& config);
	virtual BOOL CFGACI_SaveCurrentConfig(LPCTSTR lpszFilePath);
	virtual BOOL CFGACI_LoadCurrentConfig(LPCTSTR lpszFilePath);
	//@}

	//!	@name	current config
	//@{
protected:
	DFAPI_DATA_TYPE					m_CurrentConfig;
	//@}

	//!	@name	UI config
	//@{
protected:
	virtual BOOL CFGACI_GetSupportedUIMode(BOOL& bSupportUI, BOOL& bSupportModalUI);
	virtual BOOL CFGACI_GetUISize(int& nWidth, int& nHeight);
	virtual BOOL CFGACI_BeginUI(DFAPI_DATA_TYPE& config, HWND hParentWnd);
	virtual BOOL CFGACI_MoveUI(int nLeft, int nTop, int nRight, int nBottom);
	virtual BOOL CFGACI_UpdateUI(BOOL bShow, BOOL bEnable);
	virtual BOOL CFGACI_SetUIConfig(DFAPI_DATA_TYPE& config);
	virtual BOOL CFGACI_GetUIConfig(DFAPI_DATA_TYPE& config);
	virtual BOOL CFGACI_ValidateUIConfig();
	virtual BOOL CFGACI_SaveUIConfig(LPCTSTR lpszFilePath);
	virtual BOOL CFGACI_LoadUIConfig(LPCTSTR lpszFilePath);
	virtual BOOL CFGACI_EndUI(DFAPI_DATA_TYPE& config);
	virtual BOOL CFGACI_ShowModalUI(DFAPI_DATA_TYPE& config, HWND hParentWnd);
	virtual BOOL CFGACI_Help(HWND hParentWnd);
	//@}

	//!	@name	CFGACI
	//@{
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(CFGACI_GetDefaultConfig)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(CFGACI_ValidateConfig)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(CFGACI_SaveConfig)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(CFGACI_LoadConfig)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(CFGACI_SetCurrentConfig)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(CFGACI_GetCurrentConfig)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(CFGACI_ValidateCurrentConfig)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(CFGACI_SaveCurrentConfig)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(CFGACI_LoadCurrentConfig)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(CFGACI_GetSupportedUIMode)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(CFGACI_GetUISize)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(CFGACI_BeginUI)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(CFGACI_MoveUI)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(CFGACI_UpdateUI)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(CFGACI_SetUIConfig)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(CFGACI_GetUIConfig)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(CFGACI_ValidateUIConfig)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(CFGACI_SaveUIConfig)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(CFGACI_LoadUIConfig)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(CFGACI_EndUI)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(CFGACI_ShowModalUI)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(CFGACI_Help)
	//@}
};

//******************************************************************************
#include "DFCFGACIBasicImpl.inl"