// WireConnect.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "WireConnect.h"
#include "afxdialogex.h"
#include "MakeINI_Defect.h"


// WireConnect 대화 상자입니다.

IMPLEMENT_DYNAMIC(WireConnect, CDialog)

WireConnect::WireConnect(CWnd* pParent /*=NULL*/)
	: CDialog(WireConnect::IDD, pParent)
	, m_BOX1()
	, m_BOX2()
	, m_Ord1()
	, m_Ord2()
{

}

WireConnect::~WireConnect()
{
}

void WireConnect::DoDataExchange(CDataExchange* pDX)
{

	

	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_WireConnectList);
	DDX_Text(pDX, IDC_EDIT6 , m_BOX1);
	DDX_Text(pDX, IDC_EDIT7 , m_Ord1);
	DDX_Text(pDX, IDC_EDIT8 , m_BOX2);
	DDX_Text(pDX, IDC_EDIT9 , m_Ord2);
}


BEGIN_MESSAGE_MAP(WireConnect, CDialog)
	
	ON_BN_CLICKED(IDC_BUTTON1, &WireConnect::OnBnClickedAddList)
	ON_BN_CLICKED(IDC_BUTTON2, &WireConnect::OnBnClickedDeleteList)
	ON_BN_CLICKED(IDC_BUTTON3, &WireConnect::OnBnClickedModify)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST2, &WireConnect::OnEndlabeleditList2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &WireConnect::OnNMDblclkList2)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &WireConnect::OnNMClickList2)
END_MESSAGE_MAP()


// WireConnect 메시지 처리기입니다.


void WireConnect::OnEnChangeEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	//for(int i=0; i<36; i++){
	//	BOX1[i] = m_BOX1[i];
	//	BOX2[i] = m_BOX2[i];
	//	Ord1[i] = m_Ord1[i];
	//	Ord2[i] = m_Ord2[i];
	//}
	WireConnectListVal.clear();
	WireConnectListVal.reserve( m_WireConnectListVal.size());
	WireConnectInfo buffer;
	for(int i=0; i<m_WireConnectListVal.size(); i++){
		for(int j=0; j<4; j++){
			buffer.info[j] = m_WireConnectListVal[i].info[j];
		}
		WireConnectListVal.push_back(buffer);
	}
}

void WireConnect::PutData(){

	m_WireConnectList.DeleteAllItems();
	m_WireConnectListVal.clear();
	m_WireConnectListVal.reserve( WireConnectListVal.size());
	WireConnectInfo buffer;
	for(int i=0; i<WireConnectListVal.size(); i++){
		for(int j=0; j<4; j++){
			buffer.info[j] = WireConnectListVal[i].info[j];
		}
		m_WireConnectListVal.push_back(buffer);
	}
	UpdateData( FALSE );
	
	char szText[50]="";  //문자열을 저장할 변수 선언
	//int nIndex=0;  //목록의 인덱스를 저장할 변수선언

	UpdateData(TRUE);
	for(int i=0; i<m_WireConnectListVal.size(); i++){
		LVITEM lItem;  //이 구조체를 이용해서 목록에 대한 정보를 작성

		lItem.mask=LVIF_TEXT;  //이 구조체의 pszText확장
		lItem.iItem=i;  //목록의 번호를 지정

		lItem.iSubItem=0;  //세부 항목의 번호를 지정-최상목록이므로 0을 줍니다.
		sprintf(szText,"%d",i+1);  //m_strName변수가 CSstrin형이라 szText변수로 바로 값을 전송할 수가 없다. 따라서 sprintf()함수이용
		wchar_t* wStringFrom=new wchar_t[50];
		MultiByteToWideChar(CP_ACP, 0, szText, -1, wStringFrom, 50);
		lItem.pszText=wStringFrom;  //목록내용 지정
		m_WireConnectList.InsertItem(&lItem);   //최상목록추가

		for(int j=0; j<4; j++){
			lItem.iSubItem=j+1;  //세부 항목의 번호를 지정-최상목록이므로 0을 줍니다.
			sprintf(szText,"%d",m_WireConnectListVal[i].info[j]);  //m_strName변수가 CSstrin형이라 szText변수로 바로 값을 전송할 수가 없다. 따라서 sprintf()함수이용
			MultiByteToWideChar(CP_ACP, 0, szText, -1, wStringFrom, 50);
			lItem.pszText=wStringFrom;  //목록내용 지정
			m_WireConnectList.SetItem(&lItem);  //하위목록추가는 SetItem함수를 사용
		}
	}
	//추가할 아이템 넣기


	//nIndex++;   //새로운목록추가하기위해 1증가
	UpdateData(FALSE);



//출처: http://ewst.tistory.com/entry/MFC-ListBox-Column에-목록추가 [Memory]


}


void WireConnect::OnBnClickedAddList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	WireConnectInfo tmp;
	tmp.info[0] = m_BOX1;
	tmp.info[1] = m_Ord1;
	tmp.info[2] = m_BOX2;
	tmp.info[3] = m_Ord2;
	int index = m_WireConnectList.GetSelectionMark(); 
	if(m_BOX1 == 0 || m_Ord1 == 0 || m_BOX2 == 0 || m_Ord2 == 0){
		AfxMessageBox(_T("포함할 수 없는 범위를 입력하셨습니다. (0)"));
		


	}
	else{
		
	if(index == -1 )
		WireConnectListVal.push_back(tmp);
	else
		WireConnectListVal.insert(WireConnectListVal.begin()+index,tmp);
	PutData();
	}
	
}


void WireConnect::OnBnClickedDeleteList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = m_WireConnectList.GetSelectionMark(); 
	char ProcTime[500];
	sprintf( ProcTime, " Choice Number " );
	if(index == -1)
		AfxMessageBox((CString)(ProcTime));
	else{
		WireConnectListVal.erase(WireConnectListVal.begin()+index);//a.erase(a.begin()+i); 
		PutData();
	}

	//m_WireConnectList.DeleteAllItems();

}


void WireConnect::OnBnClickedModify()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	WireConnectListVal.clear();
	PutData();

}



void WireConnect::OnEndlabeleditList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//pDispInfo->item.iItem
	m_WireConnectList.SetFocus();
	m_WireConnectList.EditLabel(pDispInfo->item.iItem);

	int index = m_WireConnectList.GetSelectionMark(); 
	char ProcTime[500];
	sprintf( ProcTime, " Select %d index", index );
	AfxMessageBox((CString)(ProcTime));

	m_WireConnectList.SetItemText(pDispInfo->item.iItem, 0, pDispInfo->item.pszText);
	//출처: http://disclosure.tistory.com/entry/리스트-컨트롤-선택하여-수정하기 [HK Study Room :)]
	*pResult = 0;
}


void WireConnect::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//m_WireConnectList.getsel
	LPNMITEMACTIVATE pNMITEM = (LPNMITEMACTIVATE) pNMHDR;
	iSavedItem = pNMITEM->iItem;
	iSavedSubitem = pNMITEM->iSubItem;
	if(pNMITEM->iItem != -1)
	{
		CRect rect;
		if(pNMITEM->iSubItem == 0)
		{
			m_WireConnectList.GetItemRect(pNMITEM->iItem, rect, LVIR_BOUNDS);
			rect.right = rect.left + m_WireConnectList.GetColumnWidth(0);
		}
		else
		{
			m_WireConnectList.GetSubItemRect(pNMITEM->iItem, pNMITEM->iSubItem, LVIR_BOUNDS, rect);
		}
		m_WireConnectList.ClientToScreen(rect);
		this->ScreenToClient(rect);
		GetDlgItem(IDC_EDIT1)->SetWindowText(m_WireConnectList.GetItemText(pNMITEM->iItem, pNMITEM->iSubItem));
		GetDlgItem(IDC_EDIT1)->SetWindowPos(NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW );
		GetDlgItem(IDC_EDIT1)->SetFocus();
	}
	

	*pResult = 0;
}


BOOL WireConnect::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN){
		if(pMsg->wParam == VK_RETURN){
			if(pMsg->hwnd == GetDlgItem(IDC_EDIT1)->GetSafeHwnd())
			{
				if(iSavedSubitem == 0){
					char ProcTime[500];
					sprintf( ProcTime, "don't touch this, man~" );
					AfxMessageBox((CString)(ProcTime));
				}
				else{
					CString str;
					GetDlgItemText(IDC_EDIT1, str);
					m_WireConnectList.SetItemText(iSavedItem, iSavedSubitem, str);
					WireConnectListVal[iSavedItem].info[iSavedSubitem-1] = _ttoi(str);
					GetDlgItem(IDC_EDIT1)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW );
					PutData();
				}
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

	return CDialog::PreTranslateMessage(pMsg);
}


void WireConnect::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetDlgItemText(IDC_EDIT1, _T(""));
	GetDlgItem(IDC_EDIT1)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
	*pResult = 0;
}
