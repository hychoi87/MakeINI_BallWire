// FormFirst.cpp : implementation file
//

#include "stdafx.h"
#include "MakeINI_Defect.h"
#include "FormFirst.h"
#include "afxdialogex.h"


// CFormFirst dialog

IMPLEMENT_DYNAMIC(CFormFirst, CDialog)

CFormFirst::CFormFirst(CWnd* pParent /*=NULL*/)
	: CDialog(CFormFirst::IDD, pParent)
	, m_MaxProcessingLayer(0)
	, m_InsideCheckEn(FALSE)
	, OutsideCheckEn(FALSE)
	, WhiteDefectEn(FALSE)
	, BlackDefectEn(FALSE)
	, m_SizeCalW0(0)
	, m_SizeCalW1(0)
	, m_SizeCalB0(0)
	, m_SizeCalB1(0)
	, m_IBMargin0(0)
	, m_IBMargin1(0)
	, m_OBMargin0(0)
	, m_MergeSize(0)
	, m_SubstrateCheckEn(FALSE)
{

}

CFormFirst::~CFormFirst()
{
}

void CFormFirst::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_MaxProcessingLayer);
	DDX_Check(pDX, IDC_CHECK1, m_InsideCheckEn);
	DDX_Check(pDX, IDC_CHECK2, OutsideCheckEn);
	DDX_Check(pDX, IDC_CHECK3, WhiteDefectEn);
	DDX_Check(pDX, IDC_CHECK4, BlackDefectEn);
	DDX_Text(pDX, IDC_EDIT2, m_SizeCalW0);
	DDX_Text(pDX, IDC_EDIT3, m_SizeCalW1);
	DDX_Text(pDX, IDC_EDIT4, m_SizeCalB0);
	DDX_Text(pDX, IDC_EDIT5, m_SizeCalB1);
	DDX_Text(pDX, IDC_EDIT6, m_IBMargin0);
	DDX_Text(pDX, IDC_EDIT7, m_IBMargin1);
	DDX_Text(pDX, IDC_EDIT8, m_OBMargin0);
	DDX_Text(pDX, IDC_EDIT9, m_MergeSize);
	DDX_Check(pDX, IDC_CHECK5, m_SubstrateCheckEn);
}


BEGIN_MESSAGE_MAP(CFormFirst, CDialog)
	ON_BN_CLICKED(IDC_CHECK1, &CFormFirst::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CFormFirst::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CFormFirst::OnBnClickedCheck3)
	ON_EN_CHANGE(IDC_EDIT1, &CFormFirst::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CFormFirst::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CFormFirst::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CFormFirst::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &CFormFirst::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, &CFormFirst::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, &CFormFirst::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT8, &CFormFirst::OnEnChangeEdit8)
	ON_BN_CLICKED(IDC_CHECK4, &CFormFirst::OnBnClickedCheck4)
	ON_EN_CHANGE(IDC_EDIT9, &CFormFirst::OnEnChangeEdit9)
END_MESSAGE_MAP()


// CFormFirst message handlers

void CFormFirst::OnBnClickedCheck1()
{
	UpdateData();
	InsideCheckEn = m_InsideCheckEn;
}

void CFormFirst::PutInsideCheckEn()
{
	m_InsideCheckEn = InsideCheckEn;
	UpdateData( FALSE );
}

void CFormFirst::OnBnClickedCheck2()
{
	UpdateData();
	OutsideCheckEn1 = OutsideCheckEn;
}

void CFormFirst::PutOutsideCheckEn()
{
	OutsideCheckEn = OutsideCheckEn1;
	UpdateData( FALSE );
}

void CFormFirst::OnBnClickedCheck3()
{
	UpdateData();
	WhiteDefectEn1 = WhiteDefectEn;
}

void CFormFirst::PutWhiteDefectEn()
{
	WhiteDefectEn = WhiteDefectEn1;
	UpdateData( FALSE );
}

void CFormFirst::OnEnChangeEdit1()
{
	UpdateData();
	MaxProcessingLayer = m_MaxProcessingLayer;
}

void CFormFirst::PutMaxProcessingLayer()
{
	m_MaxProcessingLayer = MaxProcessingLayer;
	UpdateData( FALSE );
}

void CFormFirst::OnEnChangeEdit2()
{
	UpdateData();
	SizeCalW0 = m_SizeCalW0;
}

void CFormFirst::PutSizeCalW0()
{
	m_SizeCalW0 = SizeCalW0;
	UpdateData( FALSE );
}

void CFormFirst::OnEnChangeEdit3()
{
	UpdateData();
	SizeCalW1 = m_SizeCalW1;
}

void CFormFirst::PutSizeCalW1()
{
	m_SizeCalW1 = SizeCalW1;
	UpdateData( FALSE );
}

void CFormFirst::OnEnChangeEdit4()
{
	UpdateData();
	SizeCalB0 = m_SizeCalB0;
}

void CFormFirst::PutSizeCalB0()
{
	m_SizeCalB0 = SizeCalB0;
	UpdateData( FALSE );
}

void CFormFirst::OnEnChangeEdit5()
{
	UpdateData();
	SizeCalB1 = m_SizeCalB1;
}

void CFormFirst::PutSizeCalB1()
{
	m_SizeCalB1 = SizeCalB1;
	UpdateData( FALSE );
}

void CFormFirst::OnEnChangeEdit6()
{
	UpdateData();
	IBMargin0 = m_IBMargin0;
}

void CFormFirst::PutIBMargin0()
{
	m_IBMargin0 = IBMargin0;
	UpdateData( FALSE );
}

void CFormFirst::OnEnChangeEdit7()
{
	UpdateData();
	IBMargin1 = m_IBMargin1;
}

void CFormFirst::PutIBMargin1()
{
	m_IBMargin1 = IBMargin1;
	UpdateData( FALSE );
}

void CFormFirst::OnEnChangeEdit8()
{
	UpdateData();
	OBMargin0 = m_OBMargin0;
}

void CFormFirst::PutOBMargin0()
{
	m_OBMargin0 = OBMargin0;
	UpdateData( FALSE );
}


void CFormFirst::OnBnClickedCheck4()
{
	UpdateData();
	BlackDefectEn1 = BlackDefectEn;
}

void CFormFirst::PutBlackDefectEn()
{
	BlackDefectEn = BlackDefectEn1;
	UpdateData( FALSE );
}


BOOL CFormFirst::PreTranslateMessage(MSG* pMsg)
{
	 if( pMsg -> message == WM_KEYDOWN && ( pMsg -> wParam == VK_RETURN || pMsg -> wParam == VK_ESCAPE) )
	 {
	  pMsg -> wParam = NULL;
	 }

	return CDialog::PreTranslateMessage(pMsg);
}


void CFormFirst::OnEnChangeEdit9()
{
	UpdateData();
	MergeSize = m_MergeSize;
}

void CFormFirst::PutMergeSize()
{
	m_MergeSize = MergeSize;
	UpdateData( FALSE );
}
