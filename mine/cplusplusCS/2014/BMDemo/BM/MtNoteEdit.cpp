// MtNoteEdit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "MtNoteEdit.h"
#include "afxdialogex.h"


// CMtNoteEdit �Ի���

IMPLEMENT_DYNAMIC(CMtNoteEdit, CDialogEx)

CMtNoteEdit::CMtNoteEdit(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMtNoteEdit::IDD, pParent)
	, m_nodeOrgName(_T(""))
	, m_nodeNameNew(_T(""))
{

}

CMtNoteEdit::CMtNoteEdit(CMtSetProp* pMtSetProp,CWnd* pParent )
	: CDialogEx(CMtNoteEdit::IDD, pParent)
{
	m_pMtSetProp = pMtSetProp;
}

CMtNoteEdit::~CMtNoteEdit()
{
	m_pMtSetProp = NULL;
}

void CMtNoteEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NODE_ORG, m_nodeOrgName);
	DDX_Text(pDX, IDC_EDIT_NOTE_NAME_NEW, m_nodeNameNew);
}


BEGIN_MESSAGE_MAP(CMtNoteEdit, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_NOTE_SAVE, &CMtNoteEdit::OnBnClickedBtnNoteSave)
	ON_BN_CLICKED(IDC_BTN_QUIT, &CMtNoteEdit::OnBnClickedBtnQuit)
END_MESSAGE_MAP()


// CMtNoteEdit ��Ϣ�������


HBRUSH CMtNoteEdit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CMtNoteEdit::OnBnClickedBtnNoteSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_nodeNameNew.IsEmpty())
	{
		MessageBox(_T("�ڵ������Ʋ���Ϊ�գ�"));
		return;
	}
	if(m_nodeNameNew == m_nodeOrgName)
	{
		MessageBox(_T("�ڵ������Ʋ��ܺ�ԭ�ڵ�������ͬ��"));
		return;
	}
	if(!((-1 == m_nodeNameNew.Find(_T("\\")))
		&&(-1 == m_nodeNameNew.Find(_T("|")))
		&&(-1 == m_nodeNameNew.Find(_T("<")))
		&&(-1 == m_nodeNameNew.Find(_T(">")))
		))
	{
		MessageBox(_T("�ڵ������Ʋ��ܰ���'\\','|','<','>'�������ַ���"));
		return;
	}
	
	if(m_nodeNameNew.GetLength()>25)
	{
		MessageBox(_T("�ڵ������Ʋ��ܴ���25���ַ���"));
		return;
	}
	m_pMtSetProp->m_nodeNameNew_Edit = m_nodeNameNew;
	m_pMtSetProp->m_nodeNameOrg_Edit = m_nodeOrgName;
	m_pMtSetProp->SendMessage(WM_REQNODEEDIT_MtSetProp,0,0);
	CDialogEx::OnOK();
}


void CMtNoteEdit::OnBnClickedBtnQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
