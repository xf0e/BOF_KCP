/*!
	@file	DFAPIDataHelper.h
	@author	Max Wu (max.wu@kodak.com)
	@author	Copyright (C) 1998-2006 Eastman Kodak Company.
	@author	All rights reserved.
	@date	2006-09-01
*/

#pragma once

#include <afxwin.h>
#include "DFAPICommon.h"

//	Helper Macros
//******************************************************************************
#define	DFAPI_DATA_TYPE_RW(name, W_type, R_type)								\
	BOOL W_##name(DWORD& ptr, DFAPI_DATA_TYPE& db, W_type data){				\
		return W_buffer(ptr, db, &data, sizeof(data));							\
	}																			\
	BOOL R_##name(DWORD& ptr, DFAPI_DATA_TYPE& db, R_type data){				\
		return R_buffer(ptr, db, &data, sizeof(data));							\
	}

//	CDFAPIDataHelper
//******************************************************************************
//!	Base class for those data structure needs to be convert to/from data block.
class CDFAPIDataHelper{
public:
	CDFAPIDataHelper();

	//!	@name	settings
	//@{
protected:
	DWORD							m_dwBlockDeltaSize;		//!< minimal block incremental size
	//@}

	//!	@name	reset
	//@{
public:
	//!	Reset data.
	/*!	
		Override this routine to define the rule to reset native data structure.
	*/
	virtual void Reset();
	//@}

	//!	@name	convert
	//@{
protected:
	//!	Convert data structure to data block.
	/*!	
		Invoked by framework when needs to convert data structure to data block.
		Override this routine to define the rule to convert native data structure to data block
		by calling routines as "W_xxx".
		@param[in/out]	ptr			Framework parameter and simply pass it to routines as "W_xxx".
		@param[in/out]	db			Framework parameter and simply pass it to routines as "W_xxx".
		@return Returns TRUE when all native data structure had been converted.  Otherwise, it
		returns FALSE.  When it returns FALSE, the result data block will be empty.
	*/
	virtual BOOL OnToDataBlock(DWORD& ptr, DFAPI_DATA_TYPE& db);

	//!	Convert data block to data structure.
	/*
		Invoked by framework when needs to convert data block to data structure.
		Override this routine to define the rule to convert data block to native data structure
		by calling routines as "R_xxx".
		@param[in/out]	ptr			Framework parameter and simply pass it to routines as "R_xxx".
		@param[in/out]	db			Framework parameter and simply pass it to routines as "R_xxx".
		@return Returns TRUE when all native data structure had been converted.  Otherwise, it
		returns FALSE.  When it returns FALSE, the native data structure will be reset as rule
		defined in routine Reset().
	*/
	virtual BOOL OnFromDataBlock(DWORD& ptr, DFAPI_DATA_TYPE& db);

public:
	//!	Convert data structure to data block.
	BOOL ToDataBlock(DFAPI_DATA_TYPE& db);

	//!	Convert data block to data structure.
	BOOL FromDataBlock(DFAPI_DATA_TYPE& db);
	//@}

	//!	@name	read/write
	//@{
protected:
	BOOL W_buffer(DWORD& ptr, DFAPI_DATA_TYPE& db, LPVOID lpBuffer, DWORD dwBufferSize);
	BOOL R_buffer(DWORD& ptr, DFAPI_DATA_TYPE& db, LPVOID lpBuffer, DWORD dwBufferSize);

	BOOL W_string(DWORD& ptr, DFAPI_DATA_TYPE& db, LPCWSTR data);
	BOOL R_string(DWORD& ptr, DFAPI_DATA_TYPE& db, CString& data);

	DFAPI_DATA_TYPE_RW(char, char, char&)
	DFAPI_DATA_TYPE_RW(uchar, unsigned char, unsigned char&)
	DFAPI_DATA_TYPE_RW(wchar, wchar_t, wchar_t&)
	DFAPI_DATA_TYPE_RW(short, short, short&)
	DFAPI_DATA_TYPE_RW(ushort, unsigned short, unsigned short&)
	DFAPI_DATA_TYPE_RW(long, long, long&)
	DFAPI_DATA_TYPE_RW(ulong, unsigned long, unsigned long&)
	DFAPI_DATA_TYPE_RW(float, float, float&)
	DFAPI_DATA_TYPE_RW(double, double, double&)
	DFAPI_DATA_TYPE_RW(BYTE, BYTE, BYTE&)
	DFAPI_DATA_TYPE_RW(WORD, WORD, WORD&)
	DFAPI_DATA_TYPE_RW(DWORD, DWORD, DWORD&)
	DFAPI_DATA_TYPE_RW(DWORD64, DWORD64, DWORD64&)
	//@}
};

//******************************************************************************
#include "DFAPIDataHelper.inl"
