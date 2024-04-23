/*!
	@file	MyPlugin.h
	@author	Edmond
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2007-04-03
*/

#pragma once

#include "afxtempl.h"
#include "txtfilewriter.h"
#include "MyCFGACIData.h"
#include "KCBOFAPIPlugin.h"
#include "KCADVBOFAPI.h"
// CMyPluginSession
//******************************************************************************
class CMyPlugin;
typedef class TDFShellAPIPluginSession<CMyPlugin> CMyPluginSession;
enum ImgState{
	IS_NONE = 0,
	IS_SET_MULTI,
	IS_START_MULTI,
};

//	DFAPI_PLUGIN_STD_INTERFACE
//******************************************************************************
#define	DFAPI_PLUGIN_STD_INTERFACE_EE(classname, procname)							\
public:																			\
	static BOOL __##procname(DFAPI_SESSION session, LPVOID param){				\
	classname* pThis = (classname*) CheckSession(session);					\
	if (pThis == NULL) return FALSE;										\
	return pThis->procname(session, param);									\
	}																			\
protected:																		\
	virtual BOOL procname(DFAPI_SESSION session, LPVOID param);


// CMyPlugin
//******************************************************************************
class CMyPlugin:public TKCBOFAPIPlugin<CMyPluginSession, CMyPlugin>{
public:
	CMyPlugin();
	~CMyPlugin();

	//! @name plugin information
	//@{
public:
	static DFAPI_VERSION_TYPE          g_Version;				//!< plugin version
	static DFAPI_BUILDVERSION_TYPE     g_BuildVersion;			//!< plugin build version
protected:
	virtual void GetPluginInfoEx(LPCTSTR lpszLanguage, CString& strName, CString& strDescription, CString& strCopyright);
	//@}

	//! @name DFCFGACI(Configuration ACI)
	//@{
protected:
	virtual CDFCFGACIBasicUI* CreateUI();
	virtual BOOL CFGACI_ValidateConfig(DFAPI_DATA_TYPE& config);
	virtual BOOL CFGACI_GetSupportedUIMode(BOOL& bSupportUI, BOOL& bSupportModalUI);
	virtual BOOL CFGACI_GetUISize(int& nWidth, int& nHeight);
	virtual BOOL CFGACI_ValidateUIConfig();
	
	virtual BOOL CFGACI_LoadConfig(LPCTSTR lpszFilePath, DFAPI_DATA_TYPE& config);
	virtual BOOL CFGACI_SaveConfig(LPCTSTR lpszFilePath, DFAPI_DATA_TYPE& config);
	//@}


	//! @name KCBOFAPI (BOF ACI)
	//@{
	//index  
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(KCBOFAPI_ClearIndexKey)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(KCBOFAPI_AddIndexKey)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(KCBOFAPI_ClearIndexValue)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(KCBOFAPI_SetIndexValue)

	//process
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(KCBOFAPI_BeginProcess)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(KCBOFAPI_AddImageFile)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(KCBOFAPI_EndProcess)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(KCBOFAPI_AbortProcess)

	//DFAPI_PLUGIN_DECLARE_STD_INTERFACE(KCBOFAPI_GetSupportedFileTypes)
	//DFAPI_PLUGIN_DECLARE_STD_INTERFACE(KCBOFAPI_SetOutputFileType)
	//DFAPI_PLUGIN_DECLARE_STD_INTERFACE(KCBOFAPI_ValidateConfig)
	//DFAPI_PLUGIN_DECLARE_STD_INTERFACE(KCBOFAPI_GetFilePathName)
	//DFAPI_PLUGIN_DECLARE_STD_INTERFACE(KCBOFAPI_SetFilePathName)

	DFAPI_PLUGIN_STD_INTERFACE_EE(CMyPlugin, KCBOFAPI_GetSupportedFileTypes)
	DFAPI_PLUGIN_STD_INTERFACE_EE(CMyPlugin, KCBOFAPI_SetOutputFileType)
	DFAPI_PLUGIN_STD_INTERFACE_EE(CMyPlugin, KCBOFAPI_ValidateConfig)
	DFAPI_PLUGIN_STD_INTERFACE_EE(CMyPlugin, KCBOFAPI_GetFilePathName)
	DFAPI_PLUGIN_STD_INTERFACE_EE(CMyPlugin, KCBOFAPI_SetFilePathName)

	//extended API

	//@}

	//! @name support data of implementation of index engine
	//@{
protected:
	struct Index_Pair{
		int         nLevel;
		CString     strKey;
		CString     strValue;
	};
	CList<Index_Pair, Index_Pair&>    m_lstIndex;
public:
	BOOL GetProcAddress(DFAPI_SESSION session, LPCTSTR lpszProcName, LPVOID* lpProcAddress);

	void RetrieveIndex( OUT CStringArray& arrLables, OUT CStringArray& arrValues, DWORD level = KCBOFAPI_LEVEL_DOCUMENT);
	//@}

	//!	@name	implementation of process engine
	//@{
protected:
	CString							m_strBatchLevelName;
	CString							m_strDocumentLevelName;
	CString							m_strPageLevelName;
	CString							m_strImageLevelName;
	CString							m_strBatchLevelID;    // Batch Level ID(Batch name)
	CString							m_strDocumentLevelID;
	CString							m_strPageLevelID;
	CString							m_strImageLevelID;
	int								m_nCurrentLevel;

	BOOL BeginProcess(int nLevel, LPCTSTR lpszLevelName, LPCTSTR lpszLevelID);
	BOOL EndProcess(int nLevel);

	BOOL OnBeginProcessBatch();
	BOOL OnBeginProcessDocument();
	BOOL OnBeginProcessPage();
	BOOL OnBeginProcessImage();
	BOOL OnAddImageFile(LPCTSTR lpszImageFilePath, KCBOFAPI_IMAGEINFO& info);
	BOOL OnEndProcessImage();
	BOOL OnEndProcessPage();
	BOOL OnEndProcessDocument();
	BOOL OnEndProcessBatch();
	void OnAbortProcess();

	BOOL GetSupportedFileTypes(DWORD &dwFileTypeAll, DWORD &dwFileTypeBW, DWORD &dwFileTypeCG, DWORD &dwGroupModeAll, DWORD &dwGroupModeBW, DWORD &dwGroupModeCG);
	BOOL SetOutputFileType(DWORD dwFileTypeAll, DWORD dwFileTypeBW, DWORD dwFileTypeCG, DWORD dwGroupModeAll, DWORD dwGroupModeBW, DWORD dwGroupModeCG);
	BOOL ValidateConfig(DWORD dwSuccess, CString& strErrMsg);
	BOOL GetFilePathName(DWORD dwChannel, CString &strFilePathFormula);
	BOOL SetFilePathName(DWORD dwChannel, LPCTSTR lpszFilePathName);

	//@}

	//! @name ERRACI and Error handling
	//!{
protected:
	virtual BOOL GetErrorMsg(LPCTSTR lpszLanguage, DWORD dwErrCode, CString& strMsg);
	//!}

	
	//! @name data\function for process control
	//@{
protected:
	CTxtFileWriter				m_indexWriter;                 //Index File Writer
	CMyCFGACIData				m_data;						//Data struct to write/read GUI configuration data
	CString						m_strBatchDir;                 
	CString						m_strIndexFile;				// Index File Name
	int							m_nImageCounter;				// Image counter
	int							m_docCounter;					// document counter
	CStringArray				m_arrImages;					// for delete when abort

	CString						m_strErrorInfo;				//!< error information
	CString						m_strCurProcessFile;		//!< current processing file path
	CString						m_strCurProcessFolder;
	CString						m_docDirectoryPathName;	    //!< Path name to individual document.

	DWORD						m_dwFileType;

	//@}
};

  
