/*!
	@file	DFAPICommon.inl
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-09-01
*/

#pragma once

#include "DFAPICommon.h"

//	DFAPI_TEXTxxx_TYPE
//******************************************************************************
template <int TEXTLEN>
T_DFAPI_TEXT_TYPE<TEXTLEN>::T_DFAPI_TEXT_TYPE()
{
	memset(m_text, 0, sizeof(WCHAR) * TEXTLEN);
}

//	methods
//------------------------------------------------------------------------------
template <int TEXTLEN>
void T_DFAPI_TEXT_TYPE<TEXTLEN>::Clear()
{
	memset(m_text, 0, sizeof(WCHAR) * TEXTLEN);
}

template <int TEXTLEN>
void T_DFAPI_TEXT_TYPE<TEXTLEN>::Set(LPCTSTR lpszText)
{
	Clear();
	wcsncpy_s(m_text, lpszText, TEXTLEN - 1);
}

template <int TEXTLEN>
LPCTSTR T_DFAPI_TEXT_TYPE<TEXTLEN>::operator=(LPCTSTR lpszText)
{
	Set(lpszText);
	return lpszText;
}

template <int TEXTLEN>
BOOL T_DFAPI_TEXT_TYPE<TEXTLEN>::SetEx(LPCTSTR lpszText)
{
	if (wcslen(lpszText) >= TEXTLEN) return FALSE;
	Set(lpszText);
	return TRUE;
}

template <int TEXTLEN>
void T_DFAPI_TEXT_TYPE<TEXTLEN>::Get(LPTSTR lpText, int nSize)
{
	if (nSize < 1) return;
	memset(lpText, 0, sizeof(WCHAR) * nSize);
	wcsncpy_s(lpText, m_text, min(nSize - 1, TEXTLEN - 1));
}

template <int TEXTLEN>
LPCTSTR T_DFAPI_TEXT_TYPE<TEXTLEN>::Get()
{
	return ((LPCTSTR) m_text);
}

template <int TEXTLEN>
T_DFAPI_TEXT_TYPE<TEXTLEN>::operator LPCTSTR()
{
	return ((LPCTSTR) m_text);
}

//	DFAPI_DATA_TYPE
//******************************************************************************
inline DFAPI_DATA_TYPE::DFAPI_DATA_TYPE()
{
	m_hData = NULL;
	m_pData = NULL;
}

inline DFAPI_DATA_TYPE::~DFAPI_DATA_TYPE(){
	Free();
}

//	data information
//------------------------------------------------------------------------------
inline BOOL DFAPI_DATA_TYPE::IsEmpty(){
	return (m_hData == NULL);
}

inline DWORD DFAPI_DATA_TYPE::GetSize()
{
	if (m_hData == NULL) return 0;
	return ((DWORD) ::GlobalSize(m_hData));
}

//	allocate/free
//------------------------------------------------------------------------------
inline BOOL DFAPI_DATA_TYPE::Alloc(DWORD dwSize){
	//free
	Free();

	//allocate
	if (dwSize == 0) return FALSE;
	m_hData = ::GlobalAlloc(GHND, dwSize);
	if (m_hData == NULL) return FALSE;

	//
	return TRUE;
}

inline BOOL DFAPI_DATA_TYPE::ReAlloc(DWORD dwSize){
	//allocate or free
	if (m_hData == NULL) return Alloc(dwSize);
	if (dwSize == 0){
		Free();
		return TRUE;
	}
	if (dwSize == (DWORD) ::GlobalSize(m_hData)) return TRUE;
	
	//unlock
	Unlock();

	//reallocate
	HGLOBAL hNewData = ::GlobalReAlloc(m_hData, dwSize, GMEM_ZEROINIT);
	if (hNewData == NULL) return FALSE;
	m_hData = hNewData;

	//
	return TRUE;
}

inline void DFAPI_DATA_TYPE::Free()
{
	//unlock
	Unlock();

	//free
	if (m_hData){
		::GlobalFree(m_hData);
		m_hData = NULL;
	}
}

//	lock/unlock
//------------------------------------------------------------------------------
inline LPBYTE DFAPI_DATA_TYPE::Lock()
{
	if (m_pData) return m_pData;
	if (m_hData == NULL) return NULL;
	m_pData = (LPBYTE) ::GlobalLock(m_hData);
	return m_pData;
}

inline void DFAPI_DATA_TYPE::Unlock()
{
	if (m_pData){
		::GlobalUnlock(m_hData);
		m_pData = NULL;
	}
}

//	attach/detach
//------------------------------------------------------------------------------
inline void DFAPI_DATA_TYPE::Attach(HGLOBAL hFromData)
{
	//free
	Free();

	//attach
	m_hData = hFromData;
}

inline HGLOBAL DFAPI_DATA_TYPE::Detach()
{
	//unlock
	Unlock();

	//detach
	HGLOBAL hData = m_hData;
	m_hData = NULL;

	//
	return hData;
}

inline void DFAPI_DATA_TYPE::Attach(DFAPI_DATA_TYPE& from)
{
	//free
	Free();

	//attach
	m_hData = from.m_hData;
	m_pData = from.m_pData;
	from.m_hData = NULL;
	from.m_pData = NULL;
}

inline void DFAPI_DATA_TYPE::Detach(DFAPI_DATA_TYPE& to)
{
	to.Attach(*this);
}

//	copy
//------------------------------------------------------------------------------
inline BOOL DFAPI_DATA_TYPE::CopyFrom(DFAPI_DATA_TYPE& from)
{
	//free
	Free();

	//check source
	if (from.m_hData == NULL) return TRUE;
	DWORD dwSize = from.GetSize();
	if (dwSize == 0) return FALSE;

	//lock source
	BOOL bSourceIsLocked = (from.m_pData != NULL);
	LPBYTE pSource = from.Lock();
	if (pSource == NULL) return FALSE;

	//copy
	BOOL bSuccess = FALSE;
	if (Alloc(dwSize)){
		LPBYTE pDest = Lock();
		if (pDest){
			memcpy(pDest, pSource, dwSize);
			Unlock();
			bSuccess = TRUE;
		}
	}
	if (!bSuccess) Free();

	//unlock source
	if (!bSourceIsLocked) from.Unlock();

	//
	return bSuccess;
}

inline BOOL DFAPI_DATA_TYPE::CopyTo(DFAPI_DATA_TYPE& to)
{
	return to.CopyFrom(*this);
}

//	file
//------------------------------------------------------------------------------
inline BOOL DFAPI_DATA_TYPE::Save(LPCTSTR lpszFilePath)
{
	//lock data
	DWORD dwSize = GetSize();
	LPBYTE pData = NULL;
	if (dwSize > 0){
		pData = Lock();
		if (pData == NULL) return FALSE;
	}

	//create file
	BOOL bSuccess = FALSE;
	HANDLE hFile = ::CreateFile(lpszFilePath,
								GENERIC_WRITE,
								0,
								NULL,
								CREATE_ALWAYS,
								FILE_ATTRIBUTE_NORMAL,
								NULL);
	if (hFile){
		//write data
		if (pData){
			DWORD dwWrittenSize = 0;
			if (::WriteFile(hFile, pData, dwSize, &dwWrittenSize, NULL)){
				bSuccess = (dwWrittenSize == dwSize);
			}
		}
		else{
			bSuccess = TRUE;
		}

		//close file
		::CloseHandle(hFile);
	}
	if (!bSuccess) ::DeleteFile(lpszFilePath);

	//unlock data
	Unlock();

	//
	return bSuccess;
}

inline BOOL DFAPI_DATA_TYPE::Load(LPCTSTR lpszFilePath)
{
	//free
	Free();

	//open file
	HANDLE hFile = ::CreateFile(lpszFilePath,
								GENERIC_READ,
								0,
								NULL,
								OPEN_EXISTING,
								FILE_ATTRIBUTE_NORMAL,
								NULL);
	if (hFile == NULL) return FALSE;

	//read data
	BOOL bSuccess = FALSE;
	DWORD dwSize = ::GetFileSize(hFile, NULL);	
	if (dwSize > 0){
		if (Alloc(dwSize)){
			LPBYTE pData = Lock();
			if (pData){
				DWORD dwReadSize = 0;
				if (::ReadFile(hFile, pData, dwSize, &dwReadSize, NULL)){
					bSuccess = (dwReadSize == dwSize);
				}
				Unlock();
			}
		}
	}
	else{
		bSuccess = TRUE;
	}
	if (!bSuccess) Free();

	//close file
	::CloseHandle(hFile);

	//
	return bSuccess;
}

//	DFAPI_VERSION_TYPE
//******************************************************************************
inline DFAPI_VERSION_TYPE::DFAPI_VERSION_TYPE()
{
	m_dwVersion = 0;
}

inline DFAPI_VERSION_TYPE::DFAPI_VERSION_TYPE(DFAPI_VERSION_TYPE& o)
{
	m_dwVersion = o.m_dwVersion;
}

inline DFAPI_VERSION_TYPE::DFAPI_VERSION_TYPE(DWORD dwVersion)
{
	m_dwVersion = dwVersion;
}

inline DFAPI_VERSION_TYPE::DFAPI_VERSION_TYPE(WORD wMajor, WORD wMinor)
{
	Set(wMajor, wMinor);
}

//	methods
//------------------------------------------------------------------------------
inline DFAPI_VERSION_TYPE& DFAPI_VERSION_TYPE::operator=(DFAPI_VERSION_TYPE& o)
{
	m_dwVersion = o.m_dwVersion;
	return o;
}

inline DWORD DFAPI_VERSION_TYPE::operator=(DWORD dwVersion)
{
	m_dwVersion = dwVersion;
	return dwVersion;
}

inline BOOL DFAPI_VERSION_TYPE::IsCompatible(DFAPI_VERSION_TYPE& o)
{
	return m_dwVersion >= o.m_dwVersion;
}

inline BOOL DFAPI_VERSION_TYPE::IsCompatible(DWORD dwVersion)
{
	return m_dwVersion >= dwVersion;
}

inline void DFAPI_VERSION_TYPE::Set(WORD wMajor, WORD wMinor)
{
	m_dwVersion = (DWORD)(wMajor << 16) | (DWORD) wMinor;
}

inline void DFAPI_VERSION_TYPE::Get(WORD& wMajor, WORD& wMinor)
{
	wMajor = (WORD)(m_dwVersion >> 16);
	wMinor = (WORD)(m_dwVersion & 0xFFFF);
}

//	DFAPI_BUILDVERSION_TYPE
//******************************************************************************
inline DFAPI_BUILDVERSION_TYPE::DFAPI_BUILDVERSION_TYPE()
{
	m_dwBuildVersion = 0;
}

inline DFAPI_BUILDVERSION_TYPE::DFAPI_BUILDVERSION_TYPE(DFAPI_BUILDVERSION_TYPE& o)
{
	m_dwBuildVersion = o.m_dwBuildVersion;
}

inline DFAPI_BUILDVERSION_TYPE::DFAPI_BUILDVERSION_TYPE(DWORD64 dwBuildVersion)
{
	m_dwBuildVersion = dwBuildVersion;
}

inline DFAPI_BUILDVERSION_TYPE::DFAPI_BUILDVERSION_TYPE(DWORD dwMajor, DWORD dwMinor)
{
	Set(dwMajor, dwMinor);
}

//	methods
//------------------------------------------------------------------------------
inline DFAPI_BUILDVERSION_TYPE& DFAPI_BUILDVERSION_TYPE::operator=(DFAPI_BUILDVERSION_TYPE& o)
{
	m_dwBuildVersion = o.m_dwBuildVersion;
	return o;
}

inline DWORD64 DFAPI_BUILDVERSION_TYPE::operator=(DWORD64 dwBuildVersion)
{
	m_dwBuildVersion = dwBuildVersion;
	return dwBuildVersion;
}

inline void DFAPI_BUILDVERSION_TYPE::Set(DWORD dwMajor, DWORD dwMinor)
{
	m_dwBuildVersion = dwMajor;
	m_dwBuildVersion <<= 16;
	m_dwBuildVersion <<= 16;
	m_dwBuildVersion |= dwMinor;
}

inline void DFAPI_BUILDVERSION_TYPE::Get(DWORD& dwMajor, DWORD& dwMinor)
{
	dwMajor = (DWORD)(m_dwBuildVersion >> 32);
	dwMinor = (DWORD)(m_dwBuildVersion & 0xFFFFFFFF);
}

//	DFAPI_TYPEID_TYPE
//******************************************************************************
inline DFAPI_TYPEID_TYPE::DFAPI_TYPEID_TYPE()
{
	m_dwTypeID = unknown;
}

inline DFAPI_TYPEID_TYPE::DFAPI_TYPEID_TYPE(DFAPI_TYPEID_TYPE& o)
{
	m_dwTypeID = o.m_dwTypeID;
}

inline DFAPI_TYPEID_TYPE::DFAPI_TYPEID_TYPE(DWORD dwTypeID)
{
	m_dwTypeID = dwTypeID;
}

//	methods
//------------------------------------------------------------------------------
inline BOOL DFAPI_TYPEID_TYPE::IsUnknown()
{
	return m_dwTypeID == unknown;
}

inline BOOL DFAPI_TYPEID_TYPE::IsType(DFAPI_TYPEID_TYPE& o, BOOL bAcceptUnknown)
{
	if (m_dwTypeID == o.m_dwTypeID) return TRUE;
	if (bAcceptUnknown){
		if (m_dwTypeID == unknown) return TRUE;
	}
	return FALSE;
}

inline BOOL DFAPI_TYPEID_TYPE::IsType(DWORD dwTypeID, BOOL bAcceptUnknown)
{
	if (m_dwTypeID == dwTypeID) return TRUE;
	if (bAcceptUnknown){
		if (m_dwTypeID == unknown) return TRUE;
	}
	return FALSE;
}

inline DFAPI_TYPEID_TYPE& DFAPI_TYPEID_TYPE::operator=(DFAPI_TYPEID_TYPE& o)
{
	m_dwTypeID = o.m_dwTypeID;
	return o;
}

inline DWORD DFAPI_TYPEID_TYPE::operator=(DWORD dwTypeID)
{
	m_dwTypeID = dwTypeID;
	return dwTypeID;
}

inline BOOL DFAPI_TYPEID_TYPE::operator==(DFAPI_TYPEID_TYPE& o)
{
	return m_dwTypeID == o.m_dwTypeID;
}

inline BOOL DFAPI_TYPEID_TYPE::operator==(DWORD dwTypeID)
{
	return m_dwTypeID == dwTypeID;
}
