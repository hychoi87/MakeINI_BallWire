// Masking.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Masking.h"
#include "afxdialogex.h"


// Masking 대화 상자입니다.

IMPLEMENT_DYNAMIC(Masking, CDialog)

Masking::Masking(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG6, pParent)
	, m_X0Offeset(0)
	, m_X1Offeset(0)
	, m_Y0Offeset(0)
	, m_Y1Offeset(0)
	, m_Thick(0)
	, m_BoxNum(0)
	, m_type(0)
{

}

Masking::~Masking()
{
}

void Masking::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT20, m_X0Offeset);
	DDX_Text(pDX, IDC_EDIT21, m_Y0Offeset);
	DDX_Text(pDX, IDC_EDIT22, m_X1Offeset);
	DDX_Text(pDX, IDC_EDIT23, m_Y1Offeset);
	DDX_Text(pDX, IDC_EDIT35, m_BoxNum);
	DDX_Text(pDX, IDC_EDIT26, m_Thick);
	DDX_Control(pDX, IDC_LIST2, m_MaskingInfoList);
	DDX_CBIndex(pDX, IDC_COMBO7, ListComboVal);
	DDX_CBIndex(pDX, IDC_COMBO8, m_type);
}


BEGIN_MESSAGE_MAP(Masking, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &Masking::OnBnClickedAddBox)
	ON_BN_CLICKED(IDC_BUTTON2, &Masking::OnBnClickedDeleteBox)
	ON_BN_CLICKED(IDC_BUTTON3, &Masking::OnBnClickedDeleteAll)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &Masking::OnDblclkList2)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &Masking::OnClickList2)
	ON_CBN_CLOSEUP(IDC_COMBO7, &Masking::OnCloseupCombo6)
	ON_CBN_DROPDOWN(IDC_COMBO7, &Masking::OnCbnDropdownCombo7)
END_MESSAGE_MAP()


// Masking 메시지 처리기입니다.


void Masking::OnBnClickedAddBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	MaskInfo tmp;
	tmp.type	  = m_type;
	tmp.X0Offeset = m_X0Offeset;
	tmp.X1Offeset = m_X1Offeset;
	tmp.Y0Offeset = m_Y0Offeset;
	tmp.Y1Offeset = m_Y1Offeset;
	tmp.Thick	  = m_Thick;
	tmp.BoxNum	  = m_BoxNum;

	int index = m_MaskingInfoList.GetSelectionMark();
	if (index == -1)
		MaskingListVal.push_back(tmp);
	else
		MaskingListVal.insert(MaskingListVal.begin() + index, tmp);


	PutData();
}


void Masking::OnBnClickedDeleteBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = m_MaskingInfoList.GetSelectionMark();
	char ProcTime[500];
	sprintf_s(ProcTime, " Choice Number ");
	if (index == -1)
		AfxMessageBox((CString)(ProcTime));
	else {
		MaskingListVal.erase(MaskingListVal.begin() + index);//a.erase(a.begin()+i); 
		PutData();
	}
}


void Masking::OnBnClickedDeleteAll()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	MaskingListVal.clear();
	PutData();
}

BOOL Masking::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_RETURN) {
			if (pMsg->hwnd == GetDlgItem(IDC_EDIT1)->GetSafeHwnd())
			{
				if (iSavedSubitem == 0) {
					char ProcTime[500];
					sprintf_s(ProcTime, "don't touch this, man~");
					AfxMessageBox((CString)(ProcTime));
				}
				else {
					CString str;
					GetDlgItemText(IDC_EDIT1, str);
					m_MaskingInfoList.SetItemText(iSavedItem, iSavedSubitem, str);
					switch (iSavedSubitem - 1) {
					case 0: MaskingListVal[iSavedItem].type = _ttoi(str); break;
					case 1: MaskingListVal[iSavedItem].X0Offeset = _ttoi(str); break;
					case 2: MaskingListVal[iSavedItem].Y0Offeset = _ttoi(str); break;
					case 3: MaskingListVal[iSavedItem].X1Offeset = _ttoi(str); break;
					case 4: MaskingListVal[iSavedItem].Y1Offeset = _ttoi(str); break;
					case 5: MaskingListVal[iSavedItem].Thick = _ttoi(str); break;
					case 6: MaskingListVal[iSavedItem].BoxNum = _ttoi(str); break;
					}
					GetDlgItem(IDC_EDIT1)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
					PutData();
				}
			}
			else if (pMsg->hwnd == GetDlgItem(IDC_COMBO7)->GetSafeHwnd())
			{
				CString str;
				CComboBox* m_CbCombo = (CComboBox*)GetDlgItem(IDC_COMBO7);

				int nIndex = m_CbCombo->GetCurSel();

				MaskingListVal[iSavedItem].type = ListComboVal = nIndex;
				GetDlgItem(IDC_COMBO7)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
				PutData();
			}
			return TRUE;
		}
		if (pMsg->wParam == VK_ESCAPE)
		{
			SetDlgItemText(IDC_EDIT1, _T(""));
			GetDlgItem(IDC_EDIT1)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
			GetDlgItem(IDC_COMBO7)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
			return TRUE;
		}
	}
	//if(pMsg->message == WM_LBUTTONDOWN && pMsg->hwnd == GetDlgItem(IDC_COMBO7)->m_hWnd){
	// // 아무런 처리 없이 그냥 return 한다.
	// CString str;
	// GetDlgItemText(IDC_COMBO7, str);
	//
	// ListComboVal = _ttoi(str);
	// PutData();
	// return TRUE;
	//}
	return CDialog::PreTranslateMessage(pMsg);
}
void Masking::PutData()
{	UpdateData(TRUE);
	m_MaskingInfoList.DeleteAllItems();
	m_MaskingInfoListVal.clear();
	m_MaskingInfoListVal.reserve(MaskingListVal.size());
	MaskInfo buffer;
	for (int i = 0; i<MaskingListVal.size(); i++) {
		buffer.type = MaskingListVal[i].type;
		buffer.X0Offeset = MaskingListVal[i].X0Offeset;
		buffer.X1Offeset = MaskingListVal[i].X1Offeset;
		buffer.Y0Offeset = MaskingListVal[i].Y0Offeset;
		buffer.Y1Offeset = MaskingListVal[i].Y1Offeset;
		buffer.Thick	 = MaskingListVal[i].Thick;
		buffer.BoxNum	 = MaskingListVal[i].BoxNum;
		m_MaskingInfoListVal.push_back(buffer);
	}
	UpdateData(FALSE);

	char szText[50] = "";  //문자열을 저장할 변수 선언
						   //int nIndex=0;  //목록의 인덱스를 저장할 변수선언
	string direction_list[10];
	direction_list[0] = "사용안함";
	direction_list[1] = "사각형";
	direction_list[2] = "업데이트예정";
	direction_list[3] = "업데이트예정";
	UpdateData(TRUE);
	for (int i = 0; i<m_MaskingInfoListVal.size(); i++) {
		LVITEM lItem;  //이 구조체를 이용해서 목록에 대한 정보를 작성

		lItem.mask = LVIF_TEXT;  //이 구조체의 pszText확장
		lItem.iItem = i;  //목록의 번호를 지정
		lItem.iSubItem = 0;  //세부 항목의 번호를 지정-최상목록이므로 0을 줍니다.
		sprintf_s(szText, "%d", i + 1);  //m_strName변수가 CSstrin형이라 szText변수로 바로 값을 전송할 수가 없다. 따라서 sprintf()함수이용
		wchar_t* wStringFrom = new wchar_t[50];
		MultiByteToWideChar(CP_ACP, 0, szText, -1, wStringFrom, 50);
		lItem.pszText = wStringFrom;  //목록내용 지정
		m_MaskingInfoList.InsertItem(&lItem);   //최상목록추가

		for (int j = 0; j<7; j++) {
			lItem.iSubItem = j + 1;  //세부 항목의 번호를 지정-최상목록이므로 0을 줍니다.
									 //sprintf(szText,"%d",m_MaskingInfoListVal[i].info[j]);  //m_strName변수가 CSstrin형이라 szText변수로 바로 값을 전송할 수가 없다. 따라서 sprintf()함수이용
			switch (j) {
			case 0: sprintf_s(szText, "%s", direction_list[m_MaskingInfoListVal[i].type].c_str()); break;
			case 1: sprintf_s(szText, "%d", m_MaskingInfoListVal[i].X0Offeset); break;
			case 2: sprintf_s(szText, "%d", m_MaskingInfoListVal[i].Y0Offeset); break;
			case 3: sprintf_s(szText, "%d", m_MaskingInfoListVal[i].X1Offeset); break;
			case 4: sprintf_s(szText, "%d", m_MaskingInfoListVal[i].Y1Offeset); break;
			case 5: sprintf_s(szText, "%d", m_MaskingInfoListVal[i].Thick); break;
			case 6: sprintf_s(szText, "%d", m_MaskingInfoListVal[i].BoxNum); break;
				//case 6: sprintf_s(szText, "%d", m_MaskingInfoListVal[i].Direction); break;
			}

			MultiByteToWideChar(CP_ACP, 0, szText, -1, wStringFrom, 50);
			lItem.pszText = wStringFrom;  //목록내용 지정
			m_MaskingInfoList.SetItem(&lItem);  //하위목록추가는 SetItem함수를 사용
		}
	}

	//추가할 아이템 넣기


	//nIndex++;   //새로운목록추가하기위해 1증가
	UpdateData(FALSE);
}


void Masking::OnDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	LPNMITEMACTIVATE pNMITEM = (LPNMITEMACTIVATE)pNMHDR;
	iSavedItem = pNMITEM->iItem;
	iSavedSubitem = pNMITEM->iSubItem;
	if (pNMITEM->iItem != -1)
	{
		CRect rect;
		if (pNMITEM->iSubItem == 0)
		{
			m_MaskingInfoList.GetItemRect(pNMITEM->iItem, rect, LVIR_BOUNDS);
			rect.right = rect.left + m_MaskingInfoList.GetColumnWidth(0);
		}
		else
		{
			m_MaskingInfoList.GetSubItemRect(pNMITEM->iItem, pNMITEM->iSubItem, LVIR_BOUNDS, rect);
		}
		m_MaskingInfoList.ClientToScreen(rect);
		this->ScreenToClient(rect);
		GetDlgItem(IDC_EDIT1)->SetWindowText(m_MaskingInfoList.GetItemText(pNMITEM->iItem, pNMITEM->iSubItem));
		GetDlgItem(IDC_EDIT1)->SetWindowPos(NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW);
		GetDlgItem(IDC_EDIT1)->SetFocus();
	}
	*pResult = 0;
}



void Masking::OnClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	LPNMITEMACTIVATE pNMITEM = (LPNMITEMACTIVATE)pNMHDR;
	iSavedItem = pNMITEM->iItem;
	iSavedSubitem = pNMITEM->iSubItem;
	GetDlgItem(IDC_EDIT1)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
	GetDlgItem(IDC_COMBO7)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
	if (pNMITEM->iItem != -1)
	{
		if (iSavedSubitem == 1)
		{
			CRect rect;
			m_MaskingInfoList.GetSubItemRect(pNMITEM->iItem, pNMITEM->iSubItem, LVIR_BOUNDS, rect);
			m_MaskingInfoList.ClientToScreen(rect);
			this->ScreenToClient(rect);
			GetDlgItem(IDC_COMBO7)->SetWindowText(m_MaskingInfoList.GetItemText(pNMITEM->iItem, pNMITEM->iSubItem));
			//int tt,tmp;
			//m_BoxInfoList;
			//tt = m_BoxInfoList.GetScrollPos(tmp);
			//tt;
			CString str;
			//char ProcTime[500];
			//sprintf_s( ProcTime, "fucucucucucuck %d",tmp );
			//AfxMessageBox((CString)(ProcTime));
			//GetDlgItemText(IDC_COMBO7, str);
			str = m_MaskingInfoList.GetItemText(pNMITEM->iItem, pNMITEM->iSubItem);
			ListComboVal = _ttoi(str);
			ListComboVal = MaskingListVal[iSavedItem].type;
			GetDlgItem(IDC_COMBO7)->SetWindowPos(NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW);
			GetDlgItem(IDC_COMBO7)->SetFocus();

		}
		else
		{
			SetDlgItemText(IDC_EDIT1, _T(""));
			GetDlgItem(IDC_COMBO7)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
		}
		UpdateData(FALSE);
	}
	*pResult = 0;
}

void Masking::OnCloseupCombo6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	CComboBox* m_CbCombo = (CComboBox*)GetDlgItem(IDC_COMBO7);

	int nIndex = m_CbCombo->GetCurSel();

	MaskingListVal[iSavedItem].type = ListComboVal = nIndex;
	PutData();

	GetDlgItem(IDC_COMBO7)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
}



void Masking::OnCbnDropdownCombo7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	CComboBox* m_CbCombo = (CComboBox*)GetDlgItem(IDC_COMBO7);
	m_CbCombo->SetCurSel(MaskingListVal[iSavedItem].type);
}
