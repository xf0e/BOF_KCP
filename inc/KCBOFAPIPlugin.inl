/*!
	@file	KCBOFAPIPlugin.inl
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2007 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-11-07
*/

#pragma once

#include "KCBOFAPIPlugin.h"

//	TKCBOFAPIPlugin
//******************************************************************************

//	plugin information
//------------------------------------------------------------------------------
template <class SESSIONCLASS, class PLUGINCLASS>
DFAPI_TYPEID_TYPE TKCBOFAPIPlugin<SESSIONCLASS, PLUGINCLASS>::g_Type(KCBOFAPI);

template <class SESSIONCLASS, class PLUGINCLASS>
DFAPI_VERSION_TYPE TKCBOFAPIPlugin<SESSIONCLASS, PLUGINCLASS>::g_APIVersion(KCBOFAPI_VERSION);

//	session
//------------------------------------------------------------------------------
template <class SESSIONCLASS, class PLUGINCLASS>
void TKCBOFAPIPlugin<SESSIONCLASS, PLUGINCLASS>::OnOpenSession(DFAPI_SESSION session)
{
	//DFENVACI
	CDFENVACIImpl::OnOpenSession(session);

	//DFERRACI
	CDFERRACIImpl::OnOpenSession(session);

	//DFCFGACI
	CDFCFGACIImpl::OnOpenSession(session);
}

//	shell API
//------------------------------------------------------------------------------
template <class SESSIONCLASS, class PLUGINCLASS>
BOOL TKCBOFAPIPlugin<SESSIONCLASS, PLUGINCLASS>::GetProcAddress(DFAPI_SESSION session, LPCTSTR lpszProcName, LPVOID* lpProcAddress)
{
	DFAPI_PLUGIN_BEGIN_GPA()
		//KCBOFAPI
		DFAPI_PLUGIN_GPA(KCBOFAPI_CLEARINDEXKEY_PROCNAME, KCBOFAPI_ClearIndexKey)
		DFAPI_PLUGIN_GPA(KCBOFAPI_ADDINDEXKEY_PROCNAME, KCBOFAPI_AddIndexKey)
		DFAPI_PLUGIN_GPA(KCBOFAPI_CLEARINDEXVALUE_PROCNAME, KCBOFAPI_ClearIndexValue)
		DFAPI_PLUGIN_GPA(KCBOFAPI_SETINDEXVALUE_PROCNAME, KCBOFAPI_SetIndexValue)
		DFAPI_PLUGIN_GPA(KCBOFAPI_BEGINPROCESS_PROCNAME, KCBOFAPI_BeginProcess)
		DFAPI_PLUGIN_GPA(KCBOFAPI_ADDIMAGEFILE_PROCNAME, KCBOFAPI_AddImageFile)
		DFAPI_PLUGIN_GPA(KCBOFAPI_ENDPROCESS_PROCNAME, KCBOFAPI_EndProcess)
		DFAPI_PLUGIN_GPA(KCBOFAPI_ABORTPROCESS_PROCNAME, KCBOFAPI_AbortProcess)

		//DFENVACI
		if (CDFENVACIImpl::GetProcAddress(lpszProcName, lpProcAddress)) return TRUE;
		
		//DFERRACI
		if (CDFERRACIImpl::GetProcAddress(lpszProcName, lpProcAddress)) return TRUE;

		//DFCFGACI
		if (CDFCFGACIImpl::GetProcAddress(lpszProcName, lpProcAddress)) return TRUE;
	DFAPI_PLUGIN_END_GPA()
}
