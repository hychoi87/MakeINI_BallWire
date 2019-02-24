// Form4.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MakeINI_Defect.h"
#include "Form4.h"
#include "afxdialogex.h"


// CForm4 대화 상자입니다.

IMPLEMENT_DYNAMIC(CForm4, CDialog)

CForm4::CForm4(CWnd* pParent /*=NULL*/)
	: CDialog(CForm4::IDD, pParent)
{

}

CForm4::~CForm4()
{
}

void CForm4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CForm4, CDialog)
END_MESSAGE_MAP()


// CForm4 메시지 처리기입니다.
