/*!
	@file	KCBOFAPI.h
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2007 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-11-07
*/

#pragma once

#include "DFShellAPI.h"

//	KCBOFAPI
//******************************************************************************
#define	KCBOFAPI											0x00007DCE

//	KCBOFAPI_VERSION
//******************************************************************************
#define	KCBOFAPI_VERSION									0x00010000

//	KCBOFAPI_LEVEL
//******************************************************************************
#define	KCBOFAPI_LEVEL_IMAGE								0x00000001		//!< image level
#define	KCBOFAPI_LEVEL_PAGE									0x00000002		//!< page level
#define	KCBOFAPI_LEVEL_DOCUMENT								0x00000003		//!< document level
#define	KCBOFAPI_LEVEL_BATCH								0x00000004		//!< batch level

//	KCBOFAPI_IMAGESIDE
//******************************************************************************
#define	KCBOFAPI_IMAGESIDE_UNKNOWN							0x0000			//!< unknown
#define	KCBOFAPI_IMAGESIDE_FRONT							0x0001			//!< front side
#define	KCBOFAPI_IMAGESIDE_REAR								0x0002			//!< rear side
#define	KCBOFAPI_IMAGESIDE_BOTH								0x0003			//!< both sides, eg. merged image with both sides

//	KCBOFAPI_IMAGETYPE
//******************************************************************************
#define	KCBOFAPI_IMAGETYPE_UNKNOWN							0x0000			//!< unknown
#define	KCBOFAPI_IMAGETYPE_BITONAL							0x0001			//!< bitonal image
#define	KCBOFAPI_IMAGETYPE_GRAYSCALE						0x0002			//!< grayscale image
#define	KCBOFAPI_IMAGETYPE_COLOR							0x0003			//!< color image


//	KCBOFAPI_IMAGEINFO
//******************************************************************************
struct KCBOFAPI_IMAGEINFO{
	DWORD							dwID;					//!< image ID, start from 1
	WORD							wScannedSide;			//!< original side, see KCBOFAPI_IMAGESIDE
	WORD							wCurrentSide;			//!< current side, see KCBOFAPI_IMAGESIDE
	DWORD							dwHWPartNo;				//!< hardware part number, splitted by hardware
	DWORD							dwSWPartNo;				//!< software part number, splitted by software

	WORD							wImageType;				//!< image type, see KCBOFAPI_IMAGETYPE
	DWORD							dwImageSeq;				//!< image sequence, start from 1 for every document
	DWORD							dwPageSeq;				//!< page sequence, start from 1 for every document
	DWORD							dwDocumentSeq;			//!< document sequence, start from 1 for every batch
								
	BOOL							bIAInfo;				//!< true if IA information is available, and following items can be used.
	WORD							wIALevel;				//!< IA Info: Image Address level
	DFAPI_TEXT32_TYPE				szIAFixed;				//!< IA Info: Fixed field
	DFAPI_TEXT32_TYPE				szIALevel1;				//!< IA Info: Level 1
	DFAPI_TEXT32_TYPE				szIALevel2;				//!< IA Info: Level 2
	DFAPI_TEXT32_TYPE				szIALevel3;				//!< IA Info: Level 3
	DFAPI_TEXT32_TYPE				szIAEntire;				//!< IA Info: Entire Image Address
	DFAPI_TEXT32_TYPE				szPrintString;			//!< Print string

	DWORD							dwFlags;				//!< flags, reserved
};

//	KCBOFAPI_CLEARINDEXKEY
//******************************************************************************
#define	KCBOFAPI_CLEARINDEXKEY_PROCNAME						_T("KCBOFAPI.ClearIndexKey")
struct KCBOFAPI_CLEARINDEXKEY_PARAM{
	__int32							nLevel;					//!< [in]: level, see KCBOFAPI_LEVEL
};

//	KCBOFAPI_ADDINDEXKEY
//******************************************************************************
#define	KCBOFAPI_ADDINDEXKEY_PROCNAME						_T("KCBOFAPI.AddIndexKey")
struct KCBOFAPI_ADDINDEXKEY_PARAM{
	__int32							nLevel;					//!< [in]: level, see KCBOFAPI_LEVEL
	DFAPI_TEXT128_TYPE				szIndexKey;				//!< [in]: index key
};

//	KCBOFAPI_CLEARINDEXVALUE
//******************************************************************************
#define	KCBOFAPI_CLEARINDEXVALUE_PROCNAME					_T("KCBOFAPI.ClearIndexValue")
struct KCBOFAPI_CLEARINDEXVALUE_PARAM{
	__int32							nLevel;					//!< [in]: level, see KCBOFAPI_LEVEL
};

//	KCBOFAPI_SETINDEXVALUE
//******************************************************************************
#define	KCBOFAPI_SETINDEXVALUE_PROCNAME						_T("KCBOFAPI.SetIndexValue")
struct KCBOFAPI_SETINDEXVALUE_PARAM{
	__int32							nLevel;					//!< [in]: level, see KCBOFAPI_LEVEL
	DFAPI_TEXT128_TYPE				szIndexKey;				//!< [in]: index key
	DFAPI_TEXT4096_TYPE				szIndexValue;			//!< [in]: index value
};

//	KCBOFAPI_BEGINPROCESS
//******************************************************************************
#define	KCBOFAPI_BEGINPROCESS_PROCNAME						_T("KCBOFAPI.BeginProcess")
struct KCBOFAPI_BEGINPROCESS_PARAM{
	__int32							nLevel;					//!< [in]: level, see KCBOFAPI_LEVEL
	DFAPI_TEXT128_TYPE				szLevelName;			//!< [in]: level name, eg. "image", "page", "document", etc.
	DFAPI_TEXT128_TYPE				szLevelID;				//!< [in]: level ID, eg. image ID, page ID, document ID, etc.
};

//	KCBOFAPI_ADDIMAGEFILE
//******************************************************************************
#define	KCBOFAPI_ADDIMAGEFILE_PROCNAME						_T("KCBOFAPI.AddImageFile")
struct KCBOFAPI_ADDIMAGEFILE_PARAM{
	KCBOFAPI_IMAGEINFO				info;					//!< [in]: image information
	DFAPI_TEXTPATH_TYPE				szImageFilePath;		//!< [in]: image file path
};

//	KCBOFAPI_ENDPROCESS
//******************************************************************************
#define	KCBOFAPI_ENDPROCESS_PROCNAME						_T("KCBOFAPI.EndProcess")
struct KCBOFAPI_ENDPROCESS_PARAM{
	__int32							nLevel;					//!< [in]: level, see KCBOFAPI_LEVEL
};

//	KCBOFAPI_ABORTPROCESS
//******************************************************************************
#define	KCBOFAPI_ABORTPROCESS_PROCNAME						_T("KCBOFAPI.AbortProcess")
struct KCBOFAPI_ABORTPROCESS_PARAM{
};

//	DFENVACI - Variables
//******************************************************************************
#define	KCBOFAPI_TV_OUTPUTFOLDERPATH						0		//!< output folder path
#define	KCBOFAPI_TV_OUTPUTLISTFILEPATH						1		//!< output list file path
#define	KCBOFAPI_TV_JOBNAME									2		//!< job name
#define	KCBOFAPI_TV_USERNAME								3		//!< user name
#define	KCBOFAPI_TV_WORKSTATIONNAME							4		//!< work station name

#define	KCBOFAPI_DV_WORKSTATIONID							0		//!< workstation ID
#define	KCBOFAPI_DV_CREATETIMESTAMP							1		//!< batch creation time stamp
#define	KCBOFAPI_DV_PROCESSTIMESTAMP						2		//!< batch process time stamp
#define	KCBOFAPI_DV_FIRSTDOCUMENTID							3		//!< first document ID
#define	KCBOFAPI_DV_LASTDOCUMENTID							4		//!< last document ID
#define	KCBOFAPI_DV_FRONTIMAGECOUNT							5		//!< front image count
#define	KCBOFAPI_DV_BLANKFRONTIMAGECOUNT					6		//!< blank front image count
#define	KCBOFAPI_DV_RESCANNEDFRONTIMAGECOUNT				7		//!< rescanned front image count
#define	KCBOFAPI_DV_DELETEDFRONTIMAGECOUNT					8		//!< deleted front image count
#define	KCBOFAPI_DV_REARIMAGECOUNT							9		//!< rear image count
#define	KCBOFAPI_DV_BLANKREARIMAGECOUNT						10		//!< blank rear image count
#define	KCBOFAPI_DV_RESCANNEDREARIMAGECOUNT					11		//!< rescanned rear image count
#define	KCBOFAPI_DV_DELETEDREARIMAGECOUNT					12		//!< deleted rear image count
