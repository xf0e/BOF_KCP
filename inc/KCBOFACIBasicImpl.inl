/*!
@file	KCBOFACIBasicImpl.h
@author	Philip Wu (hanbing.wu@kodak.com)
@author	Copyright (C) 1998-2008 Eastman Kodak Company.
@author	All rights reserved.
@date	2009-02-18
*/

#pragma once

inline CKCBOFACIBasicImpl::CKCBOFACIBasicImpl()
{
    m_nCurrentLevel = -1;
}
DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CKCBOFACIBasicImpl, KCBOFAPI_ClearIndexKey)
{
    KCBOFAPI_CLEARINDEXKEY_PARAM* p = (KCBOFAPI_CLEARINDEXKEY_PARAM*) param;
    if (p == NULL) return FALSE;

    //clear index key
    return ClearIndexKey((int) p->nLevel);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CKCBOFACIBasicImpl, KCBOFAPI_AddIndexKey)
{
    KCBOFAPI_ADDINDEXKEY_PARAM* p = (KCBOFAPI_ADDINDEXKEY_PARAM*) param;
    if (p == NULL) return FALSE;

    //add index key
    return AddIndexKey((int) p->nLevel, p->szIndexKey);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CKCBOFACIBasicImpl, KCBOFAPI_ClearIndexValue)
{
    KCBOFAPI_CLEARINDEXVALUE_PARAM* p = (KCBOFAPI_CLEARINDEXVALUE_PARAM*) param;
    if (p == NULL) return FALSE;

    //clear index value
    return ClearIndexValue((int) p->nLevel);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CKCBOFACIBasicImpl, KCBOFAPI_SetIndexValue)
{
    KCBOFAPI_SETINDEXVALUE_PARAM* p = (KCBOFAPI_SETINDEXVALUE_PARAM*) param;
    if (p == NULL) return FALSE;

    //set index value
    return SetIndexValue((int) p->nLevel, p->szIndexKey, p->szIndexValue);
}
DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CKCBOFACIBasicImpl, KCBOFAPI_GetSupportedFileTypes)
{
    KCBOFAPI_FILETYPES_PARAM* p = (KCBOFAPI_FILETYPES_PARAM*) param;
    if (p == NULL) return FALSE;

    //get supported file types
    return GetSupportedFileTypes(p->dwFileTypeAll, p->dwFileTypeBW, p->dwFileTypeCG, p->dwGroupModeAll,p->dwGroupModeBW,p->dwGroupModeCG);
}
DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CKCBOFACIBasicImpl, KCBOFAPI_SetOutputFileType)
{
    KCBOFAPI_FILETYPES_PARAM* p = (KCBOFAPI_FILETYPES_PARAM*) param;
    if (p == NULL) return FALSE;

    //get supported file types
    return SetOutputFileType(p->dwFileTypeAll, p->dwFileTypeBW, p->dwFileTypeCG, p->dwGroupModeAll,p->dwGroupModeBW,p->dwGroupModeCG);
}
DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CKCBOFACIBasicImpl, KCBOFAPI_ValidateConfig)
{
    KCBOFAPI_VALIDATECONFIG_PARAM* p = (KCBOFAPI_VALIDATECONFIG_PARAM*) param;
    if (p == NULL) return FALSE;

    //get supported file types
    CString strErrMsg;
    if( ValidateConfig(p->bSuccess, strErrMsg))
    {
        p->szErrorMessage.SetEx(strErrMsg);
        return TRUE;
    }
    return FALSE;
}
DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CKCBOFACIBasicImpl, KCBOFAPI_GetFilePathName)
{
    KCBOFAPI_FILEPATHNAME_PARAM* p = (KCBOFAPI_FILEPATHNAME_PARAM*) param;
    if (p == NULL) return FALSE;

    //get supported file types
    CString strFilePathFormula;
    if(GetFilePathName(p->dwChannel, strFilePathFormula))
    {
        p->szPathName.SetEx(strFilePathFormula);
        return TRUE;
    }
    return FALSE;
}
DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CKCBOFACIBasicImpl, KCBOFAPI_SetFilePathName)
{
    KCBOFAPI_FILEPATHNAME_PARAM* p = (KCBOFAPI_FILEPATHNAME_PARAM*) param;
    if (p == NULL) return FALSE;

    //get supported file types
    return SetFilePathName(p->dwChannel, p->szPathName);
}
DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CKCBOFACIBasicImpl, KCBOFAPI_BeginProcess)
{
    KCBOFAPI_BEGINPROCESS_PARAM* p = (KCBOFAPI_BEGINPROCESS_PARAM*) param;
    if (p == NULL) return FALSE;

    //begin process
    return BeginProcess((int) p->nLevel, p->szLevelName, p->szLevelID);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CKCBOFACIBasicImpl, KCBOFAPI_AddImageFile)
{
    KCBOFAPI_ADDIMAGEFILE_PARAM* p = (KCBOFAPI_ADDIMAGEFILE_PARAM*) param;
    if (p == NULL) return FALSE;

    //add image file
    return OnAddImageFile(p->szImageFilePath, p->info);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CKCBOFACIBasicImpl, KCBOFAPI_EndProcess)
{
    KCBOFAPI_ENDPROCESS_PARAM* p = (KCBOFAPI_ENDPROCESS_PARAM*) param;
    if (p == NULL) return FALSE;

    //end process
    return EndProcess((int) p->nLevel);
}

DFAPI_PLUGIN_INLINE_IMPLEMENT_STD_INTERFACE(CKCBOFACIBasicImpl, KCBOFAPI_AbortProcess)
{
    KCBOFAPI_ABORTPROCESS_PARAM* p = (KCBOFAPI_ABORTPROCESS_PARAM*) param;
    if (p == NULL) return FALSE;

    //abort process
    OnAbortProcess();
    return TRUE;
}

//	level definition
//------------------------------------------------------------------------------
BOOL inline CKCBOFACIBasicImpl::CheckLevel(int nLevel)
{
    switch (nLevel){
        case KCBOFAPI_LEVEL_BATCH:
        case KCBOFAPI_LEVEL_DOCUMENT:
        case KCBOFAPI_LEVEL_PAGE:
        case KCBOFAPI_LEVEL_IMAGE:
            return TRUE;
    }
    return FALSE;
}

//	index engine
//------------------------------------------------------------------------------
BOOL inline CKCBOFACIBasicImpl::ClearIndexKey(int nLevel)
{
    //check level
    if (!CheckLevel(nLevel)) return FALSE;

    //clear index key
    POSITION pos = m_Index.GetHeadPosition();
    while (pos){
        POSITION posCurrent = pos;
        CDFObDSKeyStringItem* pItem = (CDFObDSKeyStringItem*) m_Index.GetNext(pos);
        if (pItem == NULL) continue;
        if (pItem->m_dkey == (DWORD) nLevel) m_Index.Remove(posCurrent);
    }

    //
    return TRUE;
}

BOOL inline CKCBOFACIBasicImpl::AddIndexKey(int nLevel, LPCTSTR lpszIndexKey)
{
    //check level
    if (!CheckLevel(nLevel)) return FALSE;

    //normalize key
    CString strIndexKey = lpszIndexKey;
    strIndexKey.Trim();
    if (strIndexKey.IsEmpty()) return FALSE;

    //add index key
    POSITION pos = m_Index.Find((DWORD) nLevel, strIndexKey);
    if (pos == NULL){
        CDFObDSKeyStringItem* pItem = (CDFObDSKeyStringItem*) m_Index.AddTail();
        if (pItem == NULL) return FALSE;
        pItem->m_dkey = (DWORD) nLevel;
        pItem->m_skey = strIndexKey;
    }

    //
    return TRUE;
}

BOOL inline CKCBOFACIBasicImpl::ClearIndexValue(int nLevel)
{
    //check level
    if (!CheckLevel(nLevel)) return FALSE;

    //clear index value
    POSITION pos = m_Index.GetHeadPosition();
    while (pos){
        CDFObDSKeyStringItem* pItem = (CDFObDSKeyStringItem*) m_Index.GetNext(pos);
        if (pItem == NULL) continue;
        if (pItem->m_dkey == (DWORD) nLevel) pItem->m_str.Empty();
    }

    //
    return TRUE;
}

BOOL inline CKCBOFACIBasicImpl::SetIndexValue(int nLevel, LPCTSTR lpszIndexKey, LPCTSTR lpszIndexValue)
{
    //check level
    if (!CheckLevel(nLevel)) return FALSE;

    //normalize key
    CString strIndexKey = lpszIndexKey;
    strIndexKey.Trim();
    if (strIndexKey.IsEmpty()) return FALSE;

    //find index key
    POSITION pos = m_Index.Find((DWORD) nLevel, strIndexKey);
    if (pos == NULL) return FALSE;

    //set index value
    CDFObDSKeyStringItem* pItem = (CDFObDSKeyStringItem*) m_Index.GetAt(pos);
    if (pItem == NULL) return FALSE;
    pItem->m_str = lpszIndexValue;

    //
    return TRUE;
}

BOOL inline CKCBOFACIBasicImpl::GetIndexValue(int nLevel, LPCTSTR lpszIndexKey, CString& strIndexValue)
{
    //check level
    if (!CheckLevel(nLevel)) return FALSE;

    //normalize key
    CString strIndexKey = lpszIndexKey;
    strIndexKey.Trim();
    if (strIndexKey.IsEmpty()) return FALSE;

    //find index key
    POSITION pos = m_Index.Find((DWORD) nLevel, strIndexKey);
    if (pos == NULL) return FALSE;

    //get index value
    CDFObDSKeyStringItem* pItem = (CDFObDSKeyStringItem*) m_Index.GetAt(pos);
    if (pItem == NULL) return FALSE;
    strIndexValue = pItem->m_str;

    //
    return TRUE;
}

//	process engine
//------------------------------------------------------------------------------
BOOL inline CKCBOFACIBasicImpl::GetSupportedFileTypes(DWORD &dwFileTypeAll, DWORD &dwFileTypeBW, DWORD &dwFileTypeCG, DWORD &dwGroupModeAll, DWORD &dwGroupModeBW, DWORD &dwGroupModeCG)
{
    return TRUE;
}
BOOL inline CKCBOFACIBasicImpl::SetOutputFileType(DWORD dwFileTypeAll, DWORD dwFileTypeBW, DWORD dwFileTypeCG, DWORD dwGroupModeAll, DWORD dwGroupModeBW, DWORD dwGroupModeCG)
{
    m_dwFileTypeAll = dwFileTypeAll;
    m_dwFileTypeBW = dwFileTypeBW;
    m_dwFileTypeCG = dwFileTypeCG;
    m_dwGroupModeAll = dwGroupModeAll;
    m_dwGroupModeBW = dwGroupModeBW;
    m_dwGroupModeCG = dwGroupModeCG;

    return TRUE;
}
BOOL inline CKCBOFACIBasicImpl::ValidateConfig(DWORD dwSuccess, CString& strErrMsg)
{
    dwSuccess = TRUE;
    strErrMsg.Empty();
    return TRUE;
}
BOOL inline CKCBOFACIBasicImpl::GetFilePathName(DWORD dwChannel, CString &strFilePathFormula)
{
    return FALSE;
}
BOOL inline CKCBOFACIBasicImpl::SetFilePathName(DWORD dwChannel, LPCTSTR lpszFilePathName)
{
    switch(dwChannel)
    {
    case KCBOFAPI_CHANNEL_ALL:
        m_strCurFilePathAll = lpszFilePathName;
    	break;
    case KCBOFAPI_CHANNEL_BW:
        m_strCurFilePathBW = lpszFilePathName;
    	break;
    case KCBOFAPI_CHANNEL_CG:
        m_strCurFilePathCG = lpszFilePathName;
        break;
    default:
        return FALSE;
    }
    
    return TRUE;
}

BOOL inline CKCBOFACIBasicImpl::BeginProcess(int nLevel, LPCTSTR lpszLevelName, LPCTSTR lpszLevelID)
{
    //check level
    switch (nLevel){
        case KCBOFAPI_LEVEL_BATCH:
            if (m_nCurrentLevel != -1) return FALSE;
            m_nCurrentLevel = KCBOFAPI_LEVEL_BATCH;
            m_strBatchLevelName = lpszLevelName;
            m_strBatchLevelID = lpszLevelID;
            m_nImageSequenceByBatch = 0;
            m_nImageSequenceByDocument = 0;
            return OnBeginProcessBatch();

        case KCBOFAPI_LEVEL_DOCUMENT:
            if (m_nCurrentLevel != KCBOFAPI_LEVEL_BATCH) return FALSE;
            m_nCurrentLevel = KCBOFAPI_LEVEL_DOCUMENT;
            m_strDocumentLevelName = lpszLevelName;
            m_strDocumentLevelID = lpszLevelID;
            m_nImageSequenceByDocument = 0;
            return OnBeginProcessDocument();

        case KCBOFAPI_LEVEL_PAGE:
            if (m_nCurrentLevel != KCBOFAPI_LEVEL_DOCUMENT) return FALSE;
            m_nCurrentLevel = KCBOFAPI_LEVEL_PAGE;
            m_strPageLevelName = lpszLevelName;
            m_strPageLevelID = lpszLevelID;
            return OnBeginProcessPage();

        case KCBOFAPI_LEVEL_IMAGE:
            if (m_nCurrentLevel != KCBOFAPI_LEVEL_PAGE) return FALSE;
            m_nCurrentLevel = KCBOFAPI_LEVEL_IMAGE;
            m_strImageLevelName = lpszLevelName;
            m_strImageLevelID = lpszLevelID;
            m_nImageSequenceByDocument ++;
            m_nImageSequenceByBatch ++;
            return OnBeginProcessImage();
    }

    //
    return FALSE;
}

BOOL inline CKCBOFACIBasicImpl::EndProcess(int nLevel)
{
    //check level
    switch (nLevel){
        case KCBOFAPI_LEVEL_BATCH:
            if (m_nCurrentLevel != KCBOFAPI_LEVEL_BATCH) return FALSE;
            if (!OnEndProcessBatch()) return FALSE;
            m_nCurrentLevel = -1;
            m_strBatchLevelName.Empty();
            m_strBatchLevelID.Empty();
            return TRUE;

        case KCBOFAPI_LEVEL_DOCUMENT:
            if (m_nCurrentLevel != KCBOFAPI_LEVEL_DOCUMENT) return FALSE;
            if (!OnEndProcessDocument()) return FALSE;
            m_nCurrentLevel = KCBOFAPI_LEVEL_BATCH;
            m_strDocumentLevelName.Empty();
            m_strDocumentLevelID.Empty();
            return TRUE;

        case KCBOFAPI_LEVEL_PAGE:
            if (m_nCurrentLevel != KCBOFAPI_LEVEL_PAGE) return FALSE;
            if (!OnEndProcessPage()) return FALSE;
            m_nCurrentLevel = KCBOFAPI_LEVEL_DOCUMENT;
            m_strPageLevelName.Empty();
            m_strPageLevelID.Empty();
            return TRUE;

        case KCBOFAPI_LEVEL_IMAGE:
            if (m_nCurrentLevel != KCBOFAPI_LEVEL_IMAGE) return FALSE;
            if (!OnEndProcessImage()) return FALSE;
            m_nCurrentLevel = KCBOFAPI_LEVEL_PAGE;
            m_strImageLevelName.Empty();
            m_strImageLevelID.Empty();
            return TRUE;
    }

    //
    return FALSE;
}

BOOL inline CKCBOFACIBasicImpl::OnBeginProcessBatch()
{
    return TRUE;
}

BOOL inline CKCBOFACIBasicImpl::OnBeginProcessDocument()
{
    return TRUE;
}

BOOL inline CKCBOFACIBasicImpl::OnBeginProcessPage()
{
    return TRUE;
}

BOOL inline CKCBOFACIBasicImpl::OnBeginProcessImage()
{
    return TRUE;
}

BOOL inline CKCBOFACIBasicImpl::OnAddImageFile(LPCTSTR lpszImageFilePath, KCBOFAPI_IMAGEINFO& info)
{
    return TRUE;
}

BOOL inline CKCBOFACIBasicImpl::OnEndProcessImage()
{
    return TRUE;
}

BOOL inline CKCBOFACIBasicImpl::OnEndProcessPage()
{
    return TRUE;
}

BOOL inline CKCBOFACIBasicImpl::OnEndProcessDocument()
{
    return TRUE;
}

BOOL inline CKCBOFACIBasicImpl::OnEndProcessBatch()
{
    return TRUE;
}

void inline CKCBOFACIBasicImpl::OnAbortProcess()
{
}
