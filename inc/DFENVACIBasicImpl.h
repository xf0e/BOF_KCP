/*!
	@file	DFENVACIBasicImpl.h
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-09-01
*/

#pragma once

#include "DFENVACIImpl.h"

//	Helper Macros
//******************************************************************************
#define	DFENVACI_PLUGIN_TV_SET(index, procname)									\
protected:																		\
	BOOL procname(LPCTSTR lpszValue, BOOL bReadOnly = TRUE){					\
		SetTextVariableReadOnly(index, bReadOnly);								\
		return SetTextVariable(index, lpszValue);								\
	}

#define	DFENVACI_PLUGIN_TV_GET(index, procname)									\
protected:																		\
	BOOL procname(CString& strValue){											\
		return GetTextVariable(index, strValue);								\
	}

#define	DFENVACI_PLUGIN_DV_SET(index, procname, type)							\
protected:																		\
	BOOL procname(##type value, BOOL bReadOnly = TRUE){							\
		DWORD64 v;																\
		int len = min(sizeof(value), sizeof(v));								\
		memcpy((char*)&v, (char*)&value, len);									\
		return SetDataVariable(index,  v);										\
	}

#define	DFENVACI_PLUGIN_DV_GET(index, procname, type)							\
protected:																		\
	BOOL procname(##type value){												\
		DWORD64 v = 0;															\
		if (!GetDataVariable(index, v)) return FALSE;							\
		int len= min(sizeof(value), sizeof(v));									\
		memcpy((char*)&value, (char*)&v, len);									\
		return TRUE;															\
	}

//	CDFENVACIBasicImpl
//******************************************************************************
class CDFENVACIBasicImpl:public CDFENVACIImpl{
protected:
	CDFENVACIBasicImpl();
	~CDFENVACIBasicImpl();

	//!	@name	flags definition
	//@{
protected:
	enum{
		flag_mask_readonly = 0x01,
	};
	//@}

	//!	@name	text variables
	//@{
protected:
	int								m_nTextVariableCount;	//!< number of text variables
	DFAPI_TEXT4096_TYPE*			m_pTextVariables;		//!< text variables
	LPBYTE							m_pTextVariablesFlags;	//!< text variables flags
	void InitializeTextVariables(int nCount);
	BOOL SetTextVariable(int nIndex, DFAPI_TEXT4096_TYPE& szValue);
	BOOL SetTextVariable(int nIndex, LPCTSTR lpszValue);
	BOOL GetTextVariable(int nIndex, DFAPI_TEXT4096_TYPE& szValue);
	BOOL GetTextVariable(int nIndex, CString& strValue);
	BOOL SetTextVariableReadOnly(int nIndex, BOOL bReadOnly = TRUE);
	BOOL GetTextVariableReadOnly(int nIndex, BOOL& bReadOnly);
	void CleanupTextVariables();
	//@}

	//!	@name	data variables
	//@{
protected:
	int								m_nDataVariableCount;	//!< number of data variables
	DWORD64*						m_pDataVariables;		//!< data variables
	LPBYTE							m_pDataVariablesFlags;	//!< data variables flags
	void InitializeDataVariables(int nCount);
	BOOL SetDataVariable(int nIndex, DWORD64 dwValue);
	BOOL GetDataVariable(int nIndex, DWORD64& dwValue);
	BOOL SetDataVariableReadOnly(int nIndex, BOOL bReadOnly = TRUE);
	BOOL GetDataVariableReadOnly(int nIndex, BOOL& bReadOnly);
	void CleanupDataVariables();
	//@}

	//!	@name	helper window handle
	//@{
protected:
	HWND							m_hHelperWindowHandle;	//!< helper window handle
	void SetHelperWindowHandle(HWND hWnd);
	HWND GetHelperWindowHandle();
	//@}

	//!	@name	ENVACI
	//@{
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(ENVACI_SetProxyLanguage)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(ENVACI_SetAppRootPath)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(ENVACI_SetPluginsSharedPath)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(ENVACI_SetTextVariable)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(ENVACI_GetTextVariable)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(ENVACI_SetDataVariable)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(ENVACI_GetDataVariable)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(ENVACI_SetHelperWindowHandle)
	DFAPI_PLUGIN_DECLARE_STD_INTERFACE(ENVACI_GetHelperWindowHandle)
	//@}
};

//******************************************************************************
#include "DFENVACIBasicImpl.inl"

