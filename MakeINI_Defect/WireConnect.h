#pragma once

#include "Resource.h"
#include "afxcmn.h"
#include <vector>

using namespace std;
// WireConnect ��ȭ �����Դϴ�.
struct WireConnectInfo {
	int info[4];
};
//struct MaskingInfo {
//	int info[8];
//};

extern int BOX1[36];
extern int BOX2[36];
extern int Ord1[36];
extern int Ord2[36];
extern vector<WireConnectInfo> WireConnectListVal;
//extern vector<MaskingInfo> MaksingListVal;


class WireConnect : public CDialog
{
	DECLARE_DYNAMIC(WireConnect)

public:
	WireConnect(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~WireConnect();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:	
	int m_BOX1;
	int m_BOX2;
	int m_Ord1;
	int m_Ord2;
	int iSavedItem;
	int iSavedSubitem;
	vector<WireConnectInfo> m_WireConnectListVal;
	afx_msg void OnEnChangeEdit();
	void PutData();
	CListCtrl m_WireConnectList;
	afx_msg void OnBnClickedAddList();
	afx_msg void OnBnClickedDeleteList();
	afx_msg void OnBnClickedModify();
	afx_msg void OnEndlabeleditList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
};
