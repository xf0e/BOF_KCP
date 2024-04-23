/*!
	@file	DFShellAPI.h
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-09-01
*/

#pragma once

#include "DFAPICommon.h"

//	DFSHELLAPI_VERSION
//******************************************************************************
#define	DFSHELLAPI_VERSION									0x00010000

//	DFSHELLAPI_PLUGIN_INFO
//******************************************************************************
struct DFSHELLAPI_PLUGIN_INFO{
	DFSHELLAPI_PLUGIN_INFO();

	//!	@name	data members
	//@{
	DWORD							m_dwSize;				//!< size of data structure
	DFAPI_VERSION_TYPE				m_ShellAPIVersion;		//!< shell API version
	DFAPI_TYPEID_TYPE				m_Type;					//!< API type ID
	DFAPI_VERSION_TYPE				m_APIVersion;			//!< API version
	DFAPI_VERSION_TYPE				m_Version;				//!< plugin version
	DFAPI_BUILDVERSION_TYPE			m_BuildVersion;			//!< plugin build version
	BOOL							m_bIsDebug;				//!< debug version
	//@}
};

//	DFSHELLAPI_PLUGIN_INFOEX
//******************************************************************************
struct DFSHELLAPI_PLUGIN_INFOEX:DFSHELLAPI_PLUGIN_INFO{
	DFSHELLAPI_PLUGIN_INFOEX();

	//!	@name	data members
	//@{
	DFAPI_TEXT256_TYPE				m_Name;					//!< plugin name
	DFAPI_TEXT256_TYPE				m_Description;			//!< plugin description
	DFAPI_TEXT256_TYPE				m_Copyright;			//!< plugin copyright information
	//@}
};

//	DFSHELLAPI_PROXY_INFO
//******************************************************************************
struct DFSHELLAPI_PROXY_INFO{
	DFSHELLAPI_PROXY_INFO();

	//!	@name	data members
	//@{
	DWORD							m_dwSize;				//!< size of data structure
	DFAPI_VERSION_TYPE				m_ShellAPIVersion;		//!< shell API version
	DFAPI_TYPEID_TYPE				m_Type;					//!< API type ID
	DFAPI_VERSION_TYPE				m_APIVersion;			//!< API version
	DFAPI_TEXT256_TYPE				m_Name;					//!< proxy name
	DFAPI_TEXT256_TYPE				m_Description;			//!< proxy description
	DFAPI_TEXT256_TYPE				m_Copyright;			//!< proxy copyright information
	DFAPI_TEXT128_TYPE				m_Language;				//!< proxy language
	DFAPI_TEXTPATH_TYPE				m_AppRootPath;			//!< application root path
	DFAPI_TEXTPATH_TYPE				m_PluginsSharedPath;	//!< plugins shared path
    DWORD							m_dwReserved[16];		//!< reserved
	//@}
};

//	DFSHELLAPI_SESSION_INFO
//******************************************************************************
struct DFSHELLAPI_SESSION_INFO{
	DFSHELLAPI_SESSION_INFO();
	virtual ~DFSHELLAPI_SESSION_INFO();

	//!	@name	data members
	//@{
	DWORD							m_dwSize;				//!< size of data structure
	DFSHELLAPI_PROXY_INFO*			m_pProxyInfo;			//!< copy of proxy information
	DWORD64							m_dwCreatorSignature;	//!< session creator signature
	LPVOID							m_Reserved[64];			//!< reserved
	//@}

	//!	@name	methods
	//@{
	void ResetProxyInfo();
	BOOL SetProxyInfo(DFSHELLAPI_PROXY_INFO* pProxyInfo);
	//@}
};

//	DFSHELLAPI_GETINFO
//******************************************************************************
/*!
	BOOL GetInfo(DFSHELLAPI_PLUGIN_INFO* pPluginInfo, DWORD* pSize);
	Parameters:
		Usage 1: Retrieve the size of plugin information data structure.
		pPluginInfo[in]			NULL.
		pSize[out]				If it is NULL, it will return FALSE.
								Otherwise, after the call, it will be filled with
								the required size of plugin information data structure in
								bytes.  Routine will return TRUE.
	
		Usage 2: Retrieve the plugin information.
		pPluginInfo[in/out]		Pointer to the receiving buffer that receives the
								plugin information.  It should not be NULL.
		pSize[in]				If it is NULL, it will return FALSE.
								Otherwise, it specifies the size of receiving buffer.
								If the receiving buffer is big enough to contain the
								plugin information, after the call, receiving buffer
								will be filled and it will return TRUE.  The actual 
								size could be obtained from m_dwSize member in data 
								structure.
								If the receiving buffer is too small, it will returns
								FALSE.
	Return:
		See above.
*/
#define	DFSHELLAPI_GETINFO_PROCNAME							"DFSHELLAPI_GETINFO"
typedef BOOL (*DFSHELLAPI_GETINFO_PROC)(DFSHELLAPI_PLUGIN_INFO*, DWORD*);

//	DFSHELLAPI_OPENSESSION
//******************************************************************************
/*!
	DFAPI_SESSION OpenSession(DFSHELLAPI_PROXY_INFO* pProxyInfo);
	Parameters:
		pProxyInfo[in]			Proxy information.  
								Should not be NULL, otherwise, it will return NULL.
	Return:
		When proxy is compatible with the plugin, it will return a session handle.  
		Otherwise, it returns NULL.

		"Compatible" means any of following rules should be met:
		- Proxy and plugin are in same API, says they have same API type ID.  
		  Or proxy type is unknown, that the proxy is to retrieve plugin information only;
		- Proxy's Shell API version is equal to or higher than plugin's Shell API version;
		- Proxy's API version is equal to or higher than plugin's API version.
*/
#define	DFSHELLAPI_OPENSESSION_PROCNAME						"DFSHELLAPI_OPENSESSION"
typedef DFAPI_SESSION (*DFSHELLAPI_OPENSESSION_PROC)(DFSHELLAPI_PROXY_INFO*);

//	DFSHELLAPI_GETINFOEX
//******************************************************************************
/*!	
	BOOL GetInfoEx(DFAPI_SESSION session, DFSHELLAPI_PLUGIN_INFOEX* pPluginInfoEx, DWORD* pSize);
	Parameters:
		Usage 1: Retrieve the size of plugin extended information data structure.
		session[in]				Session handle created by OpenSession().
		pPluginInfoEx[in]		NULL.
		pSize[out]				If it is NULL, it will return FALSE.
								Otherwise, after the call, it will be filled with
								the required size of plugin extended information data structure in
								bytes.  Routine will return TRUE.
	
		Usage 2: Retrieve the plugin extended information.
		session[in]				Session handle created by OpenSession().
		pPluginInfoEx[in/out]	Pointer to the receiving buffer that receives the
								plugin extended information.  It should not be NULL.
		pSize[in]				If it is NULL, it will return FALSE.
								Otherwise, it specifies the size of receiving buffer.
								If the receiving buffer is big enough to contain the
								plugin exteneded information, after the call, receiving
								buffer will be filled and it will return TRUE.  The actual 
								size could be obtained from m_dwSize member in data 
								structure.
								If the receiving buffer is too small, it will returns
								FALSE.
	Return:
		If it is not a valid session, it will return FALSE.  Otherwise, see above.
*/
#define	DFSHELLAPI_GETINFOEX_PROCNAME						"DFSHELLAPI_GETINFOEX"
typedef BOOL (*DFSHELLAPI_GETINFOEX_PROC)(DFAPI_SESSION, DFSHELLAPI_PLUGIN_INFOEX*, DWORD*);

//	DFSHELLAPI_GETPROCADDRESS
//******************************************************************************
/*!
	BOOL GetProcAddress(DFAPI_SESSION session, LPCTSTR lpszProcName, LPVOID* lpProcAddress);
	Parameters:
		session[in]				Session handle created by OpenSession().
		lpszProcName[in]		Name of API routine to be retrieved.
		lpProcAddress[out]		When API routine name had been found, it will be filled with
								address of the API routine and function returns TRUE.  Otherwise,
								it will returns FALSE.
	Return:
		If it is not a valid session, it will return FALSE.  Otherwise, see above.
*/
#define	DFSHELLAPI_GETPROCADDRESS_PROCNAME					"DFSHELLAPI_GETPROCADDRESS"
typedef BOOL (*DFSHELLAPI_GETPROCADDRESS_PROC)(DFAPI_SESSION, LPCTSTR, LPVOID*);

//	DFSHELLAPI_CLOSESESSION
//******************************************************************************
/*!
	BOOL CloseSession(DFAPI_SESSION session);
	Parameters:
		session[in]				Session handle created by OpenSession().
	Return
		If it is not a valid session, it will return FALSE.  Otherwise, the session will be
		discarded and expired after the call and it will return TRUE.
*/
#define	DFSHELLAPI_CLOSESESSION_PROCNAME					"DFSHELLAPI_CLOSESESSION"
typedef BOOL (*DFSHELLAPI_CLOSESESSION_PROC)(DFAPI_SESSION);

//******************************************************************************
#include "DFShellAPI.inl"
