#pragma once

#include "Resource.h"

// CForm4 대화 상자입니다.

class CForm4 : public CDialog
{
	DECLARE_DYNAMIC(CForm4)

public:
	CForm4(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CForm4();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
