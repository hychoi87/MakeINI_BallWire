#pragma once

#include "Resource.h"

// CForm4 ��ȭ �����Դϴ�.

class CForm4 : public CDialog
{
	DECLARE_DYNAMIC(CForm4)

public:
	CForm4(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CForm4();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
