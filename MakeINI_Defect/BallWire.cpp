// BallWire.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BallWire.h"
#include "afxdialogex.h"
#include "MakeINI_Defect.h"

// CBallWire ��ȭ �����Դϴ�.

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


// CBallWire �޽��� ó�����Դϴ�.


void CBallWire::OnEnChangeEdit()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	char szText[50]="";  //���ڿ��� ������ ���� ����
	//int nIndex=0;  //����� �ε����� ������ ��������
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
		LVITEM lItem;  //�� ����ü�� �̿��ؼ� ��Ͽ� ���� ������ �ۼ�

		lItem.mask=LVIF_TEXT;  //�� ����ü�� pszTextȮ��
		lItem.iItem=i;  //����� ��ȣ�� ����
		lItem.iSubItem=0;  //���� �׸��� ��ȣ�� ����-�ֻ����̹Ƿ� 0�� �ݴϴ�.
		sprintf_s(szText,"%d",i+1);  //m_strName������ CSstrin���̶� szText������ �ٷ� ���� ������ ���� ����. ���� sprintf()�Լ��̿�
		wchar_t* wStringFrom=new wchar_t[50];
		MultiByteToWideChar(CP_ACP, 0, szText, -1, wStringFrom, 50);
		lItem.pszText=wStringFrom;  //��ϳ��� ����
		m_BoxInfoList.InsertItem(&lItem);   //�ֻ����߰�

		for(int j=0; j<7; j++){
			lItem.iSubItem=j+1;  //���� �׸��� ��ȣ�� ����-�ֻ����̹Ƿ� 0�� �ݴϴ�.
			//sprintf(szText,"%d",m_BoxInfoListVal[i].info[j]);  //m_strName������ CSstrin���̶� szText������ �ٷ� ���� ������ ���� ����. ���� sprintf()�Լ��̿�
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
			lItem.pszText=wStringFrom;  //��ϳ��� ����
			m_BoxInfoList.SetItem(&lItem);  //��������߰��� SetItem�Լ��� ���
		}
	}

	//�߰��� ������ �ֱ�


	//nIndex++;   //���ο����߰��ϱ����� 1����
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
	// // �ƹ��� ó�� ���� �׳� return �Ѵ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BoxInfoListVal.clear();
	PutData();
}


void CBallWire::OnDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString str;
	CComboBox* m_CbCombo = (CComboBox*)GetDlgItem(IDC_COMBO6);

	int nIndex = m_CbCombo->GetCurSel();

	BoxInfoListVal[iSavedItem].Direction = ListComboVal = nIndex;
	PutData();
	GetDlgItem(IDC_COMBO6)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
}


void CBallWire::OnCbnSetfocusCombo6()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CBallWire::OnCbnDropdownCombo6()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString str;
	CComboBox* m_CbCombo = (CComboBox*)GetDlgItem(IDC_COMBO6);
	m_CbCombo->SetCurSel(BoxInfoListVal[iSavedItem].Direction);
	;
}
