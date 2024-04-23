/*!
@file	KCADVBOFAPI.h
@author	Philip Wu (hanbing.wu@kodak.com)
@author	Copyright (C) 1998-2009 Eastman Kodak Company.
@author	All rights reserved.
@date	2009-02-05
*/
#pragma once
#include "KCBOFAPI.h"

#define KCBOFACI 4
//	KCADVBOFAPI_VERSION
//******************************************************************************
#define	KCADVBOFAPI_VERSION									0x00010002

//  KCBOFAPI_FILETYPE
//******************************************************************************
#define KCBOFAPI_FILETYPE_NONE                              0X00000000
#define KCBOFAPI_FILETYPE_TIFF                              0X00000001
#define KCBOFAPI_FILETYPE_PDF                               0X00000002
#define KCBOFAPI_FILETYPE_SPDF                              0X00000004
#define KCBOFAPI_FILETYPE_JPEG                              0X00000008
#define KCBOFAPI_FILETYPE_JPEG2000                          0X00000010
#define KCBOFAPI_FILETYPE_JBIG                              0X00000020
#define KCBOFAPI_FILETYPE_GIF                               0X00000040
#define KCBOFAPI_FILETYPE_PNG                               0X00000080
#define KCBOFAPI_FILETYPE_BMP                               0X00000100
#define KCBOFAPI_FILETYPE_TXT                               0X00000200
#define KCBOFAPI_FILETYPE_RTF                               0X00000400
#define KCBOFAPI_FILETYPE_DOC                               0X00000800
#define KCBOFAPI_FILETYPE_XML                               0X00001000
#define KCBOFAPI_FILETYPE_PDFD                              0X00002000

//  KCBOFAPI_GROUPMODE
//*******************************************************************************
#define KCBOFAPI_GROUPMODE_SINGLE                           0X00000000
#define KCBOFAPI_GROUPMODE_PAGE                             0X00000001
#define KCBOFAPI_GROUPMODE_DOCUMENT                         0X00000002
#define KCBOFAPI_GROUPMODE_BATCH                            0X00000004

//  KCBOFAPI_CHANNEL
//*****************************************************************************
#define KCBOFAPI_CHANNEL_ALL                                0X00000001
#define KCBOFAPI_CHANNEL_BW                                 0X00000002
#define KCBOFAPI_CHANNEL_CG                                 0X00000003

//	KCBOFAPI_CLEARINDEXKEY
//******************************************************************************
#define	KCBOFAPI_GETSUPPORTEDFILETYPES_PROCNAME						_T("KCBOFAPI.GetSupportedFileTypes")
struct KCBOFAPI_FILETYPES_PARAM{
    DWORD dwFileTypeAll;
    DWORD dwGroupModeAll;
    DWORD dwFileTypeCG;
    DWORD dwGroupModeCG;
    DWORD dwFileTypeBW;
    DWORD dwGroupModeBW;
};

//  KCBOFAPI_SETOUTPUTFILETYPE
//*******************************************************************************
#define KCBOFAPI_SETOUTPUTFILETYPE_PROCNAME                         _T("KCBOFAPI.SetOutputFileType")
#define KCBOFAPI_VALIDATECONFIG_PROCNAME                         _T("KCBOFAPI.ValidateConfig")
struct KCBOFAPI_VALIDATECONFIG_PARAM{
    DWORD bSuccess;
    DFAPI_TEXT512_TYPE szErrorMessage;
};
//  KCBOFAPI_SETGROUPMODE
//******************************************************************************
// #define KCBOFAPI_SETGROUPMODE_PROCNAME                              _T("KCBOFAPI.SetGroupMode")
// struct KCBOFAPI_SETGROUPMODE_PARAM 
// {
//     DWORD dwGroupModeAll;
//     DWORD dwGroupModeCG;
//     DWORD dwGroupModeBW;
// };

//  KCBOFAPI_GETFILEPATHNAME
//*******************************************************************************
#define KCBOFAPI_GETFILEPATHNAME_PROCNAME                           _T("KCBOFAPI.GetFilePathName")
struct KCBOFAPI_FILEPATHNAME_PARAM 
{
    DWORD               dwChannel;
    DFAPI_TEXTPATH_TYPE szPathName;
};

//  KCBOFAPI_SETFILEPATHNAME
//*******************************************************************************
#define KCBOFAPI_SETFILEPATHNAME_PROCNAME                           _T("KCBOFAPI.SetFilePathName")
