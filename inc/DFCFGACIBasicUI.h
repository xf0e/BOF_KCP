/*!
	@file	DFCFGACIBasicUI.h
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-09-01
*/

#pragma once

#include <afxext.h>
#include "DFCFGACIBasicImpl.h"

//	CDFCFGACIBasicUI
//******************************************************************************
class CDFCFGACIBasicUI:public CFormView{
protected:
	CDFCFGACIBasicUI(LPCTSTR lpszTemplateName);
	CDFCFGACIBasicUI(UINT nIDTemplate);

	//!	@name	CFGACI framework
	//@{
protected:
	CDFCFGACIBasicImpl*				m_pCFGACIImpl;
	DFAPI_DATA_TYPE					m_config;
public:
	void SetCFGACIImpl(CDFCFGACIBasicImpl* pCFGACIImpl);
	virtual BOOL CFGACI_BeginUI(DFAPI_DATA_TYPE& config, HWND hParentWnd);
	virtual BOOL CFGACI_MoveUI(int nLeft, int nTop, int nRight, int nBottom);
	virtual BOOL CFGACI_UpdateUI(BOOL bShow, BOOL bEnable);
	virtual BOOL CFGACI_SetUIConfig(DFAPI_DATA_TYPE& config);
	virtual BOOL CFGACI_GetUIConfig(DFAPI_DATA_TYPE& config);
	virtual BOOL CFGACI_ValidateUIConfig();
	virtual BOOL CFGACI_SaveUIConfig(LPCTSTR lpszFilePath);
	virtual BOOL CFGACI_LoadUIConfig(LPCTSTR lpszFilePath);
	virtual BOOL CFGACI_EndUI(DFAPI_DATA_TYPE& config);
	//@}

	//!	@name	create/destroy
	//@{
protected:
	DWORD							m_dwStyle;
	UINT							m_nID;
	virtual BOOL Create(HWND hParentWnd);
	void PostNcDestroy();
	//@}

	//!	@name	dialog
	//@{
protected:
	afx_msg LRESULT __OnInitDialog(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnInitDialog();

	//!	Set config data to UI.
	/*!	
		Invoked by framework when config data had been updated.  Override this routine
		to display the config data on UI.
	*/
	virtual void ToUI();

	//!	Get config data from UI.
	/*!
		Invoked by framework when config data is being retrieved.  Override this routine
		to retrieve the config data from UI.
	*/
	virtual void FromUI();

	//!	Refresh UI.
	/*!
		Invoked by framework when UI is forced to refresh.  Override this routine
		to refresh the UI by its business rule.
	*/
	virtual void Refresh();
	//@}
};

//******************************************************************************
#include "DFCFGACIBasicUI.inl"