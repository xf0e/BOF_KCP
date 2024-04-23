/*!
	@file	DFEVTAPIPlugin.h
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2007 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-10-10
*/

#pragma once

#include "DFEVTAPI.h"
#include "DFShellAPIPlugin.h"
#include "DFERRACIBasicImpl.h"
#include "DFCFGACIBasicImpl.h"

//	TDFEVTAPIPlugin
//******************************************************************************
template <class SESSIONCLASS, class PLUGINCLASS>
class TDFEVTAPIPlugin:public TDFShellAPIPlugin<SESSIONCLASS, PLUGINCLASS>{
	//!	@name	plugin information
	//@{
public:
	static DFAPI_TYPEID_TYPE		g_Type;					//!< API type ID
	static DFAPI_VERSION_TYPE		g_APIVersion;			//!< API version
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

	//!	@name	DFEVTAPI
	//@{
	DFAPI_PLUGIN_STD_INTERFACE(PLUGINCLASS, DFEVTAPI_LogEvent)
	//@}
};

//******************************************************************************
#include "DFEVTAPIPlugin.inl"
