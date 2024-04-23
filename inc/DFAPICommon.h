/*!
	@file	DFAPICommon.h
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-09-01
*/

#pragma once

#include <windows.h>
#ifndef	_UNICODE
	#error DFAPI works with UNICODE only!
#endif	//_UNICODE

//	DFAPI_TEXTxxx_TYPE
//******************************************************************************
template <int TEXTLEN>
struct T_DFAPI_TEXT_TYPE{
	T_DFAPI_TEXT_TYPE();

	//!	@name	data members
	//@{
	WCHAR							m_text[TEXTLEN];
	//@}

	//!	@name	methods
	//@{
	void Clear();
	void Set(LPCTSTR lpszText);
	LPCTSTR operator=(LPCTSTR lpszText);
	BOOL SetEx(LPCTSTR lpszText);
	void Get(LPTSTR lpText, int nSize);
	LPCTSTR Get();
	operator LPCTSTR();
	//@}
};

typedef T_DFAPI_TEXT_TYPE<32>			DFAPI_TEXT32_TYPE;
typedef	T_DFAPI_TEXT_TYPE<64>			DFAPI_TEXT64_TYPE;
typedef	T_DFAPI_TEXT_TYPE<128>			DFAPI_TEXT128_TYPE;
typedef	T_DFAPI_TEXT_TYPE<256>			DFAPI_TEXT256_TYPE;
typedef	T_DFAPI_TEXT_TYPE<512>			DFAPI_TEXT512_TYPE;
typedef	T_DFAPI_TEXT_TYPE<1024>			DFAPI_TEXT1024_TYPE;
typedef	T_DFAPI_TEXT_TYPE<2048>			DFAPI_TEXT2048_TYPE;
typedef	T_DFAPI_TEXT_TYPE<4096>			DFAPI_TEXT4096_TYPE;
typedef	T_DFAPI_TEXT_TYPE<8192>			DFAPI_TEXT8192_TYPE;
typedef	T_DFAPI_TEXT_TYPE<16384>		DFAPI_TEXT16K_TYPE;
typedef	T_DFAPI_TEXT_TYPE<32768>		DFAPI_TEXT32K_TYPE;
typedef	T_DFAPI_TEXT_TYPE<65536>		DFAPI_TEXT64K_TYPE;
typedef	T_DFAPI_TEXT_TYPE<131072>		DFAPI_TEXT128K_TYPE;
typedef	T_DFAPI_TEXT_TYPE<262144>		DFAPI_TEXT256K_TYPE;
typedef	T_DFAPI_TEXT_TYPE<524288>		DFAPI_TEXT512K_TYPE;
typedef	T_DFAPI_TEXT_TYPE<1048576>		DFAPI_TEXT1M_TYPE;
typedef	T_DFAPI_TEXT_TYPE<2097152>		DFAPI_TEXT2M_TYPE;
typedef	T_DFAPI_TEXT_TYPE<4194304>		DFAPI_TEXT4M_TYPE;
typedef	T_DFAPI_TEXT_TYPE<512>			DFAPI_TEXTPATH_TYPE;

//	DFAPI_DATETIME_TYPE
//******************************************************************************
typedef double 							DFAPI_DATETIME_TYPE;

//	DFAPI_DATA_TYPE
//******************************************************************************
struct DFAPI_DATA_TYPE{
	DFAPI_DATA_TYPE();
	virtual ~DFAPI_DATA_TYPE();

	//!	@name	data members
	//@{
	HGLOBAL							m_hData;
	LPBYTE							m_pData;
	//@}

	//!	@name	data information
	//@{
	BOOL IsEmpty();
	DWORD GetSize();
	//@}

	//!	@name	allocate/free
	//@{
	BOOL Alloc(DWORD dwSize);
	BOOL ReAlloc(DWORD dwSize);
	void Free();
	//@}

	//!	@name	lock/unlock
	//@{
	LPBYTE Lock();
	void Unlock();
	//@}

	//!	@name	attach/detach
	//@{
	void Attach(HGLOBAL hFromData);
	HGLOBAL Detach();
	void Attach(DFAPI_DATA_TYPE& from);
	void Detach(DFAPI_DATA_TYPE& to);
	//@}

	//!	@name	copy
	//@{
	BOOL CopyFrom(DFAPI_DATA_TYPE& from);
	BOOL CopyTo(DFAPI_DATA_TYPE& to);
	//@}

	//!	@name	file
	//@{
	BOOL Save(LPCTSTR lpszFilePath);
	BOOL Load(LPCTSTR lpszFilePath);
	//@}
};

//	DFAPI_VERSION_TYPE
//******************************************************************************
struct DFAPI_VERSION_TYPE{
	DFAPI_VERSION_TYPE();
	DFAPI_VERSION_TYPE(DFAPI_VERSION_TYPE& o);
	DFAPI_VERSION_TYPE(DWORD dwVersion);
	DFAPI_VERSION_TYPE(WORD wMajor, WORD wMinor);

	//!	@name	data members
	//@{
	DWORD							m_dwVersion;
	//@}

	//!	@name	methods
	//@{
	DFAPI_VERSION_TYPE& operator=(DFAPI_VERSION_TYPE& o);
	DWORD operator=(DWORD dwVersion);
	BOOL IsCompatible(DFAPI_VERSION_TYPE& o);
	BOOL IsCompatible(DWORD dwVersion);
	void Set(WORD wMajor, WORD wMinor);
	void Get(WORD& wMajor, WORD& wMinor);
	//@}
};

//	DFAPI_BUILDVERSION_TYPE
//******************************************************************************
struct DFAPI_BUILDVERSION_TYPE{
	DFAPI_BUILDVERSION_TYPE();
	DFAPI_BUILDVERSION_TYPE(DFAPI_BUILDVERSION_TYPE& o);
	DFAPI_BUILDVERSION_TYPE(DWORD64 dwBuildVersion);
	DFAPI_BUILDVERSION_TYPE(DWORD dwMajor, DWORD dwMinor);

	//!	@name	data members
	//@{
	DWORD64							m_dwBuildVersion;
	//@}

	//!	@name	methods
	//@{
	DFAPI_BUILDVERSION_TYPE& operator=(DFAPI_BUILDVERSION_TYPE& o);
	DWORD64 operator=(DWORD64 dwBuildVersion);
	void Set(DWORD dwMajor, DWORD dwMinor);
	void Get(DWORD& dwMajor, DWORD& dwMinor);
	//@}
};

//	DFAPI_TYPEID_TYPE
//******************************************************************************
struct DFAPI_TYPEID_TYPE{
	DFAPI_TYPEID_TYPE();
	DFAPI_TYPEID_TYPE(DFAPI_TYPEID_TYPE& o);
	DFAPI_TYPEID_TYPE(DWORD dwTypeID);

	//!	@name	data members
	//@{
	enum{
		unknown = 0,
	};
	DWORD							m_dwTypeID;
	//@}

	//!	@name	methods
	//@{
	BOOL IsUnknown();
	BOOL IsType(DFAPI_TYPEID_TYPE& o, BOOL bAcceptUnknown = FALSE);
	BOOL IsType(DWORD dwTypeID, BOOL bAcceptUnknown = FALSE);
	DFAPI_TYPEID_TYPE& operator=(DFAPI_TYPEID_TYPE& o);
	DWORD operator=(DWORD dwTypeID);
	BOOL operator==(DFAPI_TYPEID_TYPE& o);
	BOOL operator==(DWORD dwTypeID);
	//@}
};

//	DFAPI_SESSION
//******************************************************************************
typedef DWORD64 DFAPI_SESSION;

//	DFAPI_STD_PROC
//******************************************************************************
typedef BOOL (*DFAPI_STD_PROC)(DFAPI_SESSION, LPVOID);

//******************************************************************************
#include "DFAPICommon.inl"
