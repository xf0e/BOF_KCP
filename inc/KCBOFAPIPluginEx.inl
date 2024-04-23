/*!
	@file	KCBOFAPIPluginEx.inl
	@author	Philip Wu (hanbing.wu@kodak.com)
	@author	Copyright (C) 1998-2007 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2009-02-13
*/

#pragma once

#include "KCBOFAPIPluginEx.h"

//	TKCBOFAPIPluginEx
//******************************************************************************

//	plugin information
//------------------------------------------------------------------------------
template <class SESSIONCLASS, class PLUGINCLASS>
DFAPI_TYPEID_TYPE TKCBOFAPIPluginEx<SESSIONCLASS, PLUGINCLASS>::g_Type(KCBOFAPI);

template <class SESSIONCLASS, class PLUGINCLASS>
DFAPI_VERSION_TYPE TKCBOFAPIPluginEx<SESSIONCLASS, PLUGINCLASS>::g_APIVersion(KCADVBOFAPI_VERSION);

template <class SESSIONCLASS, class PLUGINCLASS>
DFAPI_VERSION_TYPE TKCBOFAPIPluginEx<SESSIONCLASS, PLUGINCLASS>::g_Version;

template <class SESSIONCLASS, class PLUGINCLASS>
DFAPI_BUILDVERSION_TYPE TKCBOFAPIPluginEx<SESSIONCLASS, PLUGINCLASS>::g_BuildVersion;

template <class SESSIONCLASS, class PLUGINCLASS>
TKCBOFAPIPluginEx<SESSIONCLASS, PLUGINCLASS>::TKCBOFAPIPluginEx()
{
    //initialize DFENVACI variables
    InitializeTextVariables(20);
    InitializeDataVariables(20);

    //initialize index engine
    m_Index.SetCaseSensitive(FALSE);
};
//	session
//------------------------------------------------------------------------------
template <class SESSIONCLASS, class PLUGINCLASS>
void TKCBOFAPIPluginEx<SESSIONCLASS, PLUGINCLASS>::OnOpenSession(DFAPI_SESSION session)
{
	//DFENVACI
	CDFENVACIImpl::OnOpenSession(session);

	//DFERRACI
	CDFERRACIImpl::OnOpenSession(session);

	//DFCFGACI
	CDFCFGACIImpl::OnOpenSession(session);

    //KCBOFACI
    CKCBOFACIImpl::OnOpenSession(session);
}

//	shell API
//------------------------------------------------------------------------------
template <class SESSIONCLASS, class PLUGINCLASS>
BOOL TKCBOFAPIPluginEx<SESSIONCLASS, PLUGINCLASS>::GetProcAddress(DFAPI_SESSION session, LPCTSTR lpszProcName, LPVOID* lpProcAddress)
{
	DFAPI_PLUGIN_BEGIN_GPA()

	//DFENVACI
	if (CDFENVACIImpl::GetProcAddress(lpszProcName, lpProcAddress)) return TRUE;
		
	//DFERRACI
	if (CDFERRACIImpl::GetProcAddress(lpszProcName, lpProcAddress)) return TRUE;

	//DFCFGACI
	if (CDFCFGACIImpl::GetProcAddress(lpszProcName, lpProcAddress)) return TRUE;

    if (CKCBOFACIImpl::GetProcAddress(lpszProcName, lpProcAddress)) return TRUE;
	DFAPI_PLUGIN_END_GPA()
}