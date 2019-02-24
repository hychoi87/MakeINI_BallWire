// Defect_BW.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Defect_BW.h"
#include "afxdialogex.h"
#include "MakeINI_Defect.h"


// Defect_BW 대화 상자입니다.

IMPLEMENT_DYNAMIC(Defect_BW, CDialog)

	Defect_BW::Defect_BW(CWnd* pParent /*=NULL*/)
	: CDialog(Defect_BW::IDD, pParent)
	, m_BallSizeMethod(0)
	, m_BallSizeKernel(0)
	, m_NTCBallSizeKernel(0)
	, m_BallSizeGain(0)
	, m_BallFindMethod(0)
	, m_BallAdapSize(0)
	, m_BallAdapSize2(0)
	, m_ChipTop(0)
	, m_ALNSizeCheck(0)
	, m_NTCSizeCheck(0)
	, m_ChipSizeCheck(0)
	, m_WireCheck(0)
	, m_CoefficientGain(0)
	, m_ALNBallSize(0)
	, m_Version(0)
	, m_BallPositionMargin(0)
	, m_BallFindVal(0)
	, m_WireSweepVal(0)
	, m_ChipInsideWidth(0)
	, m_ALNPositionCheck(0)
	, m_InsideChipOffest(0)
	, m_ChipBallSizeFail_low(0)
	, m_ChipBallSizeFail_high(0)
	, m_NTCBallSizeFail_low(0)
	, m_NTCBallSizeFail_high(0)
	, m_ALNBallSizeFail_low(0)
	, m_ALNBallSizeFail_high(0)
	, m_ALNBallPOSLeft_low   (0)
	, m_ALNBallPOSLeft_high  (0)
	, m_ALNBallPOSRight_low  (0)
	, m_ALNBallPOSRight_high (0)
	, m_ALNBallPOSBottom_low (0)
	, m_ALNBallPOSBottom_high(0)
	, m_GoldPadBottomCheck(0)
{	  

}

Defect_BW::~Defect_BW()
{
}

void Defect_BW::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT1  , m_BallSizeKernel);
	DDX_Text(pDX, IDC_EDIT9  , m_NTCBallSizeKernel);
	DDX_Text(pDX, IDC_EDIT10 , m_BallSizeGain);

	DDX_Text(pDX, IDC_EDIT11 , m_BallAdapSize);
	DDX_Text(pDX, IDC_EDIT12 , m_BallAdapSize2);
	DDX_Text(pDX, IDC_EDIT14 , m_CoefficientGain);
	DDX_Text(pDX, IDC_EDIT15 , m_ALNBallSize);
	DDX_Text(pDX, IDC_EDIT16 , m_Version);

	DDX_CBIndex(pDX, IDC_COMBO3, m_BallSizeMethod);
	DDX_CBIndex(pDX, IDC_COMBO4, m_BallFindMethod);

	DDX_Check(pDX, IDC_CHECK1 , m_ChipTop);
	DDX_Check(pDX, IDC_CHECK2 , m_ChipSizeCheck);
	DDX_Check(pDX, IDC_CHECK5 , m_ALNSizeCheck);
	DDX_Check(pDX, IDC_CHECK6 , m_NTCSizeCheck);
	DDX_Check(pDX, IDC_CHECK26, m_WireCheck);
	DDX_Check(pDX, IDC_CHECK27, m_ALNPositionCheck);
	DDX_Check(pDX, IDC_CHECK28, m_GoldPadBottomCheck);

	DDX_Text(pDX, IDC_EDIT17 , m_BallPositionMargin);
	DDX_Text(pDX, IDC_EDIT18, m_BallFindVal);
	DDX_Text(pDX, IDC_EDIT19, m_WireSweepVal);
	DDX_Text(pDX, IDC_EDIT27, m_ChipInsideWidth);
	DDX_Text(pDX, IDC_EDIT28, m_InsideChipOffest);

	DDX_Text(pDX, IDC_EDIT7 , m_ChipBallSizeFail_low);
	DDX_Text(pDX, IDC_EDIT29 , m_ChipBallSizeFail_high);
	DDX_Text(pDX, IDC_EDIT31 , m_NTCBallSizeFail_low);
	DDX_Text(pDX, IDC_EDIT33 , m_NTCBallSizeFail_high);
	DDX_Text(pDX, IDC_EDIT20, m_ALNBallSizeFail_low);
	DDX_Text(pDX, IDC_EDIT21, m_ALNBallSizeFail_high);	

	DDX_Text(pDX, IDC_EDIT22 , m_ALNBallPOSLeft_low   );
	DDX_Text(pDX, IDC_EDIT23 , m_ALNBallPOSLeft_high  );
	DDX_Text(pDX, IDC_EDIT24 , m_ALNBallPOSRight_low  );
	DDX_Text(pDX, IDC_EDIT25 , m_ALNBallPOSRight_high );
	DDX_Text(pDX, IDC_EDIT26, m_ALNBallPOSBottom_low );
	DDX_Text(pDX, IDC_EDIT34, m_ALNBallPOSBottom_high);
}


BEGIN_MESSAGE_MAP(Defect_BW, CDialog)
	ON_EN_CHANGE(IDC_EDIT1 , &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_EDIT9 , &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_EDIT10, &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_EDIT11, &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_EDIT12, &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_EDIT14, &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_EDIT15, &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_CHECK1, &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_CHECK2, &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_CHECK5, &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_CHECK6, &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_CHECK16, &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_CHECK26, &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_EDIT17, &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_EDIT18, &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_EDIT19, &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_EDIT27, &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_EDIT28, &Defect_BW::OnEnChangeEdit_BW)
	ON_CBN_SELCHANGE(IDC_COMBO3, &Defect_BW::OnCbnSelchangeCombo3)
	ON_CBN_SELCHANGE(IDC_COMBO4, &Defect_BW::OnCbnSelchangeCombo3)
	ON_BN_CLICKED(IDC_CHECK1 , &Defect_BW::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2 , &Defect_BW::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK5 , &Defect_BW::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK6 , &Defect_BW::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK26, &Defect_BW::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK27, &Defect_BW::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK28, &Defect_BW::OnBnClickedCheck1)

	ON_EN_CHANGE(IDC_EDIT7 , &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_EDIT29, &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_EDIT31, &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_EDIT33, &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_EDIT20, &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_EDIT21, &Defect_BW::OnEnChangeEdit_BW)

	ON_EN_CHANGE(IDC_EDIT22, &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_EDIT23, &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_EDIT24, &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_EDIT25, &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_EDIT26, &Defect_BW::OnEnChangeEdit_BW)
	ON_EN_CHANGE(IDC_EDIT34, &Defect_BW::OnEnChangeEdit_BW)
END_MESSAGE_MAP()


// Defect_BW 메시지 처리기입니다.


void Defect_BW::OnEnChangeEdit_BW()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	BallSizeMethod		 =  m_BallSizeMethod;
	BallSizeKernel		 =  m_BallSizeKernel;
	NTCBallSizeKernel	 =  m_NTCBallSizeKernel;
	BallSizeGain		 =  m_BallSizeGain;
	BallFindMethod		 =  m_BallFindMethod;
	BallAdapSize		 =  m_BallAdapSize;
	BallAdapSize2		 =  m_BallAdapSize2;
	ChipTop					=  m_ChipTop;
	ALNSizeCheck		 =  m_ALNSizeCheck;
	NTCSizeCheck		 =  m_NTCSizeCheck;
	ChipSizeCheck		 =  m_ChipSizeCheck;
	WireCheck			 =  m_WireCheck;
	GoldPadBottomCheck = m_GoldPadBottomCheck;

	CoefficientGain	 =  m_CoefficientGain;
	ALNBallSize		 =  m_ALNBallSize;
	Version			 =  m_Version;
	BallPositionMargin		= m_BallPositionMargin;
	BallFindVal				= m_BallFindVal;
	WireSweepVal			= m_WireSweepVal;
	ChipInsideWidth			= m_ChipInsideWidth;
	InsideChipOffest	=	m_InsideChipOffest;

	ChipBallSizeFail_low	= m_ChipBallSizeFail_low;
	ChipBallSizeFail_high	= m_ChipBallSizeFail_high;
	NTCBallSizeFail_low		= m_NTCBallSizeFail_low;
	NTCBallSizeFail_high	= m_NTCBallSizeFail_high;
	ALNBallSizeFail_low		= m_ALNBallSizeFail_low;
	ALNBallSizeFail_high	= m_ALNBallSizeFail_high;

	ALNBallPOSLeft_low    =  m_ALNBallPOSLeft_low   ;
	ALNBallPOSLeft_high   =  m_ALNBallPOSLeft_high  ;
	ALNBallPOSRight_low   =  m_ALNBallPOSRight_low  ;
	ALNBallPOSRight_high  =  m_ALNBallPOSRight_high ;
	ALNBallPOSBottom_low  =  m_ALNBallPOSBottom_low ;
	ALNBallPOSBottom_high =  m_ALNBallPOSBottom_high;
}


void Defect_BW::OnCbnSelchangeCombo3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//cout<<m_BallSizeMethod<<endl;
	OnEnChangeEdit_BW();

}


void Defect_BW::OnBnClickedCheck1()
{
	OnEnChangeEdit_BW();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ChipTop			 =  m_ChipTop			;
	ALNSizeCheck		 =  m_ALNSizeCheck		;
	NTCSizeCheck		 =  m_NTCSizeCheck		;
	ChipSizeCheck		 =  m_ChipSizeCheck		;
	WireCheck			 =  m_WireCheck			;
	ALNPositionCheck    =  m_ALNPositionCheck  ;
}

void Defect_BW::PutData(){
	m_BallSizeMethod	 =  BallSizeMethod;
	m_BallSizeKernel	 =  BallSizeKernel;
	m_NTCBallSizeKernel	 =  NTCBallSizeKernel;
	m_BallSizeGain		 =  BallSizeGain;
	m_BallFindMethod	 =  BallFindMethod;
	m_BallAdapSize		 =  BallAdapSize;
	m_BallAdapSize2		 =  BallAdapSize2;
	m_ChipTop			 =  ChipTop;
	m_ALNSizeCheck		 =  ALNSizeCheck;
	m_NTCSizeCheck		 =  NTCSizeCheck;
	m_ChipSizeCheck		 =  ChipSizeCheck;
	m_WireCheck			 =  WireCheck;
	m_CoefficientGain	 =  CoefficientGain;
	m_ALNBallSize		 =  ALNBallSize;
	m_Version			 =  Version;
	m_BallPositionMargin		= BallPositionMargin;
	m_BallFindVal				= BallFindVal;
	m_WireSweepVal			= WireSweepVal;
	m_ChipInsideWidth			= ChipInsideWidth;
	m_ALNPositionCheck   =  ALNPositionCheck   ;
	m_InsideChipOffest	=	InsideChipOffest;
	m_GoldPadBottomCheck = GoldPadBottomCheck;
	m_ChipBallSizeFail_low	= ChipBallSizeFail_low;
	m_ChipBallSizeFail_high	= ChipBallSizeFail_high;
	m_NTCBallSizeFail_low		= NTCBallSizeFail_low;
	m_NTCBallSizeFail_high	= NTCBallSizeFail_high;
	m_ALNBallSizeFail_low		= ALNBallSizeFail_low;
	m_ALNBallSizeFail_high	= ALNBallSizeFail_high;


	m_ALNBallPOSLeft_low    =  ALNBallPOSLeft_low   ;
	m_ALNBallPOSLeft_high   =  ALNBallPOSLeft_high  ;
	m_ALNBallPOSRight_low   =  ALNBallPOSRight_low  ;
	m_ALNBallPOSRight_high  =  ALNBallPOSRight_high ;
	m_ALNBallPOSBottom_low  =  ALNBallPOSBottom_low ;
	m_ALNBallPOSBottom_high =  ALNBallPOSBottom_high;
	UpdateData( FALSE );
}


BOOL Defect_BW::PreTranslateMessage(MSG* pMsg)
{
	if( pMsg -> message == WM_KEYDOWN && ( pMsg -> wParam == VK_RETURN || pMsg -> wParam == VK_ESCAPE) )
	{
		pMsg -> wParam = NULL;
	}

	return CDialog::PreTranslateMessage(pMsg);
}
