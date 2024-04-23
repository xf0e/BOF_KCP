/*!
	@file	MyCFGACIData.cpp
	@author	Edmond
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2007-04-03
*/

#include "StdAfx.h"
#include "MyCFGACIData.h"


//  CMyCFGACIData
//******************************************************************************
CMyCFGACIData::CMyCFGACIData()
{
}

CMyCFGACIData::~CMyCFGACIData()
{
}

//  derived from CDFAPIDataHelper
//------------------------------------------------------------------------------
void CMyCFGACIData::Reset()
{
	//Default data values
	m_strFolderAll = _T("");
	m_strFolderBW = _T("");
	m_strFolderCG = _T("");

	m_strDelimiter = _T(",");
	m_lBatchImport = FALSE;


}

BOOL CMyCFGACIData::OnToDataBlock(DWORD& ptr, DFAPI_DATA_TYPE& db)
{
	// Put a random DWORD64 number as signature in the block data of this kind of plugin.
	// Every plugin signature shoud be different!
	const DWORD64 c_signature = 0x33826769144347;
	W_DWORD64(ptr, db, c_signature);

	//Write actual data members
	W_string(ptr,db, m_strFolderAll);
	W_string(ptr, db, m_strFolderBW);
	W_string(ptr, db, m_strFolderCG);

	W_string(ptr, db, m_strDelimiter);
	W_long(ptr, db, m_lBatchImport);


	//
	return TRUE;
}

BOOL CMyCFGACIData::OnFromDataBlock(DWORD& ptr, DFAPI_DATA_TYPE& db)
{
	//c_signature is the same as above. 
	const DWORD64 c_signature = 0x33826769144347;
	DWORD64 signature;
	//Before read actual data, check the signature
	R_DWORD64(ptr, db, signature);
	if (signature != c_signature) 
		return FALSE;

	//Read actual data members
	R_string(ptr,db, m_strFolderAll);
	R_string(ptr, db, m_strFolderBW);
	R_string(ptr, db, m_strFolderCG);

	R_string(ptr, db, m_strDelimiter);
	R_long(ptr, db, m_lBatchImport);

	//
	return TRUE;
}

void CMyCFGACIData::SaveConfig(CString strFile)
{
	__WriteString(_T("strFolderAll"), m_strFolderAll, strFile);
	__WriteString(_T("strFolderBW"), m_strFolderBW, strFile);
	__WriteString(_T("strFolderCG"), m_strFolderCG, strFile);

	// will be called if using an ini file
	__WriteString(_T("Delim"), m_strDelimiter, strFile);
	__WriteLong(_T("BatchImport"), m_lBatchImport, strFile);
}
void CMyCFGACIData::LoadConfig(CString strFile)
{
	m_strFolderAll = __ReadString(_T("strFolderAll"), _T(""), strFile);
	m_strFolderBW = __ReadString(_T("strFolderBW"), _T(""), strFile);
	m_strFolderCG = __ReadString(_T("strFolderCG"), _T(""), strFile);

	m_strDelimiter = __ReadString(_T("Delim"), _T(","), strFile);
	m_lBatchImport = __ReadLong(_T("BatchImport"), 0, strFile);
}

void CMyCFGACIData::__WriteString(CString strKey, CString strValue, CString strIniFile)
{
	WritePrivateProfileString(_T("EXM"), strKey, strValue, strIniFile);
}
CString CMyCFGACIData::__ReadString(CString strKey, CString strDefault, CString strIniFile)
{
	TCHAR buff[500];
	memset(buff, 0, sizeof(buff));
	int nLen = GetPrivateProfileString(_T("EXM"), strKey, strDefault, buff, sizeof(buff), strIniFile);
	return buff;
}

void CMyCFGACIData::__WriteLong(CString strKey, long lValue, CString strIniFile)
{
	CString str;
	str.Format(_T("%d"), lValue);
	__WriteString(strKey, str, strIniFile);
}
long CMyCFGACIData::__ReadLong(CString strKey, long lDefaultValue, CString strIniFile)
{
	CString str;
	CString strDefault;
	strDefault.Format(_T("%d"), lDefaultValue);
	CString strRet = __ReadString(strKey, strDefault, strIniFile);

	return _ttol(strRet);
}

