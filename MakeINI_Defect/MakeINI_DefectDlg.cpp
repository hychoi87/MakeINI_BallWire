
// MakeINI_DefectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MakeINI_Defect.h"
#include "MakeINI_DefectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

vector<MaskInfo> MaskingListVal;
vector<WireConnectInfo> WireConnectListVal;
vector<BoxInfo> BoxInfoListVal;


int X0Offeset[13];
int X1Offeset[13];
int Y0Offeset[13];
int Y1Offeset[13];
int BallNum[13];
double Threshold[13];
int Direction[13];

double ChipBallSizeFail_low;
double ChipBallSizeFail_high;
double NTCBallSizeFail_low;
double NTCBallSizeFail_high;
double ALNBallSizeFail_low;
double ALNBallSizeFail_high;
double ALNBallPOSLeft_low   ;
double ALNBallPOSLeft_high  ;
double ALNBallPOSRight_low  ;
double ALNBallPOSRight_high ;
double ALNBallPOSBottom_low ;
double ALNBallPOSBottom_high;

int BallPositionMargin;
double BallFindVal;
int WireSweepVal;
int ChipInsideWidth;

int BallSizeMethod;
int BallSizeKernel ;
int NTCBallSizeKernel ;
int BallSizeGain ;
int BallFindMethod ;
int BallAdapSize ;
int BallAdapSize2 ;
int ChipTop ;
int ALNSizeCheck ;
int NTCSizeCheck ;
int ChipSizeCheck ;
int WireCheck ;
int rotationImage;
int BallSizeImg;
int ALNPositionCheck;
int InsideChipOffest;
double CoefficientGain ;
int ALNBallSize ;
double Version;
int ALNTestVer;
int GoldPadBottomCheck;

int BOX1[36];
int BOX2[36];
int Ord1[36];
int Ord2[36];

int		TopIlluminantEnable[10];
int		BottomIlluminantEnable[10];
int		FilterIlluminantEnable[10];
CString	ModelList[1000];

FILE	*fp;
char	ProductName[300], DummyStr[500], InputFileType[100],  OutputFileType[100], input_directory[500];
int		Registered[100];


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMakeINI_DefectDlg dialog




CMakeINI_DefectDlg::CMakeINI_DefectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMakeINI_DefectDlg::IDD, pParent)
	, m_Combo1(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pwndShow = NULL;
}

void CMakeINI_DefectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	DDX_Control(pDX, IDC_COMBO1, m_ComboCon1);
	DDX_CBString(pDX, IDC_COMBO1, m_Combo1);
	DDX_Control(pDX, IDC_COMBO2, m_ComboCon2);
}

BEGIN_MESSAGE_MAP(CMakeINI_DefectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMakeINI_DefectDlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDOK3, &CMakeINI_DefectDlg::OnBnClickedOk3)
	ON_BN_CLICKED(IDOK, &CMakeINI_DefectDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDOK2, &CMakeINI_DefectDlg::OnBnClickedOk2)
END_MESSAGE_MAP()


// CMakeINI_DefectDlg message handlers

BOOL CMakeINI_DefectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	fopen_s( &fp, "DefectAnalyzer.ini", "r" );
	if( !fp ) {
		AfxMessageBox( _T("DefectAnalyzer.ini Not found") );
		exit( 1 );
	}

	fscanf_s( fp, "ProductName %s\n", ProductName );
	fclose( fp );

	RegisterModel();

	CString strTmp = _T("");
	for(int i = 0; i < 4; i++)
	{
		if( i == 0 )      strTmp.Format(_T("  General Info   "));
		else if( i == 1 ) strTmp.Format(_T("  Ball Info   "));
		else if (i == 2) strTmp.Format(_T("  Wire Info   "));
		else if (i == 3) strTmp.Format(_T("  Mask Info   "));
		m_Tab.InsertItem(i, strTmp, i);
	}

	CRect Rect;
	m_Tab.GetClientRect(&Rect);


	m_Defect_BW.Create(IDD_DIALOG2, &m_Tab);
	m_Defect_BW.SetWindowPos(NULL, 5, 25,
		Rect.Width() - 10, Rect.Height() - 30,
		SWP_SHOWWINDOW | SWP_NOZORDER);
	m_pwndShow = &m_Defect_BW;
	
	m_BallWire.Create(IDD_DIALOG5, &m_Tab);
	m_BallWire.SetWindowPos(NULL, 5, 25,
		Rect.Width() - 10, Rect.Height() - 30,
		SWP_NOZORDER);
	
	m_WireConnect.Create(IDD_DIALOG3, &m_Tab);
	m_WireConnect.SetWindowPos(NULL, 5, 25,
		Rect.Width() - 10, Rect.Height() - 30,
		SWP_NOZORDER);

	m_Masking.Create(IDD_DIALOG6, &m_Tab);
	m_Masking.SetWindowPos(NULL, 5, 25,
		Rect.Width() - 10, Rect.Height() - 30,
		SWP_NOZORDER);
	

	//==========< General Control >============//
	/*
	fopen_s( &fp_in, "MakeINI.ini", "r" );
	if( !fp_in ) {
	AfxMessageBox( _T("MakeINI.ini Not Found !") );
	exit( -1 );
	}

	fscanf( fp_in, "SingleLensMode %d\n", &SingleLensMode );
	fclose( fp_in );
	*/
	int	Cnt = 0;
	if( 1 ) {
		//m_ComboCon2.AddString(_T("DefectFinder_BW.ini"));
		Registered[Cnt]= 0;
		++Cnt;
	}

	if( 1 ) {
		//m_ComboCon2.AddString(_T("BallWire.ini"));
		Registered[Cnt]= 1;
		++Cnt;
	}

	if (1) {
		//m_ComboCon2.AddString(_T("BallWire.ini"));
		Registered[Cnt] = 2;
		++Cnt;
	}

	if (1) {
		//m_ComboCon2.AddString(_T("BallWire.ini"));
		Registered[Cnt] = 3;
		++Cnt;
	}



	m_ComboCon2.SetCurSel(0);


	//Box Info List 목록 초기화
	m_BallWire.m_BoxInfoList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//m_BallWire.m_BoxInfoList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);

	char *szText1[8]={"no","X0","Y0","X1","Y1","검출값","볼갯수","검사영역"};
	int nWid1[8]={30,42,42,42,42,65,55,80};
	LV_COLUMN lCol1;

	lCol1.mask=LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH;  //구조체의 기능을 확장할 플래그를 지정
	lCol1.fmt=LVCFMT_RIGHT;  //칼럼의 정렬을 왼쪽정렬로 지정(_CENTER, _LEFT, _RIGHT중 선택)

	for(int i=0; i<8; i++){
		wchar_t* wStringFrom=new wchar_t[1096];
		MultiByteToWideChar(CP_ACP, 0, szText1[i], -1, wStringFrom, 1096);
		lCol1.pszText=wStringFrom;  //칼럼의 제목을 지정
		lCol1.iSubItem=i;  //서브아이템의 인덱스를 지정
		lCol1.cx=nWid1[i];  //칼럼의 넓이를 지정
		m_BallWire.m_BoxInfoList.InsertColumn(i,&lCol1);
		//m_WireConnectList.InsertColumn(i,&lCol);  //LVCOLUMN구조체로 만들어진 값을 토대로 리스트 컨트롤에 칼럼을 삽입
	}

	
	//Wire Connect List 목록 초기화
	m_WireConnect.m_WireConnectList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//m_WireConnect.m_WireConnectList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	char *szText[5] = { "no","Box1","Ball1","Box2","Ball2" };
	int nWid[5] = { 35,65,65,65,65 };
	LV_COLUMN lCol;

	lCol.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;  //구조체의 기능을 확장할 플래그를 지정
	lCol.fmt = LVCFMT_RIGHT;  //칼럼의 정렬을 왼쪽정렬로 지정(_CENTER, _LEFT, _RIGHT중 선택)

	for (int i = 0; i<5; i++) {
		wchar_t* wStringFrom = new wchar_t[1096];
		MultiByteToWideChar(CP_ACP, 0, szText[i], -1, wStringFrom, 1096);
		lCol.pszText = wStringFrom;  //칼럼의 제목을 지정
		lCol.iSubItem = i;  //서브아이템의 인덱스를 지정
		lCol.cx = nWid[i];  //칼럼의 넓이를 지정
		m_WireConnect.m_WireConnectList.InsertColumn(i, &lCol);
		//m_WireConnectList.InsertColumn(i,&lCol);  //LVCOLUMN구조체로 만들어진 값을 토대로 리스트 컨트롤에 칼럼을 삽입
	}

	m_Masking.m_MaskingInfoList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	char *szText3[8] = { "no","모양","X0","Y0","X1","Y1","두께","기준박스" };
	int nWid3[8] = { 30,82,42,42,42,45,45,60 };
	LV_COLUMN lCol3;

	lCol3.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;  //구조체의 기능을 확장할 플래그를 지정
	lCol3.fmt = LVCFMT_RIGHT;  //칼럼의 정렬을 왼쪽정렬로 지정(_CENTER, _LEFT, _RIGHT중 선택)

	for (int i = 0; i<8; i++) {
		wchar_t* wStringFrom = new wchar_t[1096];
		MultiByteToWideChar(CP_ACP, 0, szText3[i], -1, wStringFrom, 1096);
		lCol3.pszText = wStringFrom;  //칼럼의 제목을 지정
		lCol3.iSubItem = i;  //서브아이템의 인덱스를 지정
		lCol3.cx = nWid3[i];  //칼럼의 넓이를 지정
		m_Masking.m_MaskingInfoList.InsertColumn(i, &lCol3);
		//m_WireConnectList.InsertColumn(i,&lCol);  //LVCOLUMN구조체로 만들어진 값을 토대로 리스트 컨트롤에 칼럼을 삽입
	}
	
	//시작하자마자 로드
	OnBnClickedOk2();


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMakeINI_DefectDlg::RegisterModel()
{
	int		i;

	CFileFind  finder;
	BOOL bWorking = finder.FindFile( _T("./DB/*.*") );

	CString Title1, Title2;
	CString strFind = _T("");
	int Order = 0, nIndex;

	i = 0;

	m_ComboCon1.ResetContent( );

	while( bWorking )
	{
		bWorking = finder.FindNextFile();
		if( finder.IsDirectory() ) {
			Title1 = finder.GetFileTitle();
			if( Title1.GetLength() > 1 ) {
				nIndex = m_ComboCon1.FindStringExact(-1, Title1);
				if(nIndex == LB_ERR) {
					m_ComboCon1.AddString( Title1 );
					ModelList[i] = Title1;

					if( Title1.Compare( (CString) ProductName ) == 0 ) Order = i;
					i++;
				}
			}
		}
	}

	m_ComboCon1.SetCurSel( Order );

}

void CMakeINI_DefectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMakeINI_DefectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMakeINI_DefectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMakeINI_DefectDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(m_pwndShow != NULL)
	{
		m_pwndShow->ShowWindow(SW_HIDE);
		m_pwndShow = NULL;
	}

	int nIndex = m_Tab.GetCurSel();
	switch(nIndex)
	{
	case 0:
		m_Defect_BW.ShowWindow(SW_SHOW);
		m_pwndShow = &m_Defect_BW;
		break;


	case 1:
		m_BallWire.ShowWindow(SW_SHOW);
		m_pwndShow = &m_BallWire;
		break;

	case 2:
		m_WireConnect.ShowWindow(SW_SHOW);
		m_pwndShow = &m_WireConnect;
		break;
	case 3:
		m_Masking.ShowWindow(SW_SHOW);
		m_pwndShow = &m_Masking;
		break;
	}

	*pResult = 0;
}


void CMakeINI_DefectDlg::OnBnClickedOk3() //save
{
	char	fname0[100], fname[100], DummyStr[100],ChkString[300];
	FILE	*fp;
	char INI_Name[1024],INI_source[1024];
	string iniString;

	UpdateData( TRUE );

	strcpy_s( fname0, 100, (char*)_bstr_t( m_Combo1 ) );
	if( fname0[0] == NULL ) AfxMessageBox( _T("Model Not Specified !") );
	else {
		int Response = AfxMessageBox( _T("Confirm to Update ?"), MB_YESNOCANCEL );

		if( Response == IDYES ) {
			//m_formFirst.UpdateData( );

			m_BallWire.UpdateData( );
			m_Defect_BW.UpdateData( );
			m_WireConnect.UpdateData();
			m_Masking.UpdateData();

			sprintf( fname, "./DB/%s/INI/BallWire.ini", fname0, Registered[m_ComboCon2.GetCurSel()] );
			fopen_s( &fp, fname, "w" );

			fprintf( fp, "[BoxOffset]\n");
			for(int i=1; i<BoxInfoListVal.size()+1; i++){

				iniString = "Box["+intToString(i)+"].p1x %d\n";
				strcpy(INI_source, iniString.c_str());
				fprintf( fp, INI_source, BoxInfoListVal[i-1].X0Offeset );
				
				iniString = "Box["+intToString(i)+"].p1y %d\n";
				strcpy(INI_source, iniString.c_str());
				fprintf( fp, INI_source, BoxInfoListVal[i-1].Y0Offeset );

				iniString = "Box["+intToString(i)+"].p2x %d\n";
				strcpy(INI_source, iniString.c_str());
				fprintf( fp, INI_source, BoxInfoListVal[i-1].X1Offeset );

				iniString = "Box["+intToString(i)+"].p2y %d\n";
				strcpy(INI_source, iniString.c_str());
				fprintf( fp, INI_source, BoxInfoListVal[i-1].Y1Offeset );

				iniString = "BoxInfo["+intToString(i)+"] %d\n";
				strcpy(INI_source, iniString.c_str());
				fprintf( fp, INI_source, BoxInfoListVal[i-1].BallNum);

				iniString = "BoxDirection["+intToString(i)+"] %d\n";
				strcpy(INI_source, iniString.c_str());
				fprintf( fp, INI_source, BoxInfoListVal[i-1].Direction);

				iniString = "BoxThresh["+intToString(i)+"] %lf\n";
				strcpy(INI_source, iniString.c_str());
				fprintf( fp, INI_source, BoxInfoListVal[i-1].Threshold);

			}	
			fprintf( fp, "[/BoxOffset]\n\n");
			fprintf( fp, "[DefectConst]\n" );
			fprintf( fp, "ChipBallSizeFail_low           %lf\n",ChipBallSizeFail_low);
			fprintf( fp, "ChipBallSizeFail_high           %lf\n",ChipBallSizeFail_high);
			fprintf( fp, "NTCBallSizeFail_low           %lf\n",NTCBallSizeFail_low);
			fprintf( fp, "NTCBallSizeFail_high           %lf\n",NTCBallSizeFail_high);
			fprintf( fp, "ALNBallSizeFail_low           %lf\n",ALNBallSizeFail_low);
			fprintf( fp, "ALNBallSizeFail_high           %lf\n",ALNBallSizeFail_high);
			fprintf( fp, "BallPositionMargin           %d\n", BallPositionMargin);
			fprintf( fp, "BallFindVal           %lf\n",BallFindVal);
			fprintf( fp, "WireSweepVal           %d\n", WireSweepVal);
			fprintf( fp, "ChipInsideWidth           %d\n", ChipInsideWidth);

			fprintf( fp, "BallSizeKernel		%d\n", BallSizeKernel );
			fprintf( fp, "NTCBallSizeKernel		%d\n", NTCBallSizeKernel );
			fprintf( fp, "BallSizeGain		%d\n", BallSizeGain );
			fprintf( fp, "BallAdapSize	%d\n", BallAdapSize );
			fprintf( fp, "BallAdapSize2		%d\n", BallAdapSize2 );
			fprintf( fp, "InsideChipOffest		%d\n", InsideChipOffest );


			fprintf( fp, "ALNBallPOSLeft_low             %lf\n" ,ALNBallPOSLeft_low   );
			fprintf( fp, "ALNBallPOSLeft_high             %lf\n",ALNBallPOSLeft_high  );
			fprintf( fp, "ALNBallPOSRight_low           %lf\n"  ,ALNBallPOSRight_low  );
			fprintf( fp, "ALNBallPOSRight_high           %lf\n" ,ALNBallPOSRight_high );
			fprintf( fp, "ALNBallPOSBottom_low          %lf\n"  ,ALNBallPOSBottom_low );
			fprintf( fp, "ALNBallPOSBottom_high          %lf\n" ,ALNBallPOSBottom_high);

			fprintf( fp, "[/DefectConst]\n" );

			fprintf(fp, "[WireConnect]\n");
			for (int i = 0; i<WireConnectListVal.size(); i++) {
				if (WireConnectListVal[i].info[0] == 0 || WireConnectListVal[i].info[1] == 0 || WireConnectListVal[i].info[2] == 0 || WireConnectListVal[i].info[3] == 0)
					continue;
				fprintf(fp, "Connect             %d %d %d %d \n", WireConnectListVal[i].info[0], WireConnectListVal[i].info[1], WireConnectListVal[i].info[2], WireConnectListVal[i].info[3]);

			}
			fprintf(fp, "[/WireConnect]\n\n");

			fprintf(fp, "[BoxMasking]\n");
			for (int i = 0; i<MaskingListVal.size(); i++) {
				fprintf(fp, "Masking             %d %d %d %d %d %d %d\n", MaskingListVal[i].type, MaskingListVal[i].X0Offeset, MaskingListVal[i].Y0Offeset, MaskingListVal[i].X1Offeset, MaskingListVal[i].Y1Offeset, MaskingListVal[i].Thick,  MaskingListVal[i].BoxNum);

			}
			fprintf(fp, "[/BoxMasking]\n\n");


			fprintf(fp, "[ConfigurationBEGIN]\n");
			fprintf(fp, "BallSizeMethod	%d\n", BallSizeMethod);
			fprintf(fp, "BallFindMethod	%d\n", BallFindMethod);
			fprintf(fp, "ChipTop			%d\n", ChipTop);
			fprintf(fp, "WireCheck			%d\n", WireCheck);
			fprintf(fp, "NTCSizeCheck		%d\n", NTCSizeCheck);
			fprintf(fp, "ALNSizeCheck		%d\n", ALNSizeCheck);
			fprintf(fp, "ChipSizeCheck		%d\n", ChipSizeCheck);
			fprintf(fp, "rotationImage		%d\n", rotationImage);
			fprintf(fp, "CoefficientGain	%lf\n", CoefficientGain);
			fprintf(fp, "ALNBallSize		%d\n", ALNBallSize);
			fprintf(fp, "BallSizeImg		%d\n", BallSizeImg);
			fprintf(fp, "ALNPositionCheck	%d\n", ALNPositionCheck);
			fprintf(fp, "ALNTestVer	%d\n", ALNTestVer);
			fprintf(fp, "GoldPadBottomCheck	%d\n", GoldPadBottomCheck);
			fprintf(fp, "[ConfigurationEND]\n");

			fclose( fp );

			AfxMessageBox(_T("Successfully Registered !"));
		}
	}
}

void CMakeINI_DefectDlg::OnBnClickedOk()	// NEW
{
	UpdateData(TRUE);

	CString strTmp = _T(""), strFind = _T("");
	int nIndex = m_ComboCon1.FindStringExact(-1, m_Combo1);
	if(nIndex != LB_ERR)
	{
		//m_Combo.GetLBText(nIndex, strFind);
		//strTmp.Format(_T("%d:%s"), nIndex, strFind);
		//AfxMessageBox(strTmp);
		AfxMessageBox(_T("NOTICE: Already Registered Name !"));
	}
	else
	{
		//AfxMessageBox(_T("일치하는 항목을 찾을 수 없습니다."));
		//콤보 박스와 리스트 박스에 모두 추가
		m_ComboCon1.AddString(m_Combo1);
		//UpdateData( FALSE );
	}
	//	m_List.AddString(m_strAddress);

	//입력 문자열 초기화
	//	m_Combo.SetEditSel(0, -1);
	//	m_Combo.Clear();
}


void CMakeINI_DefectDlg::OnBnClickedOk2()	// LOAD
{
	char	fname0[100], fname[100], DummyStr[100],ChkString[300];
	FILE	*fp;
	char INI_Name[1024],INI_source[1024];
	string iniString;
	UpdateData(TRUE);

	CString strTmp = _T(""), strFind = _T("");
	int nIndex = m_ComboCon1.FindStringExact(-1, m_Combo1);
	if(nIndex != LB_ERR)
	{
		//UpdateData();
		strcpy_s( fname0, 100, (char*)_bstr_t( m_Combo1 ) );
		//AfxMessageBox( m_Str );
		sprintf( fname, "./DefectFinder_BW.ini");
		fopen_s( &fp, fname, "r" );
		if( fp ) {

			fscanf( fp, "%s", ChkString );
			if( strcmp( ChkString, "[InformationBEGIN]" ) ) exit( -11 );
			fscanf( fp, "%s", ChkString );
			if( strcmp( ChkString, "VERSION" ) )			exit( -12 );
			fscanf( fp, "%s", ChkString );				//버젼
			fscanf( fp, "%s", ChkString );				// [InformationEND]

			fscanf( fp, "%s", ChkString );				// [AlgorithmSimulationBEGIN]
			if( !strcmp( ChkString, "[AlgorithmSimulationBEGIN]" ) ) {
				while( 1 ) {
					if( fscanf( fp, "%s", ChkString ) == EOF ) break;
					if( !strcmp( ChkString, "[AlgorithmSimulationEND]" ) ) break;
					if( !strcmp( ChkString, "##" ) ) {
						while( 1 ) if( getc( fp ) == '\n' ) break;
					}

					if( !strcmp( ChkString, "ImageFileType" ) )		 fscanf( fp, "%s %s\n", InputFileType, OutputFileType );
					if( !strcmp( ChkString, "ImageFolderPath" ) )	 fscanf( fp, "%s\n", input_directory );

				}
			}

			fscanf( fp, "%s", ChkString );
			if( !strcmp( ChkString, "[ConfigurationBEGIN]" ) ) {
				while( 1 ) {
					if( fscanf( fp, "%s", ChkString ) == EOF ) break;
					if( !strcmp( ChkString, "[ConfigurationEND]" ) ) break;
					if( !strcmp( ChkString, "##" ) ) {
						while( 1 ) if( getc( fp ) == '\n' ) break;
					}
					if( !strcmp( ChkString, "BallSizeMethod" ) )	fscanf( fp, "%d\n", &BallSizeMethod );
					if( !strcmp( ChkString, "BallFindMethod" ) )	fscanf( fp, "%d\n", &BallFindMethod );
					if( !strcmp( ChkString, "ChipTop" ) )			fscanf( fp, "%d\n", &ChipTop );
					if( !strcmp( ChkString, "WireCheck" ) )			fscanf( fp, "%d\n", &WireCheck );
					if( !strcmp( ChkString, "NTCSizeCheck" ) )		fscanf( fp, "%d\n", &NTCSizeCheck );
					if( !strcmp( ChkString, "ALNSizeCheck" ) )		fscanf( fp, "%d\n", &ALNSizeCheck );
					if( !strcmp( ChkString, "ChipSizeCheck" ) )		fscanf( fp, "%d\n", &ChipSizeCheck );
					if( !strcmp( ChkString, "rotationImage" ) )		fscanf( fp, "%d\n", &rotationImage );
					if( !strcmp( ChkString, "CoefficientGain" ) )	fscanf( fp, "%lf\n", &CoefficientGain );
					if( !strcmp( ChkString, "ALNBallSize" ) )		fscanf( fp, "%d\n", &ALNBallSize );
					if( !strcmp( ChkString, "BallSizeImg" ) )		fscanf( fp, "%d\n", &BallSizeImg );
					if( !strcmp( ChkString, "ALNPositionCheck" ) )	fscanf( fp, "%d\n", &ALNPositionCheck );
					if( !strcmp( ChkString, "ALNTestVer" ) )		fscanf( fp, "%d\n", &ALNTestVer );
					if( !strcmp( ChkString, "GoldPadBottomCheck" ) )		fscanf( fp, "%d\n", &GoldPadBottomCheck );
				}
			}
			fclose( fp );
		}

		sprintf( fname, "./DB/%s/INI/BallWire.ini", fname0);
		fopen_s( &fp, fname, "r" );
		if( fp ) {

			BoxInfo buffer;
			BoxInfoListVal.clear();

			fscanf( fp, "%s", ChkString );
			if( !strcmp( ChkString, "[BoxOffset]" ) ) {
				int i = 1;
				while( 1 ) {
					if( fscanf( fp, "%s", ChkString ) == EOF ) break;
					if( !strcmp( ChkString, "[/BoxOffset]" ) ) break;
					if( !strcmp( ChkString, "##" ) ) {
						while( 1 ) if( getc( fp ) == '\n' ) break;
					}
					

					iniString = "Box["+intToString(i)+"].p1x";// %d\n";
					if( !strcmp( ChkString, iniString.c_str() ) )
						fscanf_s( fp, "%d\n", &buffer.X0Offeset );	


					if( fscanf( fp, "%s", ChkString ) == EOF ) break;
					if( !strcmp( ChkString, "[/BoxOffset]" ) ) break;
					if( !strcmp( ChkString, "##" ) ) {
						while( 1 ) if( getc( fp ) == '\n' ) break;
					}
					iniString = "Box["+intToString(i)+"].p1y";// %d\n";
					if( !strcmp( ChkString, iniString.c_str() ) )
						fscanf_s( fp, "%d\n", &buffer.Y0Offeset );


					if( fscanf( fp, "%s", ChkString ) == EOF ) break;
					if( !strcmp( ChkString, "[/BoxOffset]" ) ) break;
					if( !strcmp( ChkString, "##" ) ) {
						while( 1 ) if( getc( fp ) == '\n' ) break;
					}
					iniString = "Box["+intToString(i)+"].p2x";// %d\n";
					if( !strcmp( ChkString, iniString.c_str() ) )
						fscanf_s( fp, "%d\n", &buffer.X1Offeset );


					if( fscanf( fp, "%s", ChkString ) == EOF ) break;
					if( !strcmp( ChkString, "[/BoxOffset]" ) ) break;
					if( !strcmp( ChkString, "##" ) ) {
						while( 1 ) if( getc( fp ) == '\n' ) break;
					}
					iniString = "Box["+intToString(i)+"].p2y";// %d\n";
					if( !strcmp( ChkString, iniString.c_str() ) )
						fscanf_s( fp, "%d\n", &buffer.Y1Offeset );


					if( fscanf( fp, "%s", ChkString ) == EOF ) break;
					if( !strcmp( ChkString, "[/BoxOffset]" ) ) break;
					if( !strcmp( ChkString, "##" ) ) {
						while( 1 ) if( getc( fp ) == '\n' ) break;
					}
					iniString = "BoxInfo["+intToString(i)+"]";// %d\n";
					if( !strcmp( ChkString, iniString.c_str() ) )
						fscanf_s( fp, "%d\n", &buffer.BallNum);


					if( fscanf( fp, "%s", ChkString ) == EOF ) break;
					if( !strcmp( ChkString, "[/BoxOffset]" ) ) break;
					if( !strcmp( ChkString, "##" ) ) {
						while( 1 ) if( getc( fp ) == '\n' ) break;
					}
					iniString = "BoxDirection["+intToString(i)+"]";// %d\n";
					if( !strcmp( ChkString, iniString.c_str() ) )
						fscanf_s( fp, "%d\n", &buffer.Direction);


					if( fscanf( fp, "%s", ChkString ) == EOF ) break;
					if( !strcmp( ChkString, "[/BoxOffset]" ) ) break;
					if( !strcmp( ChkString, "##" ) ) {
						while( 1 ) if( getc( fp ) == '\n' ) break;
					}
					iniString = "BoxThresh["+intToString(i)+"]";// %d\n";
					if( !strcmp( ChkString, iniString.c_str() ) )
						fscanf_s( fp, "%lf\n", &buffer.Threshold);

					BoxInfoListVal.push_back(buffer);
					i++;

				}
			}
			fscanf( fp, "%s", ChkString );
			if( !strcmp( ChkString, "[DefectConst]" ) ) {
				while( 1 ) {
					if( fscanf( fp, "%s", ChkString ) == EOF ) break;
					if( !strcmp( ChkString, "[/DefectConst]" ) ) break;
					if( !strcmp( ChkString, "##" ) ) {
						while( 1 ) if( getc( fp ) == '\n' ) break;
					}

					if( !strcmp( ChkString, "ChipBallSizeFail_low" ) )		fscanf( fp, "%lf\n", &ChipBallSizeFail_low);
					if( !strcmp( ChkString, "ChipBallSizeFail_high" ) )		fscanf( fp, "%lf\n", &ChipBallSizeFail_high);
					if( !strcmp( ChkString, "NTCBallSizeFail_low" ) )		fscanf( fp, "%lf\n", &NTCBallSizeFail_low);
					if( !strcmp( ChkString, "NTCBallSizeFail_high" ) )		fscanf( fp, "%lf\n", &NTCBallSizeFail_high);
					if( !strcmp( ChkString, "ALNBallSizeFail_low" ) )		fscanf( fp, "%lf\n", &ALNBallSizeFail_low);
					if( !strcmp( ChkString, "ALNBallSizeFail_high" ) )		fscanf( fp, "%lf\n", &ALNBallSizeFail_high);
					if( !strcmp( ChkString, "BallPositionMargin" ) )		fscanf( fp, "%d\n",  &BallPositionMargin);
					if( !strcmp( ChkString, "BallFindVal" ) )				fscanf( fp, "%lf\n", &BallFindVal);
					if( !strcmp( ChkString, "WireSweepVal" ) )				fscanf( fp, "%d\n",  &WireSweepVal);
					if( !strcmp( ChkString, "ChipInsideWidth" ) )			fscanf( fp, "%d\n",  &ChipInsideWidth);
				
					if( !strcmp( ChkString, "BallSizeKernel" ) )			fscanf( fp, "%d\n", &BallSizeKernel );
					if( !strcmp( ChkString, "NTCBallSizeKernel" ) )			fscanf( fp, "%d\n", &NTCBallSizeKernel );
					if( !strcmp( ChkString, "BallSizeGain" ) )				fscanf( fp, "%d\n", &BallSizeGain );
					if( !strcmp( ChkString, "BallAdapSize" ) )				fscanf( fp, "%d\n", &BallAdapSize );
					if( !strcmp( ChkString, "BallAdapSize2" ) )				fscanf( fp, "%d\n", &BallAdapSize2 );
					if( !strcmp( ChkString, "InsideChipOffest" ) )			fscanf( fp, "%d\n", &InsideChipOffest );
					
					if( !strcmp( ChkString, "ALNBallPOSLeft_low") )			fscanf( fp, "%lf\n", &ALNBallPOSLeft_low   	);
					if( !strcmp( ChkString, "ALNBallPOSLeft_high") )		fscanf( fp, "%lf\n", &ALNBallPOSLeft_high  	);
					if( !strcmp( ChkString, "ALNBallPOSRight_low") )		fscanf( fp, "%lf\n", &ALNBallPOSRight_low  	);
					if( !strcmp( ChkString, "ALNBallPOSRight_high") )		fscanf( fp, "%lf\n", &ALNBallPOSRight_high 	);
					if( !strcmp( ChkString, "ALNBallPOSBottom_low") )		fscanf( fp, "%lf\n", &ALNBallPOSBottom_low 	);
					if( !strcmp( ChkString, "ALNBallPOSBottom_high") )		fscanf( fp, "%lf\n", &ALNBallPOSBottom_high	);

				}
			}
			WireConnectInfo tmp;
			WireConnectListVal.clear();
			fscanf(fp, "%s", ChkString);
			if (!strcmp(ChkString, "[WireConnect]")) {
				while (1) {
					if (fscanf(fp, "%s", ChkString) == EOF) break;
					if (!strcmp(ChkString, "[/WireConnect]")) break;
					if (!strcmp(ChkString, "##")) {
						while (1) if (getc(fp) == '\n') break;
					}
					if (!strcmp(ChkString, "Connect")) {
						fscanf(fp, "%d %d %d %d\n", &tmp.info[0], &tmp.info[1], &tmp.info[2], &tmp.info[3]);
						WireConnectListVal.push_back(tmp);
					}
				}
			}
			MaskInfo mask_tmp;
			MaskingListVal.clear();
			fscanf(fp, "%s", ChkString);
			if (!strcmp(ChkString, "[BoxMasking]")) {
				while (1) {
					if (fscanf(fp, "%s", ChkString) == EOF) break;
					if (!strcmp(ChkString, "[/BoxMasking]")) break;
					if (!strcmp(ChkString, "##")) {
						while (1) if (getc(fp) == '\n') break;
					}
					if (!strcmp(ChkString, "Masking")) {
						fscanf(fp, "%d %d %d %d %d %d %d\n", &mask_tmp.type, &mask_tmp.X0Offeset, &mask_tmp.Y0Offeset, &mask_tmp.X1Offeset, &mask_tmp.Y1Offeset, &mask_tmp.Thick, &mask_tmp.BoxNum);
						MaskingListVal.push_back(mask_tmp);
					}
				}
			}
			fscanf(fp, "%s", ChkString);
			if (!strcmp(ChkString, "[ConfigurationBEGIN]")) {
				while (1) {
					if (fscanf(fp, "%s", ChkString) == EOF) break;
					if (!strcmp(ChkString, "[ConfigurationEND]")) break;
					if (!strcmp(ChkString, "##")) {
						while (1) if (getc(fp) == '\n') break;
					}
					if (!strcmp(ChkString, "BallSizeMethod"))	fscanf(fp, "%d\n", &BallSizeMethod);
					if (!strcmp(ChkString, "BallFindMethod"))	fscanf(fp, "%d\n", &BallFindMethod);
					if (!strcmp(ChkString, "ChipTop"))			fscanf(fp, "%d\n", &ChipTop);
					if (!strcmp(ChkString, "WireCheck"))			fscanf(fp, "%d\n", &WireCheck);
					if (!strcmp(ChkString, "NTCSizeCheck"))		fscanf(fp, "%d\n", &NTCSizeCheck);
					if (!strcmp(ChkString, "ALNSizeCheck"))		fscanf(fp, "%d\n", &ALNSizeCheck);
					if (!strcmp(ChkString, "ChipSizeCheck"))		fscanf(fp, "%d\n", &ChipSizeCheck);
					if (!strcmp(ChkString, "rotationImage"))		fscanf(fp, "%d\n", &rotationImage);
					if (!strcmp(ChkString, "CoefficientGain"))	fscanf(fp, "%lf\n", &CoefficientGain);
					if (!strcmp(ChkString, "ALNBallSize"))		fscanf(fp, "%d\n", &ALNBallSize);
					if (!strcmp(ChkString, "BallSizeImg"))		fscanf(fp, "%d\n", &BallSizeImg);
					if (!strcmp(ChkString, "ALNPositionCheck"))	fscanf(fp, "%d\n", &ALNPositionCheck);
					if (!strcmp(ChkString, "ALNTestVer"))		fscanf(fp, "%d\n", &ALNTestVer);
					if (!strcmp(ChkString, "GoldPadBottomCheck"))		fscanf(fp, "%d\n", &GoldPadBottomCheck);
				}
			}
		}


		fclose( fp );


		//m_formFirst.UpdateData( FALSE );

		m_BallWire.UpdateData( FALSE );
		m_Defect_BW.UpdateData( FALSE );
		m_WireConnect.UpdateData(FALSE);
		m_Masking.UpdateData(FALSE);
		m_Defect_BW.PutData();
		m_BallWire.PutData();
		m_WireConnect.PutData();
		m_Masking.PutData();
	}
	else
	{
		AfxMessageBox(_T("Specified File Not Existed !"));
	}
}


BOOL CMakeINI_DefectDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN){
		if(pMsg->wParam == VK_RETURN){
			if(pMsg->hwnd == GetDlgItem(IDC_EDIT1)->GetSafeHwnd())
			{
				CString str;
				GetDlgItemText(IDC_EDIT1, str);
				m_WireConnect.m_WireConnectList.SetItemText(m_WireConnect.iSavedItem, m_WireConnect.iSavedSubitem, str);
				WireConnectListVal[m_WireConnect.iSavedItem].info[m_WireConnect.iSavedSubitem-1] = _ttoi(str);
				GetDlgItem(IDC_EDIT1)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW );
				m_WireConnect.PutData();
			}
			return TRUE;
		}
		if(pMsg->wParam == VK_ESCAPE)
		{
			SetDlgItemText(IDC_EDIT1, _T(""));
			GetDlgItem(IDC_EDIT1)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW );
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

string CMakeINI_DefectDlg::intToString(int n)
{
	stringstream s;
	s << n;
	return s.str();
}