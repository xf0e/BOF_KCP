/*!
	@file	DFCFGACIBasicImpl.inl
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-09-01
*/

#pragma once

#include "DFCFGACIBasicImpl.h"
#include "DFCFGACIBasicUI.h"

//	CDFCFGACIBasicImpl
//******************************************************************************
inline CDFCFGACIBasicImpl::CDFCFGACIBasicImpl()
{
	//initialize UI helper
	m_pUI = NULL;
}

inline CDFCFGACIBasicImpl::~CDFCFGACIBasicImpl()
{
	//clean up UI helper
	DeleteUI(m_pUI);
}

//	UI helper
//------------------------------------------------------------------------------
inline CDFCFGACIBasicUI* CDFCFGACIBasicImpl::CreateUI()
{
	return NULL;
}

inline void CDFCFGACIBasicImpl::DeleteUI(CDFCFGACIBasicUI*& pUI)
{
	if (pUI == NULL) return;
	delete pUI;
	pUI = NULL;
}

//	config engine
//------------------------------------------------------------------------------
inline BOOL CDFCFGACIBasicImpl::CFGACI_GetDefaultConfig(DFAPI_DATA_TYPE& config)
{
	config.Free();
	return TRUE;
}

inline BOOL CDFCFGACIBasicImpl::CFGACI_ValidateConfig(DFAPI_DATA_TYPE& config)
{
	return TRUE;
}

inline BOOL CDFCFGACIBasicImpl::CFGACI_SaveConfig(LPCTSTR lpszFilePath, DFAPI_DATA_TYPE& config)
{
	return config.Save(lpszFilePath);
}

inline BOOL CDFCFGACIBasicImpl::CFGACI_LoadConfig(LPCTSTR lpszFilePath, DFAPI_DATA_TYPE& config)
{
	return config.Load(lpszFilePath);
}

inline BOOL CDFCFGACIBasicImpl::CFGACI_SetCurrentConfig(DFAPI_DATA_TYPE& config)
{
	return m_CurrentConfig.CopyFrom(config);
}

inline BOOL CDFCFGACIBasicImpl::CFGACI_GetCurrentConfig(DFAPI_DATA_TYPE& config)
{
	return m_CurrentConfig.CopyTo(config);
}

inline BOOL CDFCFGACIBasicImpl::CFGACI_SaveCurrentConfig(LPCTSTR lpszFilePath)
{
	return CFGACI_SaveConfig(lpszFilePath, m_CurrentConfig);
}

inline BOOL CDFCFGACIBasicImpl::CFGACI_LoadCurrentConfig(LPCTSTR lpszFilePath)
{
	DFAPI_DATA_TYPE config;
	if (!CFGACI_LoadConfig(lpszFilePath, config)) return FALSE;
	return CFGACI_SetCurrentConfig(config);
}

//	UI config
//------------------------------------------------------------------------------
inline BOOL CDFCFGACIBasicImpl::CFGACI_GetSupportedUIMode(BOOL& bSupportUI, BOOL& bSupportModalUI)
{
	bSupportUI = FALSE;
	bSupportModalUI = FALSE;
	return TRUE;
}

inline BOOL CDFCFGACIBasicImpl::CFGACI_GetUISize(int& nWidth, int& nHeight)
{
	nWidth = -1;
	nHeight = -1;
	return TRUE;
}

inline BOOL CDFCFGACIBasicImpl::CFGACI_BeginUI(DFAPI_DATA_TYPE& config, HWND hParentWnd)
{
	//create UI
	DeleteUI(m_pUI);
	m_pUI = CreateUI();
	if (m_pUI == NULL) return FALSE;
	m_pUI->SetCFGACIImpl(this);

	//begin UI
	return m_pUI->CFGACI_BeginUI(config, hParentWnd);
}

inline BOOL CDFCFGACIBasicImpl::CFGACI_MoveUI(int nLeft, int nTop, int nRight, int nBottom)
{
	if (m_pUI == NULL) return FALSE;
	return m_pUI->CFGACI_MoveUI(nLeft, nTop, nRight, nBottom);
}

inline BOOL CDFCFGACIBasicImpl::CFGACI_UpdateUI(BOOL bShow, BOOL bEnable)
{
	if (m_pUI == NULL) return FALSE;
	return m_pUI->CFGACI_UpdateUI(bShow, bEnable);
}

inline BOOL CDFCFGACIBasicImpl::CFGACI_SetUIConfig(DFAPI_DATA_TYPE& config)
{
	if (m_pUI == NULL) return FALSE;
	return m_pUI->CFGACI_SetUIConfig(config);
}

inline BOOL CDFCFGACIBasicImpl::CFGACI_GetUIConfig(DFAPI_DATA_TYPE& config)
{
	if (m_pUI == NULL) return FALSE;
	return m_pUI->CFGACI_GetUIConfig(config);
}

inline BOOL CDFCFGACIBasicImpl::CFGACI_ValidateUIConfig()
{
	if (m_pUI == NULL) return FALSE;
	return m_pUI->CFGACI_ValidateUIConfig();
}

inline BOOL CDFCFGACIBasicImpl::CFGACI_SaveUIConfig(LPCTSTR lpszFilePath)
{
	if (m_pUI == NULL) return FALSE;
	return m_pUI->CFGACI_SaveUIConfig(lpszFilePath);
}

inline BOOL CDFCFGACIBasicImpl::CFGACI_LoadUIConfig(LPCTSTR lpszFilePath)
{
	if (m_pUI == NULL) return FALSE;
	return m_pUI->CFGACI_LoadUIConfig(lpszFilePath);
}

inline BOOL CDFCFGACIBasicImpl::CFGACI_EndUI(DFAPI_DATA_TYPE& config)
{
	//end UI
	if (m_pUI == NULL) return FALSE;
	BOOL bSuccess = m_pUI->CFGACI_EndUI(config);

	//delete UI
	DeleteUI(m_pUI);

	//
	return bSuccess;
}

inline BOOL CDFCFGACIBasicImpl::CFGACI_ShowModalUI(DFAPI_DATA_TYPE& config, HWND hParentWnd)
{
	return FALSE;
}

inline BOOL CDFCFGACIBasicImpl::CFGACI_Help(HWND hParentWnd)
{
	return FALSE;
}

//	CFGACI
//------------------------------------------------------------------------------
DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFCFGACIBasicImpl, CFGACI_GetDefaultConfig)
{
	DFCFGACI_GETDEFAULTCONFIG_PARAM* p = (DFCFGACI_GETDEFAULTCONFIG_PARAM*) param;
	if (p == NULL) return FALSE;

	//get default config
	return CFGACI_GetDefaultConfig(p->config);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFCFGACIBasicImpl, CFGACI_ValidateConfig)
{
	DFCFGACI_VALIDATECONFIG_PARAM* p = (DFCFGACI_VALIDATECONFIG_PARAM*) param;
	if (p == NULL) return FALSE;

	//validate config
	return CFGACI_ValidateConfig(p->config);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFCFGACIBasicImpl, CFGACI_SaveConfig)
{
	DFCFGACI_SAVECONFIG_PARAM* p = (DFCFGACI_SAVECONFIG_PARAM*) param;
	if (p == NULL) return FALSE;

	//save config
	return CFGACI_SaveConfig(p->szFilePath, p->config);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFCFGACIBasicImpl, CFGACI_LoadConfig)
{
	DFCFGACI_LOADCONFIG_PARAM* p = (DFCFGACI_LOADCONFIG_PARAM*) param;
	if (p == NULL) return FALSE;

	//load config
	return CFGACI_LoadConfig(p->szFilePath, p->config);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFCFGACIBasicImpl, CFGACI_SetCurrentConfig)
{
	DFCFGACI_SETCURRENTCONFIG_PARAM* p = (DFCFGACI_SETCURRENTCONFIG_PARAM*) param;
	if (p == NULL) return FALSE;

	//set current config
	return CFGACI_SetCurrentConfig(p->config);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFCFGACIBasicImpl, CFGACI_GetCurrentConfig)
{
	DFCFGACI_GETCURRENTCONFIG_PARAM* p = (DFCFGACI_GETCURRENTCONFIG_PARAM*) param;
	if (p == NULL) return FALSE;

	//get current config
	return CFGACI_GetCurrentConfig(p->config);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFCFGACIBasicImpl, CFGACI_ValidateCurrentConfig)
{
	DFCFGACI_VALIDATECURRENTCONFIG_PARAM* p = (DFCFGACI_VALIDATECURRENTCONFIG_PARAM*) param;
	if (p == NULL) return FALSE;

	//validate current config
	return CFGACI_ValidateConfig(m_CurrentConfig);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFCFGACIBasicImpl, CFGACI_SaveCurrentConfig)
{
	DFCFGACI_SAVECURRENTCONFIG_PARAM* p = (DFCFGACI_SAVECURRENTCONFIG_PARAM*) param;
	if (p == NULL) return FALSE;

	//save current config
	return CFGACI_SaveCurrentConfig(p->szFilePath);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFCFGACIBasicImpl, CFGACI_LoadCurrentConfig)
{
	DFCFGACI_LOADCURRENTCONFIG_PARAM* p = (DFCFGACI_LOADCURRENTCONFIG_PARAM*) param;
	if (p == NULL) return FALSE;

	//load current config
	return CFGACI_LoadCurrentConfig(p->szFilePath);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFCFGACIBasicImpl, CFGACI_GetSupportedUIMode)
{
	DFCFGACI_GETSUPPORTEDUIMODE_PARAM* p = (DFCFGACI_GETSUPPORTEDUIMODE_PARAM*) param;
	if (p == NULL) return FALSE;

	//get supported UI mode
	return CFGACI_GetSupportedUIMode(p->bSupportUI, p->bSupportModalUI);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFCFGACIBasicImpl, CFGACI_GetUISize)
{
	DFCFGACI_GETUISIZE_PARAM* p = (DFCFGACI_GETUISIZE_PARAM*) param;
	if (p == NULL) return FALSE;

	//get standard UI size
	return CFGACI_GetUISize(p->nWidth, p->nHeight);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFCFGACIBasicImpl, CFGACI_BeginUI)
{
	DFCFGACI_BEGINUI_PARAM* p = (DFCFGACI_BEGINUI_PARAM*) param;
	if (p == NULL) return FALSE;

	//begin UI
	return CFGACI_BeginUI(p->config, p->hParentWnd);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFCFGACIBasicImpl, CFGACI_MoveUI)
{
	DFCFGACI_MOVEUI_PARAM* p = (DFCFGACI_MOVEUI_PARAM*) param;
	if (p == NULL) return FALSE;

	//move UI
	return CFGACI_MoveUI(p->nLeft, p->nTop, p->nRight, p->nBottom);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFCFGACIBasicImpl, CFGACI_UpdateUI)
{
	DFCFGACI_UPDATEUI_PARAM* p = (DFCFGACI_UPDATEUI_PARAM*) param;
	if (p == NULL) return FALSE;

	//update UI
	return CFGACI_UpdateUI(p->bShow, p->bEnable);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFCFGACIBasicImpl, CFGACI_SetUIConfig)
{
	DFCFGACI_SETUICONFIG_PARAM* p = (DFCFGACI_SETUICONFIG_PARAM*) param;
	if (p == NULL) return FALSE;

	//set UI config
	return CFGACI_SetUIConfig(p->config);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFCFGACIBasicImpl, CFGACI_GetUIConfig)
{
	DFCFGACI_GETUICONFIG_PARAM* p = (DFCFGACI_GETUICONFIG_PARAM*) param;
	if (p == NULL) return FALSE;

	//get UI config
	return CFGACI_GetUIConfig(p->config);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFCFGACIBasicImpl, CFGACI_ValidateUIConfig)
{
	DFCFGACI_VALIDATEUICONFIG_PARAM* p = (DFCFGACI_VALIDATEUICONFIG_PARAM*) param;
	if (p == NULL) return FALSE;

	//validate UI config
	return CFGACI_ValidateUIConfig();
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFCFGACIBasicImpl, CFGACI_SaveUIConfig)
{
	DFCFGACI_SAVEUICONFIG_PARAM* p = (DFCFGACI_SAVEUICONFIG_PARAM*) param;
	if (p == NULL) return FALSE;

	//save UI config
	return CFGACI_SaveUIConfig(p->szFilePath);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFCFGACIBasicImpl, CFGACI_LoadUIConfig)
{
	DFCFGACI_LOADUICONFIG_PARAM* p = (DFCFGACI_LOADUICONFIG_PARAM*) param;
	if (p == NULL) return FALSE;

	//load UI config
	return CFGACI_LoadUIConfig(p->szFilePath);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFCFGACIBasicImpl, CFGACI_EndUI)
{
	DFCFGACI_ENDUI_PARAM* p = (DFCFGACI_ENDUI_PARAM*) param;
	if (p == NULL) return FALSE;

	//end UI
	return CFGACI_EndUI(p->config);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFCFGACIBasicImpl, CFGACI_ShowModalUI)
{
	DFCFGACI_SHOWMODALUI_PARAM* p = (DFCFGACI_SHOWMODALUI_PARAM*) param;
	if (p == NULL) return FALSE;

	//show modal UI
	return CFGACI_ShowModalUI(p->config, p->hParentWnd);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CDFCFGACIBasicImpl, CFGACI_Help)
{
	DFCFGACI_HELP_PARAM* p = (DFCFGACI_HELP_PARAM*) param;
	if (p == NULL) return FALSE;

	//help
	return CFGACI_Help(p->hParentWnd);
}