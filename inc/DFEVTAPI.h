/*!
	@file	DFEVTAPI.h
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2007 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-10-10
*/

#pragma once

#include "DFShellAPI.h"

//	DFEVTAPI
//******************************************************************************
#define	DFEVTAPI											0x0000C413

//	DFEVTAPI_VERSION
//******************************************************************************
#define	DFEVTAPI_VERSION									0x00010000

//	DFEVTAPI_LOGEVENT
//******************************************************************************
#define	DFEVTAPI_LOGEVENT_PROCNAME							_T("DFEVTAPI.LogEvent")
struct DFEVTAPI_LOGEVENT_PARAM{
	DFAPI_DATETIME_TYPE				dtTimeStamp;			//!< [in]: time stamp
	DFAPI_TEXT128_TYPE				szEventName;			//!< [in]: event name
	DFAPI_TEXT1024_TYPE				szParameters;			//!< [in]: parameters
};
