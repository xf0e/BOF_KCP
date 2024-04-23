/*!
	@file	MyCFGACIUI.h
	@author	Edmond
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2007-04-03
*/

#pragma once

#include "MyCFGACIData.h"

// CMyCFGACIUI
//******************************************************************************
class CMyCFGACIUI: public CDFCFGACIBasicUI{
	DECLARE_DYNAMIC(CMyCFGACIUI)
	DECLARE_MESSAGE_MAP()
public:
	CMyCFGACIUI();
	~CMyCFGACIUI();

	//! @name dialog
	//@{
protected:
	void DoDataExchange(CDataExchange* pDX);
	BOOL OnInitDialog();
	virtual void ToUI();
	virtual void FromUI();
	virtual void Refresh();
	//@}
	
public:
	// Called By MyPlugin to validate UI.
	BOOL ValidateUI();

	//! @name controls
	//@{
protected:

	CEdit            m_edtDelimiter;
	CButton 		 m_ChkBatchImport;
	CComboBox		 m_cbDocFields;
	CComboBox		 m_cbBatchFields;
	//@}

	
};

