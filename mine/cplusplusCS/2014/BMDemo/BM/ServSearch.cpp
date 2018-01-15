// ServSearch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "ServSearch.h"
#include "afxdialogex.h"
#include "ServiceSearch.h"

// CServSearch �Ի���

IMPLEMENT_DYNAMIC(CServSearch, CDialogEx)

CServSearch::CServSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServSearch::IDD, pParent)
	, m_keyword(_T(""))
{

}

CServSearch::CServSearch(CServiceSearch* pServiceSearch,CWnd* pParent)
	: CDialogEx(CServSearch::IDD, pParent)
{
	m_pServiceSearch = pServiceSearch;
}
 

CServSearch::~CServSearch()
{
	m_pServiceSearch = NULL;
}

void CServSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_KEYWORD, m_keyword);
}


BEGIN_MESSAGE_MAP(CServSearch, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_FINDALL, &CServSearch::OnBnClickedBtnFindall)
	ON_BN_CLICKED(IDC_BTN_SEARCH, &CServSearch::OnBnClickedBtnSearch)
	ON_BN_CLICKED(IDC_RADIO_SERV_DATE, &CServSearch::OnBnClickedRadioServDate)
	ON_BN_CLICKED(IDC_RADIO_CTM_NAME, &CServSearch::OnBnClickedRadioCtmName)
END_MESSAGE_MAP()


// CServSearch ��Ϣ�������
BOOL CServSearch::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	LoadDefaultChioceFromIni();

	return TRUE;
}

HBRUSH CServSearch::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CServSearch::OnBnClickedBtnFindall()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pServiceSearch->FindAllServ();
	CDialogEx::OnOK();
}


void CServSearch::OnBnClickedBtnSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pServiceSearch->m_searchByKeyWord.Empty();
	m_pServiceSearch->m_searchByKeyWord = _T("��������,");
	UpdateData(TRUE);
	if(m_keyword.IsEmpty())   //�������Ϊ�ս�����ȫ��Ա������
	{
		if(IDYES == MessageBox(_T("�����ؼ���Ϊ�գ�������ȫ������ȷ�������"),_T("��ʾ"),MB_YESNO))
		{
			m_pServiceSearch->FindAllServ();
			CDialogEx::OnOK();
		}else{
			return;
		}
	}else{
		CString _strFind = _T(",");
		int flag = m_keyword.Find(_strFind);
		if(-1 != flag)   //��������
		{
			MessageBox(_T("�ؼ��ֲ��ܰ������ţ�"));
			m_keyword.Empty();
			UpdateData(FALSE);
			return;
		}
		if(m_keyword.GetLength()>30)
		{
			MessageBox(_T("�ؼ��ֲ��ܳ���30���ַ�"));
			return;
		}
		if(1 == ((CButton*)GetDlgItem(IDC_RADIO_SERV_DATE))->GetCheck())
		{
			m_pServiceSearch->m_searchByKeyWord += _T("��������,")+ m_keyword;
		}else
		{
			m_pServiceSearch->m_searchByKeyWord += _T("�ͻ�����,")+ m_keyword;
		}
	}
	void* dlg = m_pServiceSearch;
	CSock::StartFindServByKeyWord(dlg);
	CDialogEx::OnOK();
}

void CServSearch::LoadDefaultChioceFromIni()
{
	CString chioce = NULL;
	CFileFind finder;
	BOOL isFind = finder.FindFile(_T(".//BMClient.ini"));
	if(isFind)
	{
		GetPrivateProfileString(_T("��������"),_T("Ĭ������"),_T("-1"),chioce.GetBuffer(10),10,_T(".//BMClient.ini")); 
		if(_T("-1") == chioce)
		{
			CheckDlgButton(IDC_RADIO_SERV_DATE,1);
		}else{
			if(_T("��������") == chioce)
			{
				CheckDlgButton(IDC_RADIO_SERV_DATE,1);
			}else{
				CheckDlgButton(IDC_RADIO_CTM_NAME,1);
			}
		}
	}else{   //�����ڸ��ļ�  ����Ĭ������
		CheckDlgButton(IDC_RADIO_SERV_DATE,1);
	}
}


void CServSearch::OnBnClickedRadioServDate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString temp = _T("��������");
	WritePrivateProfileString(_T("��������"),_T("Ĭ������"),temp,_T(".//BMClient.ini")); 
}


void CServSearch::OnBnClickedRadioCtmName()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString temp = _T("�ͻ�����");
	WritePrivateProfileString(_T("��������"),_T("Ĭ������"),temp,_T(".//BMClient.ini")); 
}
