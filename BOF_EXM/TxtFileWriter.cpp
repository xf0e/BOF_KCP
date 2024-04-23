#include "StdAfx.h"
#include "txtfilewriter.h"


CTxtFileWriter::CTxtFileWriter(void)
{
	m_bOpen = FALSE;
}

CTxtFileWriter::~CTxtFileWriter(void)
{
}
//Writes the index field values for one document to the .txt file.
BOOL CTxtFileWriter::WriteDocumentIndexValues (CStringArray& indexValues, int docNumber, CString delimiter)
{
		
	//This is set to true once at least one index value is found to be defined.
	BOOL isOneDefined = FALSE; 

	int count = indexValues.GetCount();
	for (int index = 0; index < count; index++)
	{
		CString value = indexValues[index];
		if (!value.IsEmpty())	// do we have any indexes defined
			isOneDefined = TRUE;

		WriteString(value);

		if (index < (count - 1)) 
			WriteString(delimiter);
	}

	WriteString(_T("\r\n"));

	//Check to make sure at least one index field defined.
	if (!isOneDefined)	
		return FALSE;

	return TRUE;
}

//Writes the path name of one image to the .txt file.
BOOL CTxtFileWriter::WriteImagePath(CString imagePath)
{

	CString str;
	str.Format(_T("@%s\r\n"), imagePath); 
	WriteString(str);

	return TRUE;
}

//Write the index file when the Batch Import Only box is checked in the
//setup dialog.
BOOL CTxtFileWriter::WriteImportOnlyVersion (CString batchName, CString filePath)
{
	CString str;
	CString extension;
	str.Format( _T("%s\r\n@%s\\*.*"), batchName, filePath);
	WriteStringLine(str);

	return TRUE;
}

//	open/close
//------------------------------------------------------------------------------
BOOL CTxtFileWriter::Open(LPCTSTR lpszFilePath)
{
	//attempt to open file
	BOOL bSuccess = FALSE;

	//open file
	if (!m_file.Open(lpszFilePath, CFile::modeCreate|CFile::modeReadWrite)) 
		return FALSE;

	m_bOpen = TRUE;
	bSuccess = TRUE;
	
	return (bSuccess);
}

BOOL CTxtFileWriter::Create(LPCTSTR lpszFilePath)
{
	//attempt to create file
	BOOL bSuccess = FALSE;

	//create file
	if (!m_file.Open(lpszFilePath, CFile::modeCreate|CFile::modeReadWrite)) return FALSE;

		

	m_bOpen = TRUE;
	//
	return (bSuccess);
}

void CTxtFileWriter::WriteString(CString str)
{
	int nLen = str.GetLength();
	m_file.WriteString((LPCTSTR)str);
}
void CTxtFileWriter::WriteStringLine(CString str)
{
	WriteString(str + _T("\r\t"));
}