/*!
	@file	DFAPIDataHelper.inl
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-09-01
*/

#pragma once

#include "DFAPIDataHelper.h"

//	CDFAPIDataHelper
//******************************************************************************
inline CDFAPIDataHelper::CDFAPIDataHelper()
{
	//initialize settings
	m_dwBlockDeltaSize = 1024;
}

//	reset
//------------------------------------------------------------------------------
inline void CDFAPIDataHelper::Reset()
{
}

//	convert
//------------------------------------------------------------------------------
inline BOOL CDFAPIDataHelper::OnToDataBlock(DWORD& ptr, DFAPI_DATA_TYPE& db)
{
	return TRUE;
}

inline BOOL CDFAPIDataHelper::OnFromDataBlock(DWORD& ptr, DFAPI_DATA_TYPE& db)
{
	return TRUE;
}

inline BOOL CDFAPIDataHelper::ToDataBlock(DFAPI_DATA_TYPE& db)
{
	//initialize data block
	db.Free();

	//data structure to data block
	DWORD ptr = 0;
	if (!OnToDataBlock(ptr, db)){
		db.Free();
		return FALSE;
	}
	db.Unlock();

	//
	return TRUE;
}

inline BOOL CDFAPIDataHelper::FromDataBlock(DFAPI_DATA_TYPE& db)
{
	//initialize data structure
	Reset();

	//data block to data structure
	DWORD ptr = 0;
	if (!OnFromDataBlock(ptr, db)){
		db.Unlock();
		Reset();
		return FALSE;
	}
	db.Unlock();

	//
	return TRUE;
}

//	read/write
//------------------------------------------------------------------------------
inline BOOL CDFAPIDataHelper::W_buffer(DWORD& ptr, DFAPI_DATA_TYPE& db, LPVOID lpBuffer, DWORD dwBufferSize)
{
	//check buffer
	if (dwBufferSize == 0) return TRUE;
	if (lpBuffer == NULL) return FALSE;

	//allocate
	DWORD dwSize = db.GetSize();
	DWORD dwRequiredSize = ptr + dwBufferSize;
	if (dwRequiredSize > dwSize){
		ASSERT(m_dwBlockDeltaSize > 0);
		DWORD dwNewBlockCount = (dwRequiredSize - dwSize - 1) / m_dwBlockDeltaSize + 1;
		DWORD dwNewSize = dwSize + m_dwBlockDeltaSize * dwNewBlockCount;
		if (!db.ReAlloc(dwNewSize)) return FALSE;
	}
	
	//lock
	LPBYTE lpData = db.Lock();
	if (lpData == NULL) return FALSE;

	//write
	memcpy(lpData + ptr, lpBuffer, dwBufferSize);
	ptr += dwBufferSize;

	//
	return TRUE;
}

inline BOOL CDFAPIDataHelper::R_buffer(DWORD& ptr, DFAPI_DATA_TYPE& db, LPVOID lpBuffer, DWORD dwBufferSize)
{
	//check buffer
	if (dwBufferSize == 0) return TRUE;
	if (lpBuffer == NULL) return FALSE;

	//check ptr
	DWORD dwSize = db.GetSize();
	DWORD dwRequiredSize = ptr + dwBufferSize;
	if (dwRequiredSize > dwSize) return FALSE;

	//lock
	LPBYTE lpData = db.Lock();
	if (lpData == NULL) return FALSE;

	//read
	memcpy(lpBuffer, lpData + ptr, dwBufferSize);
	ptr += dwBufferSize;

	//
	return TRUE;
}

inline BOOL CDFAPIDataHelper::W_string(DWORD& ptr, DFAPI_DATA_TYPE& db, LPCWSTR data)
{
	//write size
	unsigned long ulSize = lstrlenW(data) * sizeof(wchar_t);
	if (ulSize < 0) return FALSE;
	if (!W_ulong(ptr, db, ulSize)) return FALSE;

	//write string
	if (ulSize == 0) return TRUE;
	return W_buffer(ptr, db, (LPVOID) data, ulSize);
}

inline BOOL CDFAPIDataHelper::R_string(DWORD& ptr, DFAPI_DATA_TYPE& db, CString& data)
{
	//read size
	unsigned long ulSize = 0;
	if (!R_ulong(ptr, db, ulSize)) return FALSE;
	if (ulSize < 0) return FALSE;
	if ((ulSize % sizeof(wchar_t)) != 0) return FALSE;

	//read string
	if (ulSize == 0){
		data = _T("");
		return TRUE;
	}
	LPWSTR pData = data.GetBuffer(ulSize + sizeof(wchar_t));
	if (pData == NULL) return FALSE;
	memset(pData, 0, ulSize + sizeof(wchar_t));
	if (!R_buffer(ptr, db, (LPVOID) pData, ulSize)){
		data.ReleaseBuffer();
		data.Empty();
		return FALSE;
	}
	data.ReleaseBuffer();
	return TRUE;
}