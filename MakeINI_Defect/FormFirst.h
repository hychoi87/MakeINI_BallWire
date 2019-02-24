#pragma once

extern int MaxProcessingLayer;
extern BOOL InsideCheckEn;
extern BOOL OutsideCheckEn1;
extern BOOL WhiteDefectEn1;
extern BOOL BlackDefectEn1;
extern float SizeCalW0;
extern float SizeCalW1;
extern float SizeCalB0;
extern float SizeCalB1;
extern int IBMargin0;
extern int IBMargin1;
extern int OBMargin0;
extern int MergeSize;

class CFormFirst : public CDialog
{
	DECLARE_DYNAMIC(CFormFirst)

public:
	CFormFirst(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFormFirst();

	void PutMaxProcessingLayer();
	void PutInsideCheckEn();
	void PutOutsideCheckEn();
	void PutWhiteDefectEn();
	void PutBlackDefectEn();
	void PutSizeCalW0();
	void PutSizeCalW1();
	void PutSizeCalB0();
	void PutSizeCalB1();
	void PutIBMargin0();
	void PutIBMargin1();
	void PutOBMargin0();
	void PutMergeSize();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_MaxProcessingLayer;
	BOOL m_InsideCheckEn;
	BOOL OutsideCheckEn;
	BOOL WhiteDefectEn;
	BOOL BlackDefectEn;
	float m_SizeCalW0;
	float m_SizeCalW1;
	float m_SizeCalB0;
	float m_SizeCalB1;
	int m_IBMargin0;
	int m_IBMargin1;
	int m_OBMargin0;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnEnChangeEdit8();
	afx_msg void OnBnClickedCheck4();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int m_MergeSize;
	afx_msg void OnEnChangeEdit9();
	BOOL m_SubstrateCheckEn;
};
