/*!
@file	KCBOFAPIPluginEx.h
@author	Philip Wu (hanbing.wu@kodak.com)
@author	Copyright (C) 1998-2007 Eastman Kodak Company.
@author	All rights reserved.
@date	2009-02-13
*/

#pragma once

#include "KCADVBOFAPI.h"
#include "DFShellAPIPlugin.h"
#include "DFENVACIBasicImpl.h"
#include "DFERRACIBasicImpl.h"
#include "DFCFGACIBasicImpl.h"
#include "KCBOFACIBasicImpl.h"
//	TKCBOFAPIPluginEx
//******************************************************************************
template <class SESSIONCLASS, class PLUGINCLASS>
class TKCBOFAPIPluginEx:public TDFShellAPIPlugin<SESSIONCLASS, PLUGINCLASS>,
    public CDFENVACIBasicImpl,
    public CDFERRACIBasicImpl,
    public CDFCFGACIBasicImpl,
    public CKCBOFACIBasicImpl{

protected:
    TKCBOFAPIPluginEx();
    //!	@name	plugin information
    //@{
public:
    static DFAPI_TYPEID_TYPE		g_Type;					//!< API type ID
    static DFAPI_VERSION_TYPE		g_APIVersion;			//!< API version

    static DFAPI_VERSION_TYPE		g_Version;				//!< plugin version
    static DFAPI_BUILDVERSION_TYPE	g_BuildVersion;			//!< plugin build version
    //@}

    //!	@name	session
    //@{
public:
    virtual void OnOpenSession(DFAPI_SESSION session);
    virtual void OnCloseSession(DFAPI_SESSION session){}
    //@}

    //!	@name	shell API
    //@{
public:
    virtual BOOL GetProcAddress(DFAPI_SESSION session, LPCTSTR lpszProcName, LPVOID* lpProcAddress);
    virtual void CloseSession(DFAPI_SESSION session){}
    //@}

    //!	@name	DFENVACI - variables
    //@{
protected:
    DFENVACI_PLUGIN_TV_GET(KCBOFAPI_TV_OUTPUTFOLDERPATH, TV_GetOutputFolderPath)
    DFENVACI_PLUGIN_TV_GET(KCBOFAPI_TV_OUTPUTLISTFILEPATH, TV_GetListFilePath)
    DFENVACI_PLUGIN_TV_GET(KCBOFAPI_TV_JOBNAME, TV_GetJobName)
    DFENVACI_PLUGIN_TV_GET(KCBOFAPI_TV_USERNAME, TV_GetUserName)
    DFENVACI_PLUGIN_TV_GET(KCBOFAPI_TV_WORKSTATIONNAME,TV_GetWorkStationName)

    DFENVACI_PLUGIN_DV_GET(KCBOFAPI_DV_WORKSTATIONID, DV_GetWorkstationID, DWORD&)
    DFENVACI_PLUGIN_DV_GET(KCBOFAPI_DV_CREATETIMESTAMP, DV_GetCreateTimeStamp, DATE&)
    DFENVACI_PLUGIN_DV_GET(KCBOFAPI_DV_PROCESSTIMESTAMP, DV_GetProcessTimeStamp, DATE&)
    DFENVACI_PLUGIN_DV_GET(KCBOFAPI_DV_FIRSTDOCUMENTID, DV_GetFirstDocumentID, DWORD&)
    DFENVACI_PLUGIN_DV_GET(KCBOFAPI_DV_LASTDOCUMENTID, DV_GetLastDocumentID, DWORD&)
    DFENVACI_PLUGIN_DV_GET(KCBOFAPI_DV_FRONTIMAGECOUNT, DV_GetFrontImageCount, long&)
    DFENVACI_PLUGIN_DV_GET(KCBOFAPI_DV_BLANKFRONTIMAGECOUNT, DV_GetBlankFrontImageCount, long&)
    DFENVACI_PLUGIN_DV_GET(KCBOFAPI_DV_RESCANNEDFRONTIMAGECOUNT, DV_GetRescannedFrontImageCount, long&)
    DFENVACI_PLUGIN_DV_GET(KCBOFAPI_DV_DELETEDFRONTIMAGECOUNT, DV_GetDeletedFrontImageCount, long&)
    DFENVACI_PLUGIN_DV_GET(KCBOFAPI_DV_REARIMAGECOUNT, DV_GetRearImageCount, long&)
    DFENVACI_PLUGIN_DV_GET(KCBOFAPI_DV_BLANKREARIMAGECOUNT, DV_GetBlankRearImageCount, long&)
    DFENVACI_PLUGIN_DV_GET(KCBOFAPI_DV_RESCANNEDREARIMAGECOUNT, DV_GetRescannedRearImageCount, long&)
    DFENVACI_PLUGIN_DV_GET(KCBOFAPI_DV_DELETEDREARIMAGECOUNT, DV_GetDeletedRearImageCount, long&)
    //@}
    };

//******************************************************************************
#include "KCBOFAPIPluginEx.inl"
