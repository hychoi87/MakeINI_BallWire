// WireConnect.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "WireConnect.h"
#include "afxdialogex.h"
#include "MakeINI_Defect.h"


// WireConnect ��ȭ �����Դϴ�.

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


// WireConnect �޽��� ó�����Դϴ�.


void WireConnect::OnEnChangeEdit()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	
	char szText[50]="";  //���ڿ��� ������ ���� ����
	//int nIndex=0;  //����� �ε����� ������ ��������

	UpdateData(TRUE);
	for(int i=0; i<m_WireConnectListVal.size(); i++){
		LVITEM lItem;  //�� ����ü�� �̿��ؼ� ��Ͽ� ���� ������ �ۼ�

		lItem.mask=LVIF_TEXT;  //�� ����ü�� pszTextȮ��
		lItem.iItem=i;  //����� ��ȣ�� ����

		lItem.iSubItem=0;  //���� �׸��� ��ȣ�� ����-�ֻ����̹Ƿ� 0�� �ݴϴ�.
		sprintf(szText,"%d",i+1);  //m_strName������ CSstrin���̶� szText������ �ٷ� ���� ������ ���� ����. ���� sprintf()�Լ��̿�
		wchar_t* wStringFrom=new wchar_t[50];
		MultiByteToWideChar(CP_ACP, 0, szText, -1, wStringFrom, 50);
		lItem.pszText=wStringFrom;  //��ϳ��� ����
		m_WireConnectList.InsertItem(&lItem);   //�ֻ����߰�

		for(int j=0; j<4; j++){
			lItem.iSubItem=j+1;  //���� �׸��� ��ȣ�� ����-�ֻ����̹Ƿ� 0�� �ݴϴ�.
			sprintf(szText,"%d",m_WireConnectListVal[i].info[j]);  //m_strName������ CSstrin���̶� szText������ �ٷ� ���� ������ ���� ����. ���� sprintf()�Լ��̿�
			MultiByteToWideChar(CP_ACP, 0, szText, -1, wStringFrom, 50);
			lItem.pszText=wStringFrom;  //��ϳ��� ����
			m_WireConnectList.SetItem(&lItem);  //��������߰��� SetItem�Լ��� ���
		}
	}
	//�߰��� ������ �ֱ�


	//nIndex++;   //���ο����߰��ϱ����� 1����
	UpdateData(FALSE);



//��ó: http://ewst.tistory.com/entry/MFC-ListBox-Column��-����߰� [Memory]


}


void WireConnect::OnBnClickedAddList()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	WireConnectInfo tmp;
	tmp.info[0] = m_BOX1;
	tmp.info[1] = m_Ord1;
	tmp.info[2] = m_BOX2;
	tmp.info[3] = m_Ord2;
	int index = m_WireConnectList.GetSelectionMark(); 
	if(m_BOX1 == 0 || m_Ord1 == 0 || m_BOX2 == 0 || m_Ord2 == 0){
		AfxMessageBox(_T("������ �� ���� ������ �Է��ϼ̽��ϴ�. (0)"));
		


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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	WireConnectListVal.clear();
	PutData();

}



void WireConnect::OnEndlabeleditList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//pDispInfo->item.iItem
	m_WireConnectList.SetFocus();
	m_WireConnectList.EditLabel(pDispInfo->item.iItem);

	int index = m_WireConnectList.GetSelectionMark(); 
	char ProcTime[500];
	sprintf( ProcTime, " Select %d index", index );
	AfxMessageBox((CString)(ProcTime));

	m_WireConnectList.SetItemText(pDispInfo->item.iItem, 0, pDispInfo->item.pszText);
	//��ó: http://disclosure.tistory.com/entry/����Ʈ-��Ʈ��-�����Ͽ�-�����ϱ� [HK Study Room :)]
	*pResult = 0;
}


void WireConnect::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SetDlgItemText(IDC_EDIT1, _T(""));
	GetDlgItem(IDC_EDIT1)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
	*pResult = 0;
}
