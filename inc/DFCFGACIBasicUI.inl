/*!
	@file	DFCFGACIBasicUI.inl
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-09-01
*/

#pragma once

#include "DFCFGACIBasicUI.h"

//	CDFCFGACIUIBasicUI
//******************************************************************************
inline CDFCFGACIBasicUI::CDFCFGACIBasicUI(LPCTSTR lpszTemplateName)
:CFormView(lpszTemplateName)
{
	//initialize data connection
	m_pCFGACIImpl = NULL;

	//initialize create/destroy
	m_dwStyle = WS_CHILD;
	m_nID = 0;
}

inline CDFCFGACIBasicUI::CDFCFGACIBasicUI(UINT nIDTemplate)
:CFormView(nIDTemplate)
{
	//initialize data connection
	m_pCFGACIImpl = NULL;

	//initialize create/destroy
	m_dwStyle = WS_CHILD;
	m_nID = 0;
}

//	CFGACI framework
//------------------------------------------------------------------------------
inline void CDFCFGACIBasicUI::SetCFGACIImpl(CDFCFGACIBasicImpl* pCFGACIImpl)
{
	m_pCFGACIImpl = pCFGACIImpl;
}

inline BOOL CDFCFGACIBasicUI::CFGACI_BeginUI(DFAPI_DATA_TYPE& config, HWND hParentWnd)
{
	//copy data
	if (!m_config.CopyFrom(config)) return FALSE;

	//create window
	if (!Create(hParentWnd)) return FALSE;
	ShowWindow(SW_HIDE);

	//to UI
	ToUI();
	Refresh();

	//
	return TRUE;
}

inline BOOL CDFCFGACIBasicUI::CFGACI_MoveUI(int nLeft, int nTop, int nRight, int nBottom)
{
	//check window
	if (!::IsWindow(m_hWnd)) return FALSE;

	//from UI
	FromUI();

	//get window rect
	CRect rcWnd;
	if (nLeft == -1 && nTop == -1 && nRight == -1 && nBottom == -1){
		CWnd* pParentWnd = GetParent();
		if (pParentWnd == NULL) return FALSE;
		pParentWnd->GetClientRect(&rcWnd);
	}
	else{
		rcWnd.left = nLeft;
		rcWnd.top = nTop;
		rcWnd.right = nRight;
		rcWnd.bottom = nBottom;
	}
	rcWnd.NormalizeRect();

	//move
	MoveWindow(&rcWnd);

	//to UI
	Refresh();

	//
	return TRUE;
}

inline BOOL CDFCFGACIBasicUI::CFGACI_UpdateUI(BOOL bShow, BOOL bEnable)
{
	//check window
	if (!::IsWindow(m_hWnd)) return FALSE;

	//from UI
	FromUI();

	//update window
	EnableWindow(bEnable);
	ShowWindow((bShow)?(SW_SHOW):(SW_HIDE));

	//to UI
	Refresh();

	//
	return TRUE;
}

inline BOOL CDFCFGACIBasicUI::CFGACI_SetUIConfig(DFAPI_DATA_TYPE& config)
{
	//set config
	BOOL bSuccess = m_config.CopyFrom(config);

	//to UI
	ToUI();
	Refresh();

	//
	return bSuccess;
}

inline BOOL CDFCFGACIBasicUI::CFGACI_GetUIConfig(DFAPI_DATA_TYPE& config)
{
	//from UI
	FromUI();

	//get config
	return config.CopyFrom(m_config);
}

inline BOOL CDFCFGACIBasicUI::CFGACI_ValidateUIConfig()
{
	if (m_pCFGACIImpl == NULL) return FALSE;

	//from UI
	FromUI();

	//validate config
	return m_pCFGACIImpl->CFGACI_ValidateConfig(m_config);
}

inline BOOL CDFCFGACIBasicUI::CFGACI_SaveUIConfig(LPCTSTR lpszFilePath)
{
	if (m_pCFGACIImpl == NULL) return FALSE;
	
	//from UI
	FromUI();

	//save config
	return m_pCFGACIImpl->CFGACI_SaveConfig(lpszFilePath, m_config);
}

inline BOOL CDFCFGACIBasicUI::CFGACI_LoadUIConfig(LPCTSTR lpszFilePath)
{
	if (m_pCFGACIImpl == NULL) return FALSE;

	//load config
	BOOL bSuccess = m_pCFGACIImpl->CFGACI_LoadConfig(lpszFilePath, m_config);

	//to UI
	ToUI();
	Refresh();

	//
	return bSuccess;
}

inline BOOL CDFCFGACIBasicUI::CFGACI_EndUI(DFAPI_DATA_TYPE& config)
{
	//destroy
	if (::IsWindow(m_hWnd)){
		//from UI
		FromUI();

		//destroy window
		DestroyWindow();
	}

	//get config
	return config.CopyFrom(m_config);
}

//	create/destroy
//------------------------------------------------------------------------------
inline BOOL CDFCFGACIBasicUI::Create(HWND hParentWnd)
{
	//check parent window
	if (hParentWnd == NULL) return FALSE;
	if (!::IsWindow(hParentWnd)) return FALSE;
	CWnd* pParentWnd = CWnd::FromHandle(hParentWnd);
	if (pParentWnd == NULL) return FALSE;

	//check window
	if (::IsWindow(m_hWnd)) return FALSE;

	//create
	if(!CFormView::Create(NULL, NULL, m_dwStyle, CRect(0, 0, 0, 0), pParentWnd, m_nID, NULL))
		return FALSE;
	ModifyStyleEx(0, WS_EX_CONTROLPARENT);

	return TRUE;
}

inline void CDFCFGACIBasicUI::PostNcDestroy()
{
	//do nothing but ignore the auto delete rule defined in CView
}

//	dialog
//------------------------------------------------------------------------------
inline LRESULT CDFCFGACIBasicUI::__OnInitDialog(WPARAM wParam, LPARAM lParam)
{
	return OnInitDialog();
}

inline BOOL CDFCFGACIBasicUI::OnInitDialog()
{
	//update data
	UpdateData(FALSE);

	//
	return TRUE;
}

inline void CDFCFGACIBasicUI::ToUI()
{
}

inline void CDFCFGACIBasicUI::FromUI()
{
}

inline void CDFCFGACIBasicUI::Refresh()
{
}
