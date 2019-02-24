
// MakeINI_DefectDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "BallWire.h"
#include "Defect_BW.h"
#include "WireConnect.h"
#include "Masking.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
// CMakeINI_DefectDlg dialog
class CMakeINI_DefectDlg : public CDialogEx
{
// Construction
public:
	CMakeINI_DefectDlg(CWnd* pParent = NULL);	// standard constructor

//	CFormFirst		m_formFirst;
	CBallWire		m_BallWire;
	Defect_BW		m_Defect_BW;
	WireConnect		m_WireConnect;
	Masking			m_Masking;
	CWnd*			m_pwndShow;

	void RegisterModel();

// Dialog Data
	enum { IDD = IDD_MAKEINI_DEFECT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_Tab;
	CComboBox m_ComboCon1;
	CString m_Combo1;
	CComboBox m_ComboCon2;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk3();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedOk2();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
	string intToString(int n);
};