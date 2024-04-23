/*!
	@file	MyCFGACIData.h
	@author	Edmond
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2007-04-03
*/

#pragma once

// CMyCFGACIData
//******************************************************************************
class CMyCFGACIData: public CDFAPIDataHelper{
public:
	CMyCFGACIData();
	~CMyCFGACIData();

	//! @name derived from CDFAPIDataHelper
	//@{
public:
	virtual void Reset();
protected:
	virtual BOOL OnToDataBlock(DWORD& ptr, DFAPI_DATA_TYPE& db);
	virtual BOOL OnFromDataBlock(DWORD& ptr, DFAPI_DATA_TYPE& db);
	//@}

	//! @name data members
	//@{
public:
	CString			m_strDelimiter;
	long			m_lUsingJPG;
	long			m_lBatchImport;

	CString         m_strFolderAll;
	CString         m_strFolderBW;
	CString         m_strFolderCG;

	//@}

	//! @name save configuration data to INI format file; load configuration data from INI format file
	//@{
public:
	void SaveConfig(CString strFile);
	void LoadConfig(CString strFile);

protected:
	void __WriteString(CString strKey, CString strValue, CString strIniFile);
	CString __ReadString(CString strKey, CString strDefault, CString strIniFile);
	void __WriteLong(CString strKey, long lValue, CString strIniFile);
	long __ReadLong(CString strKey, long lDefaultValue, CString strIniFile);
	//@}
};


