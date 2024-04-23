#pragma once

class CTxtFileWriter
{
public:

public:
	//!	Open a file.
	BOOL Open(LPCTSTR lpszFilePath);

	//!	Create a file.
	BOOL Create(LPCTSTR lpszFilePath);
	BOOL IsOpen(){return m_bOpen;};
	void Close(){ if(IsOpen()) m_file.Close();};




	CTxtFileWriter(void);
	~CTxtFileWriter(void);
	//Writes the index field values for one document to the .txt file.
	BOOL	WriteDocumentIndexValues (CStringArray& indexValues, int docNumber, CString delimiter);

	//Writes the path name of one image to the .txt file.
	BOOL	WriteImagePath			 (CString imagePath);

	//Write the index file when the Batch Import Only box is checked in the
	//setup dialog.
	BOOL    WriteImportOnlyVersion   (CString batchName, CString batchPath);

protected:
	CStdioFile			    m_file;
	BOOL					m_bOpen;

	void WriteString(CString str);
	void WriteStringLine(CString str);
};


