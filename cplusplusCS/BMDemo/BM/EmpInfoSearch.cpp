// EmpInfoSearch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "EmpInfoSearch.h"
#include "afxdialogex.h"


// CEmpInfoSearch �Ի���

IMPLEMENT_DYNAMIC(CEmpInfoSearch, CDialogEx)

CEmpInfoSearch::CEmpInfoSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEmpInfoSearch::IDD, pParent)
	, m_keyWord(_T(""))
{

}

CEmpInfoSearch::CEmpInfoSearch(CEmpInfoView* pView,CWnd* pParent)
	: CDialogEx(CEmpInfoSearch::IDD, pParent)
{
	m_pEmpInfoView = pView;
}


CEmpInfoSearch::~CEmpInfoSearch()
{
	m_pEmpInfoView = NULL;
}

void CEmpInfoSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_KEY_WORD, m_keyWord);
}


BEGIN_MESSAGE_MAP(CEmpInfoSearch, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_SEARCH_ALL, &CEmpInfoSearch::OnBnClickedBtnSearchAll)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_SEARCH_BY_KEYWORD, &CEmpInfoSearch::OnBnClickedBtnSearchByKeyword)
	ON_BN_CLICKED(IDC_BTN_GIVEUP, &CEmpInfoSearch::OnBnClickedBtnGiveup)
	ON_BN_CLICKED(IDC_RADIO_NAME, &CEmpInfoSearch::OnBnClickedRadioName)
	ON_BN_CLICKED(IDC_RADIO_NUM, &CEmpInfoSearch::OnBnClickedRadioNum)
	ON_BN_CLICKED(IDC_RADIO_ADDR, &CEmpInfoSearch::OnBnClickedRadioAddr)
	ON_BN_CLICKED(IDC_RADIO_POS, &CEmpInfoSearch::OnBnClickedRadioPos)
END_MESSAGE_MAP()


// CEmpInfoSearch ��Ϣ�������


void CEmpInfoSearch::OnBnClickedBtnSearchAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetClassLong(this->GetSafeHwnd(),GCL_HCURSOR ,(LONG)LoadCursor(NULL , IDC_WAIT));  //ԲȦ ��ʾ�ȴ�
	//m_pEmpInfoView->m_list.DeleteAllItems();

	void* dlg = m_pEmpInfoView;

	CSock::StartSearchAllEmpInfo(dlg);
	CDialogEx::OnOK();
}




HBRUSH CEmpInfoSearch::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)  
	{
		pDC->SetBkMode(TRANSPARENT);  
		//hbr=(HBRUSH)::GetStockObject(NULL_BRUSH);
		HBRUSH b_static=CreateSolidBrush(RGB(185,211,255));	
		return b_static;	
	}
	if(nCtlColor == CTLCOLOR_DLG){
		pDC->SetTextColor(RGB(0,0,0)); 
		pDC->SetBkColor(RGB(185,211,255)); 
		HBRUSH b=CreateSolidBrush(RGB(185,211,255)); 
		return b;
	}
	return hbr;
}

BOOL CEmpInfoSearch::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//GetDlgItem(IDC_RADIO_NAME)->SetCheck(TRUE);
	LoadDefaultChioceFromIni();
	
	return TRUE;
}

void CEmpInfoSearch::OnBnClickedBtnSearchByKeyword()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pEmpInfoView->m_searchByKeyWord.Empty();
	UpdateData(TRUE);
	if(m_keyWord.IsEmpty())   //�������Ϊ�ս�����ȫ��Ա������
	{
		if(IDYES == MessageBox(_T("�����ؼ���Ϊ�գ�������ȫ��Ա����ȷ�����������������������������"),_T("��ʾ"),MB_YESNO))
		{
			void* dlg = m_pEmpInfoView;
			CSock::StartSearchAllEmpInfo(dlg);
			CDialogEx::OnOK();
		}else{
			return;
		}
	}else{
		CString _strFind = _T(",");
		int flag = m_keyWord.Find(_strFind);
		if(-1 != flag)   //��������
		{
			MessageBox(_T("�ؼ��ֲ��ܰ������ţ�"));
			m_keyWord.Empty();
			UpdateData(FALSE);
			return;
		}
		if(1 == ((CButton*)GetDlgItem(IDC_RADIO_NAME))->GetCheck())
		{
			m_pEmpInfoView->m_searchByKeyWord = _T("Ա������,")+ m_keyWord;
		}else if(1 == ((CButton*)GetDlgItem(IDC_RADIO_NUM))->GetCheck())
		{
			m_pEmpInfoView->m_searchByKeyWord = _T("Ա������,")+ m_keyWord;
		}else if(1 == ((CButton*)GetDlgItem(IDC_RADIO_POS))->GetCheck())
		{
			m_pEmpInfoView->m_searchByKeyWord = _T("ְ��,")+ m_keyWord;
		}else if(1 == ((CButton*)GetDlgItem(IDC_RADIO_ADDR))->GetCheck())
		{
			m_pEmpInfoView->m_searchByKeyWord = _T("�����ص�,")+ m_keyWord;
		}
	}
	//WriteDefaultChoiceToIni();
	void* dlg = m_pEmpInfoView;
	CSock::StartSearchEmpByKeyWord(dlg);
	//CSock::StartSearchAllEmpInfo(dlg);
	CDialogEx::OnOK();
}


void CEmpInfoSearch::OnBnClickedBtnGiveup()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}

void CEmpInfoSearch::WriteDefaultChoiceToIni()
{
	CString toFind = _T(",");
	int index = m_pEmpInfoView->m_searchByKeyWord.Find(toFind);
	CString temp = m_pEmpInfoView->m_searchByKeyWord.Mid(0,index);
	WritePrivateProfileString(_T("Ա������"),_T("Ĭ������"),temp,_T(".//BMClient.ini")); 
}

void CEmpInfoSearch::LoadDefaultChioceFromIni()
{
	CString chioce = NULL;
	CFileFind finder;
	BOOL isFind = finder.FindFile(_T(".//BMClient.ini"));
	if(isFind)
	{
		GetPrivateProfileString(_T("Ա������"),_T("Ĭ������"),_T("-1"),chioce.GetBuffer(10),10,_T(".//BMClient.ini")); 
		if(_T("-1") == chioce)
		{
			CheckDlgButton(IDC_RADIO_NAME,1);
			WritePrivateProfileString(_T("Ա������"),_T("Ĭ������"),_T("Ա������"),_T(".//BMClient.ini")); 
		}else{
			if(_T("Ա������") == chioce)
			{
				CheckDlgButton(IDC_RADIO_NAME,1);
			}else if(_T("Ա������") == chioce){
				CheckDlgButton(IDC_RADIO_NUM,1);
			}else if(_T("ְ��") == chioce){
				CheckDlgButton(IDC_RADIO_POS,1);
			}else{
				CheckDlgButton(IDC_RADIO_ADDR,1);
			}
		}
	}else{   //�����ڸ��ļ�  ����Ĭ������
		CheckDlgButton(IDC_RADIO_NAME,1);
		WritePrivateProfileString(_T("Ա������"),_T("Ĭ������"),_T("Ա������"),_T(".//BMClient.ini")); 
	}
}

void CEmpInfoSearch::OnBnClickedRadioName()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString temp = _T("Ա������");
	WritePrivateProfileString(_T("Ա������"),_T("Ĭ������"),temp,_T(".//BMClient.ini")); 
}


void CEmpInfoSearch::OnBnClickedRadioNum()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString temp = _T("Ա������");
	WritePrivateProfileString(_T("Ա������"),_T("Ĭ������"),temp,_T(".//BMClient.ini")); 
}


void CEmpInfoSearch::OnBnClickedRadioAddr()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString temp = _T("�����ص�");
	WritePrivateProfileString(_T("Ա������"),_T("Ĭ������"),temp,_T(".//BMClient.ini")); 
}


void CEmpInfoSearch::OnBnClickedRadioPos()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString temp = _T("ְ��");
	WritePrivateProfileString(_T("Ա������"),_T("Ĭ������"),temp,_T(".//BMClient.ini")); 
}
