/*!
@file	KCBOFACIImpl.h
@author	Philip Wu (hanbing.wu@kodak.com)
@author	Copyright (C) 1998-2008 Eastman Kodak Company.
@author	All rights reserved.
@date	2009-02-18
*/

#pragma once
#include "KCBOFACIImpl.h"
#include "DFCKRN.h"
//	CDFERRACIBasicImpl
//******************************************************************************
class CKCBOFACIBasicImpl:public CKCBOFACIImpl{
protected:
    CKCBOFACIBasicImpl();

    DFAPI_PLUGIN_DECLARE_STD_INTERFACE(KCBOFAPI_ClearIndexKey)
    DFAPI_PLUGIN_DECLARE_STD_INTERFACE(KCBOFAPI_AddIndexKey)
    DFAPI_PLUGIN_DECLARE_STD_INTERFACE(KCBOFAPI_ClearIndexValue)
    DFAPI_PLUGIN_DECLARE_STD_INTERFACE(KCBOFAPI_SetIndexValue)
    DFAPI_PLUGIN_DECLARE_STD_INTERFACE(KCBOFAPI_BeginProcess)
    DFAPI_PLUGIN_DECLARE_STD_INTERFACE(KCBOFAPI_AddImageFile)
    DFAPI_PLUGIN_DECLARE_STD_INTERFACE(KCBOFAPI_EndProcess)
    DFAPI_PLUGIN_DECLARE_STD_INTERFACE(KCBOFAPI_AbortProcess)
    DFAPI_PLUGIN_DECLARE_STD_INTERFACE(KCBOFAPI_GetSupportedFileTypes)
    DFAPI_PLUGIN_DECLARE_STD_INTERFACE(KCBOFAPI_SetOutputFileType)
    DFAPI_PLUGIN_DECLARE_STD_INTERFACE(KCBOFAPI_ValidateConfig)
    DFAPI_PLUGIN_DECLARE_STD_INTERFACE(KCBOFAPI_GetFilePathName)
    DFAPI_PLUGIN_DECLARE_STD_INTERFACE(KCBOFAPI_SetFilePathName)

    //!	@name	level definition
    //@{
protected:
    BOOL CheckLevel(int nLevel);
    //@}

    //!	@name	index engine
    //@{

public:
    CDFObDSKeyStringItemList		m_Index;
	
protected:
    virtual BOOL ClearIndexKey(int nLevel);
    virtual BOOL AddIndexKey(int nLevel, LPCTSTR lpszIndexKey);
    virtual BOOL ClearIndexValue(int nLevel);
    virtual BOOL SetIndexValue(int nLevel, LPCTSTR lpszIndexKey, LPCTSTR lpszIndexValue);
    virtual BOOL GetIndexValue(int nLevel, LPCTSTR lpszIndexKey, CString& strIndexValue);
    //     virtual BOOL BeginProcess(int nLevel, LPCTSTR lpszLevelName, LPCTSTR lpszLevelID);
    //     virtual BOOL EndProcess(int nLevel);

    //@}

    //!	@name	process engine
    //@{
protected:
    CString							m_strBatchLevelName;
    CString							m_strDocumentLevelName;
    CString							m_strPageLevelName;
    CString							m_strImageLevelName;
    CString							m_strBatchLevelID;
    CString							m_strDocumentLevelID;
    CString							m_strPageLevelID;
    CString							m_strImageLevelID;
    int								m_nCurrentLevel;

    int                             m_nImageSequenceByBatch;
    int                             m_nImageSequenceByDocument;

    DWORD m_dwGroupModeAll;
    DWORD m_dwGroupModeBW;
    DWORD m_dwGroupModeCG;

    DWORD m_dwFileTypeAll;
    DWORD m_dwFileTypeBW;
    DWORD m_dwFileTypeCG;

    CString                         m_strCurFilePathAll;
    CString                         m_strCurFilePathBW;
    CString                         m_strCurFilePathCG;

    BOOL BeginProcess(int nLevel, LPCTSTR lpszLevelName, LPCTSTR lpszLevelID);
    BOOL EndProcess(int nLevel);

    virtual BOOL OnAddImageFile(LPCTSTR lpszImageFilePath, KCBOFAPI_IMAGEINFO& info);

    virtual BOOL OnBeginProcessBatch();
    virtual BOOL OnBeginProcessDocument();
    virtual BOOL OnBeginProcessPage();
    virtual BOOL OnBeginProcessImage();

    virtual BOOL OnEndProcessImage();
    virtual BOOL OnEndProcessPage();
    virtual BOOL OnEndProcessDocument();
    virtual BOOL OnEndProcessBatch();
    virtual void OnAbortProcess();

    virtual BOOL GetSupportedFileTypes(DWORD &dwFileTypeAll, DWORD &dwFileTypeBW, DWORD &dwFileTypeCG, DWORD &dwGroupModeAll, DWORD &dwGroupModeBW, DWORD &dwGroupModeCG);
    virtual BOOL SetOutputFileType(DWORD dwFileTypeAll, DWORD dwFileTypeBW, DWORD dwFileTypeCG, DWORD dwGroupModeAll, DWORD dwGroupModeBW, DWORD dwGroupModeCG);
    virtual BOOL ValidateConfig(DWORD dwSuccess, CString& strErrMsg);
    virtual BOOL GetFilePathName(DWORD dwChannel, CString &strFilePathFormula);
    virtual BOOL SetFilePathName(DWORD dwChannel, LPCTSTR lpszFilePathName);
};

//******************************************************************************
#include "KCBOFACIBasicImpl.inl"
