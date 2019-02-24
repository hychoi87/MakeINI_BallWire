
// MakeINI_Defect.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMakeINI_DefectApp:
// See MakeINI_Defect.cpp for the implementation of this class
//

class CMakeINI_DefectApp : public CWinApp
{
public:
	CMakeINI_DefectApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMakeINI_DefectApp theApp;