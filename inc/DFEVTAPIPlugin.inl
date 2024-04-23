/*!
	@file	DFEVTAPIPlugin.inl
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2007 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-10-10
*/

#pragma once

#include "DFEVTAPIPlugin.h"

//	TDFEVTAPIPlugin
//******************************************************************************

//	plugin information
//------------------------------------------------------------------------------
template <class SESSIONCLASS, class PLUGINCLASS>
DFAPI_TYPEID_TYPE TDFEVTAPIPlugin<SESSIONCLASS, PLUGINCLASS>::g_Type(DFEVTAPI);

template <class SESSIONCLASS, class PLUGINCLASS>
DFAPI_VERSION_TYPE TDFEVTAPIPlugin<SESSIONCLASS, PLUGINCLASS>::g_APIVersion(DFEVTAPI_VERSION);

//	session
//------------------------------------------------------------------------------
template <class SESSIONCLASS, class PLUGINCLASS>
void TDFEVTAPIPlugin<SESSIONCLASS, PLUGINCLASS>::OnOpenSession(DFAPI_SESSION session)
{
}

//	shell API
//------------------------------------------------------------------------------
template <class SESSIONCLASS, class PLUGINCLASS>
BOOL TDFEVTAPIPlugin<SESSIONCLASS, PLUGINCLASS>::GetProcAddress(DFAPI_SESSION session, LPCTSTR lpszProcName, LPVOID* lpProcAddress)
{
	DFAPI_PLUGIN_BEGIN_GPA()
		//DFEVTAPI
		DFAPI_PLUGIN_GPA(DFEVTAPI_LOGEVENT_PROCNAME, DFEVTAPI_LogEvent)
	DFAPI_PLUGIN_END_GPA()
}
