/*
	Capture Pro Example System BOF
	MyPlugin.cpp
	Copyright (C) 1998-2008 Eastman Kodak Company.
	All rights reserved.
	February 2008 V1.0

	October 2008 v1.1
	Includes example of Image Address data and use of the KCSBOFSDK
*/

#include "StdAfx.h"
#include "MyPlugin.h"
#include "MyCFGACIData.h"
#include "MyCFGACIUI.h"


// If TRUE data BOF configuration data is save to an 'ini' file
// if FALSE data is saved to a Kodak Capture Pro data block
BOOL g_bRegularPersistData = FALSE; 

//  Define your error code here, use SetLastError to return error code number. 
//  And error code description to GetErrorMsg implementation in this file.

enum ErrCode{
	//file system error [1, 20]
	EC_OPEN_INDEX = 1,
	EC_COPY_FILE ,		//	2,
	EC_WRITE_FILE,		//	3,
	EC_CREATE_FOLDER,	//  4
	EC_FOLDER_EXIST,	//	5   
	//image process error [21,50]
	EC_NOINDEX = 21,
	//other error [51,+)
};
// Plugin Implementation
//******************************************************************************
DFAPI_IMPLEMENT_PLUGIN_DLLMAIN()
DFAPI_IMPLEMENT_PLUGIN_ENTRYPOINTS(CMyPlugin)

// Map the Advanced BOF API functions
//******************************************************************************
BOOL CMyPlugin::GetProcAddress(DFAPI_SESSION session, LPCTSTR lpszProcName, LPVOID* lpProcAddress)
{
	if( (NULL == lpszProcName) || (NULL == lpProcAddress) )
	{
		return FALSE;
	}
	DFAPI_PLUGIN_GPA(KCBOFAPI_GETSUPPORTEDFILETYPES_PROCNAME, KCBOFAPI_GetSupportedFileTypes);
	DFAPI_PLUGIN_GPA(KCBOFAPI_SETOUTPUTFILETYPE_PROCNAME, KCBOFAPI_SetOutputFileType);
	DFAPI_PLUGIN_GPA(KCBOFAPI_VALIDATECONFIG_PROCNAME, KCBOFAPI_ValidateConfig);
	DFAPI_PLUGIN_GPA(KCBOFAPI_GETFILEPATHNAME_PROCNAME, KCBOFAPI_GetFilePathName);
	DFAPI_PLUGIN_GPA(KCBOFAPI_SETFILEPATHNAME_PROCNAME, KCBOFAPI_SetFilePathName);
	return 	TKCBOFAPIPlugin<TDFShellAPIPluginSession<CMyPlugin>,CMyPlugin>::GetProcAddress(session, lpszProcName, lpProcAddress);
}



// CMyPlugin
//******************************************************************************
CMyPlugin::CMyPlugin() : m_strCurProcessFile(L"")
{
	//initialize DFENVACI variables
	// These are used to access KodakCapturePro program settings

	// Set this global to KCADVBOFAPI_VERSION to have CapturePro create the files (pdf/tif/jpg)
	// and use: GetSupportedFileTypes()
	//          SetOutputFileType()
	//          ValidateConfig()
	//          GetFilePathName()
	//          SetFilePathName()

	//g_APIVersion = KCBOFAPI_VERSION

	g_APIVersion = KCADVBOFAPI_VERSION;
	
	InitializeTextVariables(20);  //DFENVACI support 20 text variables
	InitializeDataVariables(20);  //DFENVACI support 20 data variables
	
	// default m_nCurrentLevel to a know starting point
	m_nCurrentLevel = -1;  //
}

CMyPlugin::~CMyPlugin()
{
}

// plugin information
//------------------------------------------------------------------------------
DFAPI_VERSION_TYPE CMyPlugin::g_Version;
DFAPI_BUILDVERSION_TYPE CMyPlugin::g_BuildVersion;

void CMyPlugin::GetPluginInfoEx(LPCTSTR lpszLanguage, CString& strName, CString& strDescription, CString& strCopyright)
{
	// You should populate strName, strDescription and strCopyright with the appropriate data
	strName = _T("My Output");	// This is the name displayed in the Job Setup Screen
	strDescription = _T("This is an Example Plugin for Kodak Capture Pro.");
	strCopyright = _T("Copyright (C) 1998-2009 Eastman Kodak Company.  All rights reserved.");
#ifdef	_DEBUG
	strName += _T(" (Debug)");
#endif	//_DEBUG
}

//DFCFGACI
//------------------------------------------------------------------------------
CDFCFGACIBasicUI* CMyPlugin::CreateUI()
{
	return (new CMyCFGACIUI);
}

BOOL CMyPlugin::CFGACI_ValidateConfig(DFAPI_DATA_TYPE& config)
{
	//According to business logical rule, check the configuration  
	CMyCFGACIData data;
	data.FromDataBlock(config);
	
	// Verify that the data from the Setup is correct.
	// If its OK return TRUE, otherwise return FALSE

	return TRUE;
}

BOOL CMyPlugin::CFGACI_GetSupportedUIMode(BOOL& bSupportUI, BOOL& bSupportModalUI)
{
	// bSupportUI, if TRUE will embed the defined setup 
	// dialog template with in a Kodak Capture Pro dialog frame
	// This is the only mode currently supported

	bSupportUI = TRUE;          //Embedded UI
	bSupportModalUI = FALSE;    //Modal UI - ******** NOT SUPPORTED **********
	
	return TRUE;
}

BOOL CMyPlugin::CFGACI_GetUISize(int& nWidth, int& nHeight)
{
  	// Set the nWidth and nHeight (Dialog Units) variables to
	// match the dialog template
    nWidth = 300;
    nHeight = 190;
    return TRUE;
}
BOOL CMyPlugin::CFGACI_LoadConfig(LPCTSTR lpszFilePath, DFAPI_DATA_TYPE& config)
{
	BOOL bRet = TRUE;

	// Load the BOF configuration data
	if (g_bRegularPersistData)	// g_bRegularPersistData is a global variable defaulted to TRUE
	{  //From binary data file
		bRet = __super::CFGACI_LoadConfig(lpszFilePath, config);
	}
	else
	{  //Load data from INI format file
		CMyCFGACIData data;
		data.LoadConfig(lpszFilePath);
		if(bRet ) 
			bRet = data.ToDataBlock(config);
	}

	return bRet;
}
BOOL CMyPlugin::CFGACI_SaveConfig(LPCTSTR lpszFilePath, DFAPI_DATA_TYPE& config)
{
	BOOL bRet = TRUE;

	// Save the BOF configuration data
	if (g_bRegularPersistData)
	{  //To binary format data file
		bRet = __super::CFGACI_SaveConfig(lpszFilePath, config);
	}
	else
	{  //To INI format file
		CMyCFGACIData data;
		bRet = data.FromDataBlock(config);
		if (bRet) 
			data.SaveConfig(lpszFilePath);
	}

	return bRet;
}

BOOL CMyPlugin::CFGACI_ValidateUIConfig()
{
	//Validate the GUI configuration when press ok button 
	CMyCFGACIUI* pUI = (CMyCFGACIUI*) m_pUI;
	return pUI->ValidateUI();
}


//	KCBOFAPI
//------------------------------------------------------------------------------
DFAPI_PLUGIN_IMPLEMENT_STD_INTERFACE(CMyPlugin, KCBOFAPI_ClearIndexKey)
{
	KCBOFAPI_CLEARINDEXKEY_PARAM* p = (KCBOFAPI_CLEARINDEXKEY_PARAM*) param;
	if (p == NULL) return FALSE;

	// Level
	// 1	Image
	// 2	Page
	// 3	Document
	// 4	Batch

	POSITION pos = m_lstIndex.GetHeadPosition();
	while (pos)
	{	// loop through, only working on the required level
		Index_Pair& item = m_lstIndex.GetNext(pos);
		if (item.nLevel == p->nLevel)
		{	// Set Key to ""
			item.strKey = _T("");
		}
	}
	return TRUE;
}

DFAPI_PLUGIN_IMPLEMENT_STD_INTERFACE(CMyPlugin, KCBOFAPI_AddIndexKey)
{
	KCBOFAPI_ADDINDEXKEY_PARAM* p = (KCBOFAPI_ADDINDEXKEY_PARAM*) param;
	if (p == NULL) 
		return FALSE;

	// Add this key to the list
	Index_Pair item;
	item.nLevel = p->nLevel;
	item.strKey = p->szIndexKey;
	m_lstIndex.AddTail(item);

	return TRUE;
}

DFAPI_PLUGIN_IMPLEMENT_STD_INTERFACE(CMyPlugin, KCBOFAPI_ClearIndexValue)
{
	KCBOFAPI_CLEARINDEXVALUE_PARAM* p = (KCBOFAPI_CLEARINDEXVALUE_PARAM*) param;
	if (p == NULL) return FALSE;

	POSITION pos = m_lstIndex.GetHeadPosition();
	while (pos)
	{	// loop through, only working on the required level
		POSITION posOld = pos;
		Index_Pair& item = m_lstIndex.GetNext(pos);
		if (item.nLevel == p->nLevel)
		{	// Delete the Data stored in Value
			item.strValue = _T("");
		}
	}
	return TRUE;
}

DFAPI_PLUGIN_IMPLEMENT_STD_INTERFACE(CMyPlugin, KCBOFAPI_SetIndexValue)
{
	KCBOFAPI_SETINDEXVALUE_PARAM* p = (KCBOFAPI_SETINDEXVALUE_PARAM*) param;
	if (p == NULL) return FALSE;

	POSITION pos = m_lstIndex.GetHeadPosition();
	while (pos) 
	{	// Set the index value based on level and key
		Index_Pair& item = m_lstIndex.GetNext(pos);
		if (item.nLevel == p->nLevel && item.strKey == p->szIndexKey)
		{
			item.strValue = p->szIndexValue;
		}
	}
	
	return TRUE;
}
DFAPI_PLUGIN_IMPLEMENT_STD_INTERFACE(CMyPlugin, KCBOFAPI_BeginProcess)
{
	KCBOFAPI_BEGINPROCESS_PARAM* p = (KCBOFAPI_BEGINPROCESS_PARAM*) param;
	if (p == NULL) return FALSE;

	//begin process
	return BeginProcess((int) p->nLevel, p->szLevelName, p->szLevelID);
}

DFAPI_PLUGIN_IMPLEMENT_STD_INTERFACE(CMyPlugin, KCBOFAPI_AddImageFile)
{
	KCBOFAPI_ADDIMAGEFILE_PARAM* p = (KCBOFAPI_ADDIMAGEFILE_PARAM*) param;
	if (p == NULL) 
		return FALSE;

	//add image file
	return OnAddImageFile(p->szImageFilePath, p->info);
}


DFAPI_PLUGIN_IMPLEMENT_STD_INTERFACE(CMyPlugin, KCBOFAPI_EndProcess)
{
	KCBOFAPI_ENDPROCESS_PARAM* p = (KCBOFAPI_ENDPROCESS_PARAM*) param;
	if (p == NULL) return FALSE;
	
	return EndProcess(p->nLevel);

}

DFAPI_PLUGIN_IMPLEMENT_STD_INTERFACE(CMyPlugin, KCBOFAPI_AbortProcess)
{
	// This function is called in response to an error
	KCBOFAPI_ABORTPROCESS_PARAM* p = (KCBOFAPI_ABORTPROCESS_PARAM*) param;
	if (p == NULL) 
		return FALSE;

	// Cleanup anything we have started
	OnAbortProcess();

	return TRUE;
}

DFAPI_PLUGIN_IMPLEMENT_STD_INTERFACE(CMyPlugin, KCBOFAPI_GetSupportedFileTypes)
{
	KCBOFAPI_FILETYPES_PARAM* p = (KCBOFAPI_FILETYPES_PARAM*) param;
	if (p == NULL) return FALSE;

	return GetSupportedFileTypes(p->dwFileTypeAll, p->dwFileTypeBW, p->dwFileTypeCG, p->dwGroupModeAll,p->dwGroupModeBW,p->dwGroupModeCG);
}
DFAPI_PLUGIN_IMPLEMENT_STD_INTERFACE(CMyPlugin, KCBOFAPI_SetOutputFileType)
{
	KCBOFAPI_FILETYPES_PARAM* p = (KCBOFAPI_FILETYPES_PARAM*) param;
	if (p == NULL) return FALSE;

	return SetOutputFileType(p->dwFileTypeAll, p->dwFileTypeBW, p->dwFileTypeCG, p->dwGroupModeAll,p->dwGroupModeBW,p->dwGroupModeCG);
}
DFAPI_PLUGIN_IMPLEMENT_STD_INTERFACE(CMyPlugin, KCBOFAPI_ValidateConfig)
{
	KCBOFAPI_VALIDATECONFIG_PARAM* p = (KCBOFAPI_VALIDATECONFIG_PARAM*) param;
	if (p == NULL) return FALSE;

	CString strErrMsg;
	if( ValidateConfig(p->bSuccess, strErrMsg))
	{
		p->szErrorMessage.SetEx(strErrMsg);
		return TRUE;
	}
	return FALSE;
}
DFAPI_PLUGIN_IMPLEMENT_STD_INTERFACE(CMyPlugin, KCBOFAPI_GetFilePathName)
{
	KCBOFAPI_FILEPATHNAME_PARAM* p = (KCBOFAPI_FILEPATHNAME_PARAM*) param;
	if (p == NULL) return FALSE;

	CString strFilePathFormula;
	if(GetFilePathName(p->dwChannel, strFilePathFormula))
	{
		p->szPathName.SetEx(strFilePathFormula);
		return TRUE;
	}
	return FALSE;
}
DFAPI_PLUGIN_IMPLEMENT_STD_INTERFACE(CMyPlugin, KCBOFAPI_SetFilePathName)
{
	KCBOFAPI_FILEPATHNAME_PARAM* p = (KCBOFAPI_FILEPATHNAME_PARAM*) param;
	if (p == NULL) return FALSE;

	return SetFilePathName(p->dwChannel, p->szPathName);
}


//	process engine
//------------------------------------------------------------------------------
BOOL CMyPlugin::BeginProcess(int nLevel, LPCTSTR lpszLevelName, LPCTSTR lpszLevelID)
{
	//check level
	switch (nLevel){
		case KCBOFAPI_LEVEL_BATCH:
			if (m_nCurrentLevel != -1) 
				return FALSE;
			m_nCurrentLevel = KCBOFAPI_LEVEL_BATCH;
			m_strBatchLevelName = lpszLevelName;
			m_strBatchLevelID = lpszLevelID;
			return OnBeginProcessBatch();

		case KCBOFAPI_LEVEL_DOCUMENT:
			if (m_nCurrentLevel != KCBOFAPI_LEVEL_BATCH) 
				return FALSE;
			m_nCurrentLevel = KCBOFAPI_LEVEL_DOCUMENT;
			m_strDocumentLevelName = lpszLevelName;
			m_strDocumentLevelID = lpszLevelID;
			return OnBeginProcessDocument();

		case KCBOFAPI_LEVEL_PAGE:
			if (m_nCurrentLevel != KCBOFAPI_LEVEL_DOCUMENT) 
				return FALSE;
			m_nCurrentLevel = KCBOFAPI_LEVEL_PAGE;
			m_strPageLevelName = lpszLevelName;
			m_strPageLevelID = lpszLevelID;
			return OnBeginProcessPage();

		case KCBOFAPI_LEVEL_IMAGE:
			if (m_nCurrentLevel != KCBOFAPI_LEVEL_PAGE) 
				return FALSE;
			m_nCurrentLevel = KCBOFAPI_LEVEL_IMAGE;
			m_strImageLevelName = lpszLevelName;
			m_strImageLevelID = lpszLevelID;
			return OnBeginProcessImage();
	}
	// Default is to return FALSE
	return FALSE;
}

BOOL CMyPlugin::EndProcess(int nLevel)
{
	// based on Level, set global variables so the BOF
	// knows where it is in the process.
	// This will ensure we will complete one process before
	// another is started then call the appropriate EndProcess 
	// function for the current level
	
	switch (nLevel)
	{
		case KCBOFAPI_LEVEL_BATCH:
			if (m_nCurrentLevel != KCBOFAPI_LEVEL_BATCH) 
				return FALSE;
			if (!OnEndProcessBatch()) 
				return FALSE;
			m_nCurrentLevel = -1;
			m_strBatchLevelName.Empty();
			m_strBatchLevelID.Empty();
			return TRUE;

		case KCBOFAPI_LEVEL_DOCUMENT:
			if (m_nCurrentLevel != KCBOFAPI_LEVEL_DOCUMENT) 
				return FALSE;
			if (!OnEndProcessDocument()) 
				return FALSE;
			m_nCurrentLevel = KCBOFAPI_LEVEL_BATCH;
			m_strDocumentLevelName.Empty();
			m_strDocumentLevelID.Empty();
			return TRUE;

		case KCBOFAPI_LEVEL_PAGE:
			if (m_nCurrentLevel != KCBOFAPI_LEVEL_PAGE) 
				return FALSE;
			if (!OnEndProcessPage()) 
				return FALSE;
			m_nCurrentLevel = KCBOFAPI_LEVEL_DOCUMENT;
			m_strPageLevelName.Empty();
			m_strPageLevelID.Empty();
			return TRUE;

		case KCBOFAPI_LEVEL_IMAGE:
			if (m_nCurrentLevel != KCBOFAPI_LEVEL_IMAGE) 
				return FALSE;
			if (!OnEndProcessImage()) 
				return FALSE;
			m_nCurrentLevel = KCBOFAPI_LEVEL_PAGE;
			m_strImageLevelName.Empty();
			m_strImageLevelID.Empty();
			return TRUE;
	}

	// Default is to return FALSE
	return FALSE;
}

BOOL CMyPlugin::OnBeginProcessBatch()
{

	if(!m_data.FromDataBlock(m_CurrentConfig)) 
		m_data.Reset();

	m_nImageCounter = 1;

	// Get the Capture Pro Job specific output path	
	CString strOutputPath;
	TV_GetOutputFolderPath(strOutputPath);

	// m_strBatchLevelID is the batch name
	m_strBatchDir = strOutputPath + m_strBatchLevelID + _T("\\");

	if (!CreateDirectory(m_strBatchDir, NULL))
	{
		//Set error code, and the Capture Pro get description of the error code by calling GetErrorMsg
		// DON'T pop up error message dialog in this module. Otherwise the dialog will block CapturePro.
		SetLastError(EC_CREATE_FOLDER);
		return FALSE;
	}
		
	m_strIndexFile = strOutputPath + m_strBatchLevelID + _T(".txt");
	m_indexWriter.Create(m_strIndexFile);




	return TRUE;



}
BOOL CMyPlugin::OnBeginProcessDocument()
{
	// Write index data to file
	CStringArray arrLabels, arrValues;
	// Retrieve document index Data (Key and Value)
	RetrieveIndex(arrLabels, arrValues, KCBOFAPI_LEVEL_DOCUMENT);

	//This example BOF requires that at least one document level index field 
	// with a non blank value is available
	if(!m_data.m_lBatchImport && arrLabels.GetSize()<=0)
	{
		SetLastError(EC_NOINDEX);
		return FALSE;
	}

	m_docCounter++;
	if(!m_data.m_lBatchImport)
	{
		if(!m_indexWriter.WriteDocumentIndexValues(arrValues, m_docCounter, m_data.m_strDelimiter))
		{
			SetLastError(EC_NOINDEX);
			return FALSE;
		}
	}

	return TRUE;
}
BOOL CMyPlugin::OnBeginProcessPage()
{
	return TRUE;
}
BOOL CMyPlugin::OnBeginProcessImage()
{
	return TRUE;
}
BOOL CMyPlugin::OnAddImageFile(LPCTSTR lpszImageFilePath, KCBOFAPI_IMAGEINFO& info)
{

	// If info.bIAInfo is TRUE then the document contains Image Address and print String information
//	if( info.bIAInfo )
//	{
//		//image address information is available. See kcbofapi.h for the structure format
//		
//		....
//	}
	
	// While not used in this example, the following line gets the type of image that is being processed
	BOOL bColorGrayScale = (info.wImageType == KCBOFAPI_IMAGETYPE_GRAYSCALE || info.wImageType == KCBOFAPI_IMAGETYPE_COLOR);

	CString strDst;
	strDst.Format(_T("%s%08d.txt"),m_strBatchDir, m_nImageCounter);

	m_nImageCounter++;

	//write image path name to .txt file if appropriate
	if (!m_data.m_lBatchImport)
	{
		if (!m_indexWriter.WriteImagePath (strDst))
		{
			SetLastError(EC_WRITE_FILE);
			return FALSE;
		}
	}

	// Add target Image name to array.
	m_arrImages.Add(strDst);

	return TRUE;
}
BOOL CMyPlugin::OnEndProcessImage()
{
	return TRUE;
}
BOOL CMyPlugin::OnEndProcessPage()
{
	return TRUE;
}
BOOL CMyPlugin::OnEndProcessDocument()
{
	return TRUE;
}
BOOL CMyPlugin::OnEndProcessBatch()
{
	if(m_data.m_lBatchImport)
	{
		if(!m_indexWriter.WriteImportOnlyVersion(m_strBatchLevelID, m_strBatchDir))
		{
			SetLastError(EC_WRITE_FILE);
			return FALSE;
		}
	}

	// Close Index file if required
	if(m_indexWriter.IsOpen()) 
		m_indexWriter.Close();

	return TRUE;
}
void CMyPlugin::OnAbortProcess()
{
	// This function will be called if any of the above functions have returned FALSE
	// or Capture Pro has detected an error.
	// It is the responsibility of this BOF to cleanup in the event of an error

	// Remove the index file 
	
	// If the index file is open, close it
	if (m_indexWriter.IsOpen()) 
		m_indexWriter.Close();
	// and then delete it
	DeleteFile(m_strIndexFile);

	// During process, we added the path to each image written to
	// an array. 
	// Delete each image we have output
	for(int i=0; i<m_arrImages.GetCount(); i++)
	{
		DeleteFile(m_arrImages[i]);
	}
	// And finally remove the batch folder we created.
	RemoveDirectory(m_strBatchDir);

}
BOOL CMyPlugin::GetErrorMsg(LPCTSTR lpszLanguage, DWORD dwErrCode, CString& strMsg)
{	
	// If you encountered an error we called SetLastError with our Error No and then returned FALSE.
	// After the BOF has returning FALSE Capture Pro will call this function to get the error description.
	// you should populate the CString& strMsg with your error message
	// IMPORTANT
	// You should not display a MessageBox in this function

	switch (dwErrCode)
    {
    case EC_CREATE_FOLDER:
        strMsg = _T("Cannot create Batch folder!");
        break;
	case EC_COPY_FILE:
        strMsg = _T("Failed to copy file!");
        break;
	case EC_OPEN_INDEX:
		strMsg = _T("Cannot open index file!");
		break;
	case EC_WRITE_FILE:
		  strMsg = _T("Failed to write index file!");
		break;
	case EC_NOINDEX:
		strMsg = _T("This format requires that at least one valid document level index field");
		break;
    default:
        break;
    }
    return TRUE;
}


void CMyPlugin::RetrieveIndex( CStringArray& arrLables, CStringArray& arrValues, DWORD level)
{
	arrValues.RemoveAll();
	arrLables.RemoveAll();

	// Get the defined Index Key and Vale from the list
	// only retrieve data for the specified level
	POSITION pos = m_lstIndex.GetHeadPosition();
	while (pos)
	{
		POSITION posOld = pos;
		Index_Pair& item = m_lstIndex.GetNext(pos);
		if(item.nLevel == level)
		{
			arrLables.Add(item.strKey);
			arrValues.Add(item.strValue);
		}
	}
}

BOOL CMyPlugin::GetSupportedFileTypes(DWORD &dwFileTypeAll, DWORD &dwFileTypeBW, DWORD &dwFileTypeCG, DWORD &dwGroupModeAll, DWORD &dwGroupModeBW, DWORD &dwGroupModeCG)
{
	// This can be used to suppress certain groupings (by batch/document/page or single) or file types
	// The method is called during plugin setup
	dwGroupModeAll &= ~KCBOFAPI_GROUPMODE_BATCH;
	dwFileTypeCG &= ~KCBOFAPI_FILETYPE_JPEG;

	return TRUE;
}
BOOL CMyPlugin::SetOutputFileType(DWORD dwFileTypeAll, DWORD dwFileTypeBW, DWORD dwFileTypeCG, DWORD dwGroupModeAll, DWORD dwGroupModeBW, DWORD dwGroupModeCG)
{
	return TRUE;
}
BOOL CMyPlugin::ValidateConfig(DWORD dwSuccess, CString& strErrMsg)
{
	dwSuccess = TRUE;
	strErrMsg.Empty();
	return TRUE;
}
BOOL CMyPlugin::GetFilePathName(DWORD dwChannel, CString &strFilePathFormula)
{
	CString strImageName;
	strImageName.Format(_T("%08d"),m_nImageCounter);

	// The application will interpret the returned formula before generating the 
	// image file.
	strFilePathFormula = m_strBatchDir + strImageName + _T("<DEFAULT_EXT>");

	return TRUE;
}
BOOL CMyPlugin::SetFilePathName(DWORD dwChannel, LPCTSTR lpszFilePathName)
{

	// If a formula element was used in GetFilePathName(), it will be substituted with
	// when SetFilePathName is called

	//switch(dwChannel)
	//{
	//case KCBOFAPI_CHANNEL_ALL:
	//	m_strCurFilePathAll = lpszFilePathName;
	//	break;
	//case KCBOFAPI_CHANNEL_BW:
	//	m_strCurFilePathBW = lpszFilePathName;
	//	break;
	//case KCBOFAPI_CHANNEL_CG:
	//	m_strCurFilePathCG = lpszFilePathName;
	//	break;
	//default:
	//	return FALSE;
	//}
	
	m_strCurProcessFile = lpszFilePathName;
	return TRUE;
}

