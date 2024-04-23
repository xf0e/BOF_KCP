/*!
	@file	MyCFGACIUI.cpp
	@author	Edmond
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2007-04-03
*/

#include "StdAfx.h"
#include "MyCFGACIUI.h"
#include "Resource\Resource.h"
#include "MyPlugin.h"

//  CMyCFGACIUI
//******************************************************************************
IMPLEMENT_DYNAMIC(CMyCFGACIUI, CDFCFGACIBasicUI)

BEGIN_MESSAGE_MAP(CMyCFGACIUI, CDFCFGACIBasicUI)
	ON_MESSAGE(WM_INITDIALOG, __OnInitDialog)
END_MESSAGE_MAP()


CMyCFGACIUI::CMyCFGACIUI() :CDFCFGACIBasicUI(_T("IDD_MYCFGACIUI"))
{
}

CMyCFGACIUI::~CMyCFGACIUI()
{
}

void CMyCFGACIUI::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DELIMITER, m_edtDelimiter);
	DDX_Control(pDX, IDC_BATCHIMPORT, m_ChkBatchImport);
	DDX_Control(pDX, IDC_DOCFIELDLIST, m_cbDocFields);
	DDX_Control(pDX, IDC_BATCHFIELDLIST, m_cbBatchFields);

}

BOOL CMyCFGACIUI::OnInitDialog()
{
	//forward
	BOOL bRt = CDFCFGACIBasicUI::OnInitDialog();
	m_edtDelimiter.SetLimitText(1);

	// Retrieve the Batch and Document Index names 
	// and populate the appropriate ComboBox
	// These valuse are not used in this example 
	// but show how to access index data at
	// BOF setup time

	CMyPlugin* pPlugin = (CMyPlugin*)m_pCFGACIImpl;
	CStringArray arLabels, arValues;
	pPlugin->RetrieveIndex(arLabels, arValues, KCBOFAPI_LEVEL_BATCH);
	for (int i = 0; i < arLabels.GetCount(); i++) 
		m_cbBatchFields.AddString(arLabels[i]);

	pPlugin->RetrieveIndex(arLabels, arValues, KCBOFAPI_LEVEL_DOCUMENT);
	for (int i = 0; i < arLabels.GetCount(); i++) 
		m_cbDocFields.AddString(arLabels[i]);

	return bRt;
}

void CMyCFGACIUI::ToUI()
{
	CMyCFGACIData data;
	data.FromDataBlock(m_config);

	m_edtDelimiter.SetWindowText(data.m_strDelimiter);
	m_ChkBatchImport.SetCheck(data.m_lBatchImport);
}

void CMyCFGACIUI::FromUI()
{
	//Save the configuration to data block m_config.
	CMyCFGACIData data;
	data.m_lBatchImport = m_ChkBatchImport.GetCheck();
    m_edtDelimiter.GetWindowText(data.m_strDelimiter);
	data.ToDataBlock(m_config);

}

void CMyCFGACIUI::Refresh()
{
}

//Validate the UI configuration when press ok button. if return false, dialog will not disappear
BOOL CMyCFGACIUI::ValidateUI()
{
	// Check the data entered on the setup dialog
	CString strText;
	m_edtDelimiter.GetWindowText(strText);

	if (strText.IsEmpty())
	{
		AfxMessageBox(_T("You must specify an index delimiter"));
		m_edtDelimiter.SetFocus();
		return FALSE;
	}

	// No error so return TRUE
	return TRUE;
}
