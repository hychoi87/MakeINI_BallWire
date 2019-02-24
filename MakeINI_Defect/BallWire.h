#pragma once
#include "Resource.h"
#include "afxcmn.h"
#include <vector>

using namespace std;
// CBallWire 대화 상자입니다.

struct BoxInfo{
	int X0Offeset;
	int X1Offeset;
	int Y0Offeset;
	int Y1Offeset;
	int BallNum;
	double Threshold;
	int Direction;
};

extern int X0Offeset[13];
extern int X1Offeset[13];
extern int Y0Offeset[13];
extern int Y1Offeset[13];
extern int BallNum[13];
extern double Threshold[13];
extern int Direction[13];

extern vector<BoxInfo> BoxInfoListVal;

class CBallWire : public CDialog
{
	DECLARE_DYNAMIC(CBallWire)

public:
	CBallWire(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CBallWire();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_X0Offeset;
	int m_X1Offeset;
	int m_Y0Offeset;
	int m_Y1Offeset;
	int m_BallNum;
	int iSavedItem ; 
	int iSavedSubitem;
	int ListComboVal;
	
	vector<BoxInfo> m_BoxInfoListVal;

	double m_Threshold;
	int m_Direction;
	afx_msg void OnEnChangeEdit();
	void PutData();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CListCtrl m_BoxInfoList;
	afx_msg void OnBnClickedAddBox();
	afx_msg void OnBnClickedDeleteBox();
	afx_msg void OnBnClickedDeleteAll();
	afx_msg void OnDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCloseupCombo6();
	afx_msg void OnCbnSetfocusCombo6();
	afx_msg void OnCbnDropdownCombo6();
};
