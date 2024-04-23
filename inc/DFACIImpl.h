/*!
	@file	DFACIImpl.h
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-09-01
*/

#pragma once

#include "DFShellAPI.h"
#include "DFAPIPluginHelper.h"

//	SDFACIImpl
//******************************************************************************
class SDFACIImpl{
	//!	@name	session
	//@{
protected:
	static DFSHELLAPI_SESSION_INFO* ACI_GetSession(DFAPI_SESSION session);
	static void ACI_UpdateSession(DFAPI_SESSION session, int nACIType, LPVOID pACI);
	static LPVOID ACI_CheckSession(DFAPI_SESSION session, int nACIType);
	//@}

	//!	@name	proxy environment
	//@{
protected:
	static DFSHELLAPI_PROXY_INFO* ACI_GetProxyInfo(DFAPI_SESSION session);
	static BOOL ACI_GetProxyLanguage(DFAPI_SESSION session, DFAPI_TEXT128_TYPE& szLanguage);
	static BOOL ACI_GetAppRootPath(DFAPI_SESSION session, DFAPI_TEXTPATH_TYPE& szPath);
	static BOOL ACI_GetPluginsSharedPath(DFAPI_SESSION session, DFAPI_TEXTPATH_TYPE& szPath);
	static BOOL ACI_GetReservedData(DFAPI_SESSION session, int nIndex, DWORD& dwData);
	//@}
};

//******************************************************************************
#include "DFACIImpl.inl"