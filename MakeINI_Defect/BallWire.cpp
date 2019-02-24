// BallWire.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BallWire.h"
#include "afxdialogex.h"
#include "MakeINI_Defect.h"

// CBallWire 대화 상자입니다.

IMPLEMENT_DYNAMIC(CBallWire, CDialog)

	CBallWire::CBallWire(CWnd* pParent /*=NULL*/)
	: CDialog(CBallWire::IDD, pParent)
	, m_X0Offeset()
	, m_X1Offeset()
	, m_Y0Offeset()
	, m_Y1Offeset()
	, m_BallNum()
	, m_Threshold()
	, m_Direction()
{
}

CBallWire::~CBallWire()
{
}

void CBallWire::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT20, m_X0Offeset);
	DDX_Text(pDX, IDC_EDIT21, m_Y0Offeset);
	DDX_Text(pDX, IDC_EDIT22, m_X1Offeset);
	DDX_Text(pDX, IDC_EDIT23, m_Y1Offeset);
	DDX_Text(pDX, IDC_EDIT24,   m_BallNum);
	DDX_Text(pDX, IDC_EDIT26, m_Threshold);
	DDX_CBIndex(pDX, IDC_COMBO5, m_Direction);
	DDX_CBIndex(pDX, IDC_COMBO6, ListComboVal);
	DDX_Control(pDX, IDC_LIST2, m_BoxInfoList);
}

BEGIN_MESSAGE_MAP(CBallWire, CDialog)
	ON_EN_CHANGE(IDC_EDIT20 , &CBallWire::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT21 , &CBallWire::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT22 , &CBallWire::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT23 , &CBallWire::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT24 , &CBallWire::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT26 , &CBallWire::OnEnChangeEdit)

	ON_BN_CLICKED(IDC_BUTTON1, &CBallWire::OnBnClickedAddBox)
	ON_BN_CLICKED(IDC_BUTTON2, &CBallWire::OnBnClickedDeleteBox)
	ON_BN_CLICKED(IDC_BUTTON3, &CBallWire::OnBnClickedDeleteAll)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CBallWire::OnDblclkList2)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CBallWire::OnClickList2)
	ON_CBN_CLOSEUP(IDC_COMBO6, &CBallWire::OnCloseupCombo6)
	ON_CBN_SETFOCUS(IDC_COMBO6, &CBallWire::OnCbnSetfocusCombo6)
	ON_CBN_DROPDOWN(IDC_COMBO6, &CBallWire::OnCbnDropdownCombo6)
END_MESSAGE_MAP()


// CBallWire 메시지 처리기입니다.


void CBallWire::OnEnChangeEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();


	BoxInfoListVal.clear();
	BoxInfoListVal.reserve( m_BoxInfoListVal.size());
	BoxInfo buffer;
	for(int i=0; i<m_BoxInfoListVal.size(); i++){
		buffer.X0Offeset = m_BoxInfoListVal[i].X0Offeset;
		buffer.X1Offeset = m_BoxInfoListVal[i].X1Offeset;
		buffer.Y0Offeset = m_BoxInfoListVal[i].Y0Offeset;
		buffer.Y1Offeset = m_BoxInfoListVal[i].Y1Offeset;
		buffer.BallNum   = m_BoxInfoListVal[i].BallNum  ;
		buffer.Threshold = m_BoxInfoListVal[i].Threshold;
		buffer.Direction = m_BoxInfoListVal[i].Direction;	
		BoxInfoListVal.push_back(buffer);
	}


}
void CBallWire::PutData(){
	UpdateData(TRUE);
	m_BoxInfoList.DeleteAllItems();
	m_BoxInfoListVal.clear();
	m_BoxInfoListVal.reserve( BoxInfoListVal.size());
	BoxInfo buffer;
	for(int i=0; i<BoxInfoListVal.size(); i++){		
		buffer.X0Offeset = BoxInfoListVal[i].X0Offeset;
		buffer.X1Offeset = BoxInfoListVal[i].X1Offeset;
		buffer.Y0Offeset = BoxInfoListVal[i].Y0Offeset;
		buffer.Y1Offeset = BoxInfoListVal[i].Y1Offeset;
		buffer.BallNum   = BoxInfoListVal[i].BallNum  ;
		buffer.Threshold = BoxInfoListVal[i].Threshold;
		buffer.Direction = BoxInfoListVal[i].Direction;	
		m_BoxInfoListVal.push_back(buffer);
	}
	UpdateData( FALSE );

	char szText[50]="";  //문자열을 저장할 변수 선언
	//int nIndex=0;  //목록의 인덱스를 저장할 변수선언
	string direction_list[10];
	direction_list[0] = "GOLDPAD";
	direction_list[1] = "GOLDPAD_BOTTOM";
	direction_list[2] = "VCSEL_LFT";
	direction_list[3] = "VCSEL_RGT";
	direction_list[4] = "ALN";
	direction_list[5] = "NTC_TOP";
	direction_list[6] = "NTC_BOTTOM";
	UpdateData(TRUE);
	for(int i=0; i<m_BoxInfoListVal.size(); i++){
		LVITEM lItem;  //이 구조체를 이용해서 목록에 대한 정보를 작성

		lItem.mask=LVIF_TEXT;  //이 구조체의 pszText확장
		lItem.iItem=i;  //목록의 번호를 지정
		lItem.iSubItem=0;  //세부 항목의 번호를 지정-최상목록이므로 0을 줍니다.
		sprintf_s(szText,"%d",i+1);  //m_strName변수가 CSstrin형이라 szText변수로 바로 값을 전송할 수가 없다. 따라서 sprintf()함수이용
		wchar_t* wStringFrom=new wchar_t[50];
		MultiByteToWideChar(CP_ACP, 0, szText, -1, wStringFrom, 50);
		lItem.pszText=wStringFrom;  //목록내용 지정
		m_BoxInfoList.InsertItem(&lItem);   //최상목록추가

		for(int j=0; j<7; j++){
			lItem.iSubItem=j+1;  //세부 항목의 번호를 지정-최상목록이므로 0을 줍니다.
			//sprintf(szText,"%d",m_BoxInfoListVal[i].info[j]);  //m_strName변수가 CSstrin형이라 szText변수로 바로 값을 전송할 수가 없다. 따라서 sprintf()함수이용
			switch(j){
			case 0 : sprintf_s(szText,"%d"   ,m_BoxInfoListVal[i].X0Offeset);break;
			case 1 : sprintf_s(szText,"%d",   m_BoxInfoListVal[i].Y0Offeset);break;
			case 2 : sprintf_s(szText,"%d",   m_BoxInfoListVal[i].X1Offeset);break;
			case 3 : sprintf_s(szText,"%d",   m_BoxInfoListVal[i].Y1Offeset);break;
			case 4 : sprintf_s(szText,"%.2lf",m_BoxInfoListVal[i].Threshold);break;
			case 5 : sprintf_s(szText,"%d"   ,m_BoxInfoListVal[i].BallNum  );break;
			case 6: sprintf_s(szText, "%s", direction_list[m_BoxInfoListVal[i].Direction].c_str()); break;
			//case 6: sprintf_s(szText, "%d", m_BoxInfoListVal[i].Direction); break;
			}

			MultiByteToWideChar(CP_ACP, 0, szText, -1, wStringFrom, 50);
			lItem.pszText=wStringFrom;  //목록내용 지정
			m_BoxInfoList.SetItem(&lItem);  //하위목록추가는 SetItem함수를 사용
		}
	}

	//추가할 아이템 넣기


	//nIndex++;   //새로운목록추가하기위해 1증가
	UpdateData(FALSE);
}

BOOL CBallWire::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN){
		if(pMsg->wParam == VK_RETURN){
			if(pMsg->hwnd == GetDlgItem(IDC_EDIT1)->GetSafeHwnd())
			{
				if(iSavedSubitem == 0){
					char ProcTime[500];
					sprintf_s( ProcTime, "don't touch this, man~" );
					AfxMessageBox((CString)(ProcTime));
				}
				else{
					CString str;
					GetDlgItemText(IDC_EDIT1, str);
					m_BoxInfoList.SetItemText(iSavedItem, iSavedSubitem, str);
					switch(iSavedSubitem-1){
					case 0 : BoxInfoListVal[iSavedItem].X0Offeset = _ttoi(str);break;
					case 1 : BoxInfoListVal[iSavedItem].Y0Offeset = _ttoi(str);break;
					case 2 : BoxInfoListVal[iSavedItem].X1Offeset = _ttoi(str);break;
					case 3 : BoxInfoListVal[iSavedItem].Y1Offeset = _ttoi(str);break;
					case 4 : BoxInfoListVal[iSavedItem].Threshold = _ttoi(str);break;
					case 5 : BoxInfoListVal[iSavedItem].BallNum   = _ttoi(str);break;
					case 6 : BoxInfoListVal[iSavedItem].Direction = _ttoi(str);break;
					}
					GetDlgItem(IDC_EDIT1)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW );
					PutData();
				}
			}
			else if(pMsg->hwnd == GetDlgItem(IDC_COMBO6)->GetSafeHwnd())
			{
				CString str;
				CComboBox* m_CbCombo = (CComboBox*)GetDlgItem(IDC_COMBO6);

				int nIndex = m_CbCombo->GetCurSel();

				BoxInfoListVal[iSavedItem].Direction = ListComboVal = nIndex;
				PutData();

				GetDlgItem(IDC_COMBO6)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
			}
			return TRUE;
		}
		if(pMsg->wParam == VK_ESCAPE)
		{
			SetDlgItemText(IDC_EDIT1, _T(""));
			GetDlgItem(IDC_EDIT1)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
			GetDlgItem(IDC_COMBO6)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
			return TRUE;
		}
	}
	//if(pMsg->message == WM_LBUTTONDOWN && pMsg->hwnd == GetDlgItem(IDC_COMBO6)->m_hWnd){
	// // 아무런 처리 없이 그냥 return 한다.
	// CString str;
	// GetDlgItemText(IDC_COMBO6, str);
	//
	// ListComboVal = _ttoi(str);
	// PutData();
	// return TRUE;
	//}

	return CDialog::PreTranslateMessage(pMsg);
}


void CBallWire::OnBnClickedAddBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	BoxInfo tmp;
	tmp.X0Offeset = m_X0Offeset;
	tmp.X1Offeset = m_X1Offeset;
	tmp.Y0Offeset = m_Y0Offeset;
	tmp.Y1Offeset = m_Y1Offeset;
	tmp.BallNum   = m_BallNum  ;
	tmp.Threshold = m_Threshold;
	tmp.Direction = m_Direction;

	int index = m_BoxInfoList.GetSelectionMark(); 
	if(index == -1 )
		BoxInfoListVal.push_back(tmp);
	else
		BoxInfoListVal.insert(BoxInfoListVal.begin()+index,tmp);


	PutData();
}



void CBallWire::OnBnClickedDeleteBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = m_BoxInfoList.GetSelectionMark(); 
	char ProcTime[500];
	sprintf_s( ProcTime, " Choice Number " );
	if(index == -1)
		AfxMessageBox((CString)(ProcTime));
	else{
		BoxInfoListVal.erase(BoxInfoListVal.begin()+index);//a.erase(a.begin()+i); 
		PutData();
	}
}


void CBallWire::OnBnClickedDeleteAll()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BoxInfoListVal.clear();
	PutData();
}


void CBallWire::OnDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	LPNMITEMACTIVATE pNMITEM = (LPNMITEMACTIVATE) pNMHDR;
	iSavedItem = pNMITEM->iItem;
	iSavedSubitem = pNMITEM->iSubItem;
	if(pNMITEM->iItem != -1)
	{
		CRect rect;
		if(pNMITEM->iSubItem == 0)
		{
			m_BoxInfoList.GetItemRect(pNMITEM->iItem, rect, LVIR_BOUNDS);
			rect.right = rect.left + m_BoxInfoList.GetColumnWidth(0);
		}
		else
		{
			m_BoxInfoList.GetSubItemRect(pNMITEM->iItem, pNMITEM->iSubItem, LVIR_BOUNDS, rect);
		}
		m_BoxInfoList.ClientToScreen(rect);
		this->ScreenToClient(rect);
		GetDlgItem(IDC_EDIT1)->SetWindowText(m_BoxInfoList.GetItemText(pNMITEM->iItem, pNMITEM->iSubItem));
		GetDlgItem(IDC_EDIT1)->SetWindowPos(NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW );
		GetDlgItem(IDC_EDIT1)->SetFocus();
	}
	*pResult = 0;
}



void CBallWire::OnClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	LPNMITEMACTIVATE pNMITEM = (LPNMITEMACTIVATE) pNMHDR;
	iSavedItem = pNMITEM->iItem;
	iSavedSubitem = pNMITEM->iSubItem;
	GetDlgItem(IDC_EDIT1)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW );
	GetDlgItem(IDC_COMBO6)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW );
	if(pNMITEM->iItem != -1)
	{
		if(iSavedSubitem == 7)
		{
			CRect rect;
			m_BoxInfoList.GetSubItemRect(pNMITEM->iItem, pNMITEM->iSubItem, LVIR_BOUNDS, rect);
			m_BoxInfoList.ClientToScreen(rect);
			this->ScreenToClient(rect);
			GetDlgItem(IDC_COMBO6)->SetWindowText(m_BoxInfoList.GetItemText(pNMITEM->iItem, pNMITEM->iSubItem));
			//int tt,tmp;
			//m_BoxInfoList;
			//tt = m_BoxInfoList.GetScrollPos(tmp);
			//tt;
			CString str;
			//char ProcTime[500];
			//sprintf_s( ProcTime, "fucucucucucuck %d",tmp );
			//AfxMessageBox((CString)(ProcTime));
			//GetDlgItemText(IDC_COMBO6, str);
			str = m_BoxInfoList.GetItemText(pNMITEM->iItem, pNMITEM->iSubItem);
			ListComboVal = _ttoi(str);;
			ListComboVal = BoxInfoListVal[iSavedItem].Direction;
			GetDlgItem(IDC_COMBO6)->SetWindowPos(NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW );
			GetDlgItem(IDC_COMBO6)->SetFocus();
			
		}
		else
		{
			SetDlgItemText(IDC_EDIT1, _T(""));
			GetDlgItem(IDC_COMBO6)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW );
		}
		UpdateData(FALSE);
	}
	*pResult = 0;
}


void CBallWire::OnCloseupCombo6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	CComboBox* m_CbCombo = (CComboBox*)GetDlgItem(IDC_COMBO6);

	int nIndex = m_CbCombo->GetCurSel();

	BoxInfoListVal[iSavedItem].Direction = ListComboVal = nIndex;
	PutData();
	GetDlgItem(IDC_COMBO6)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
}


void CBallWire::OnCbnSetfocusCombo6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CBallWire::OnCbnDropdownCombo6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	CComboBox* m_CbCombo = (CComboBox*)GetDlgItem(IDC_COMBO6);
	m_CbCombo->SetCurSel(BoxInfoListVal[iSavedItem].Direction);
	;
}
