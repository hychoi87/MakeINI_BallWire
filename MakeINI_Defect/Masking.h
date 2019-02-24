#pragma once
#include "Resource.h"
#include "afxcmn.h"
#include <vector>

using namespace std;

struct MaskInfo {
	int type;
	int X0Offeset;
	int X1Offeset;
	int Y0Offeset;
	int Y1Offeset;
	int Thick;
	int BoxNum;
	double Threshold;
};

extern vector<MaskInfo> MaskingListVal;
// Masking 대화 상자입니다.

class Masking : public CDialog
{
	DECLARE_DYNAMIC(Masking)

public:
	Masking(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Masking();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_X0Offeset;
	int m_X1Offeset;
	int m_Y0Offeset;
	int m_Y1Offeset;
	int m_Thick;
	int m_BoxNum;
	int m_type;
	int iSavedItem;
	int iSavedSubitem;
	int ListComboVal;

	afx_msg void OnEnChangeEdit();
	void PutData();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	vector <MaskInfo> m_MaskingInfoListVal;
	afx_msg void OnBnClickedAddBox();
	afx_msg void OnBnClickedDeleteBox();
	afx_msg void OnBnClickedDeleteAll();
	afx_msg void OnDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCloseupCombo6();
	CListCtrl m_MaskingInfoList;
	afx_msg void OnCbnDropdownCombo7();
};
