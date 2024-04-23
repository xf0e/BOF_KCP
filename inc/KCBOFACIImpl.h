/*!
@file	KCBOFACIImpl.h
@author	Philip Wu (hanbing.wu@kodak.com)
@author	Copyright (C) 1998-2008 Eastman Kodak Company.
@author	All rights reserved.
@date	2009-02-18
*/

#pragma once

#include "KCADVBOFAPI.h"
#include "DFACIImpl.h"

//	CDFERRACIImpl
//******************************************************************************
class CKCBOFACIImpl:public SDFACIImpl{
    //!	@name	session
    //@{
protected:
    void OnOpenSession(DFAPI_SESSION session){
        ACI_UpdateSession(session, KCBOFACI, this);
    }

    static CKCBOFACIImpl* ACI_CheckSession(DFAPI_SESSION session){
        return (CKCBOFACIImpl*) SDFACIImpl::ACI_CheckSession(session, KCBOFACI);
    }

    static BOOL GetProcAddress(LPCTSTR lpszProcName, LPVOID* lpProcAddress){
        DFAPI_PLUGIN_GPA(KCBOFAPI_CLEARINDEXKEY_PROCNAME, KCBOFAPI_ClearIndexKey)
            DFAPI_PLUGIN_GPA(KCBOFAPI_ADDINDEXKEY_PROCNAME, KCBOFAPI_AddIndexKey)
            DFAPI_PLUGIN_GPA(KCBOFAPI_CLEARINDEXVALUE_PROCNAME, KCBOFAPI_ClearIndexValue)
            DFAPI_PLUGIN_GPA(KCBOFAPI_SETINDEXVALUE_PROCNAME, KCBOFAPI_SetIndexValue)
            DFAPI_PLUGIN_GPA(KCBOFAPI_BEGINPROCESS_PROCNAME, KCBOFAPI_BeginProcess)
            DFAPI_PLUGIN_GPA(KCBOFAPI_ADDIMAGEFILE_PROCNAME, KCBOFAPI_AddImageFile)
            DFAPI_PLUGIN_GPA(KCBOFAPI_ENDPROCESS_PROCNAME, KCBOFAPI_EndProcess)
            DFAPI_PLUGIN_GPA(KCBOFAPI_ABORTPROCESS_PROCNAME, KCBOFAPI_AbortProcess)
            DFAPI_PLUGIN_GPA(KCBOFAPI_GETSUPPORTEDFILETYPES_PROCNAME, KCBOFAPI_GetSupportedFileTypes)
            DFAPI_PLUGIN_GPA(KCBOFAPI_SETOUTPUTFILETYPE_PROCNAME, KCBOFAPI_SetOutputFileType)
            DFAPI_PLUGIN_GPA(KCBOFAPI_VALIDATECONFIG_PROCNAME, KCBOFAPI_ValidateConfig)
            DFAPI_PLUGIN_GPA(KCBOFAPI_GETFILEPATHNAME_PROCNAME, KCBOFAPI_GetFilePathName)
            DFAPI_PLUGIN_GPA(KCBOFAPI_SETFILEPATHNAME_PROCNAME, KCBOFAPI_SetFilePathName)
        DFAPI_PLUGIN_END_GPA()
    }
    //@}

    //!	@name	KCBOFAPI
    //@{
    DFAPI_PLUGIN_STD_INTERFACE_ACI(CKCBOFACIImpl, KCBOFAPI_ClearIndexKey)
    DFAPI_PLUGIN_STD_INTERFACE_ACI(CKCBOFACIImpl, KCBOFAPI_AddIndexKey)
    DFAPI_PLUGIN_STD_INTERFACE_ACI(CKCBOFACIImpl, KCBOFAPI_ClearIndexValue)
    DFAPI_PLUGIN_STD_INTERFACE_ACI(CKCBOFACIImpl, KCBOFAPI_SetIndexValue)
    DFAPI_PLUGIN_STD_INTERFACE_ACI(CKCBOFACIImpl, KCBOFAPI_BeginProcess)
    DFAPI_PLUGIN_STD_INTERFACE_ACI(CKCBOFACIImpl, KCBOFAPI_AddImageFile)
    DFAPI_PLUGIN_STD_INTERFACE_ACI(CKCBOFACIImpl, KCBOFAPI_EndProcess)
    DFAPI_PLUGIN_STD_INTERFACE_ACI(CKCBOFACIImpl, KCBOFAPI_AbortProcess)
    DFAPI_PLUGIN_STD_INTERFACE_ACI(CKCBOFACIImpl, KCBOFAPI_GetSupportedFileTypes)
    DFAPI_PLUGIN_STD_INTERFACE_ACI(CKCBOFACIImpl, KCBOFAPI_SetOutputFileType)
    DFAPI_PLUGIN_STD_INTERFACE_ACI(CKCBOFACIImpl, KCBOFAPI_ValidateConfig)
    DFAPI_PLUGIN_STD_INTERFACE_ACI(CKCBOFACIImpl, KCBOFAPI_GetFilePathName)
    DFAPI_PLUGIN_STD_INTERFACE_ACI(CKCBOFACIImpl, KCBOFAPI_SetFilePathName)
    //@}
};