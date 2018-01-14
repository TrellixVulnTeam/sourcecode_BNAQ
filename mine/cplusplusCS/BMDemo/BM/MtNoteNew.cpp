// MtNoteNew.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "MtNoteNew.h"
#include "afxdialogex.h"
#include "MtSetProp.h"

// CMtNoteNew �Ի���

IMPLEMENT_DYNAMIC(CMtNoteNew, CDialogEx)

CMtNoteNew::CMtNoteNew(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMtNoteNew::IDD, pParent)
	, m_parentNode(_T(""))
	, m_nodeNew(_T(""))
{

}

CMtNoteNew::CMtNoteNew(CMtSetProp* pMtSetProp,CWnd* pParent /*=NULL*/)
	: CDialogEx(CMtNoteNew::IDD, pParent)
{
	m_pMtSetProp = pMtSetProp;
}

CMtNoteNew::~CMtNoteNew()
{
	m_pMtSetProp = NULL;
}

void CMtNoteNew::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PARENT_NODE, m_parentNode);
	DDX_Text(pDX, IDC_EDIT_NODE_NEW, m_nodeNew);
}


BEGIN_MESSAGE_MAP(CMtNoteNew, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_NOTE_NEW, &CMtNoteNew::OnBnClickedBtnNoteNew)
	//ON_EN_CHANGE(IDC_EDIT1, &CMtNoteNew::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BTN_QUIT, &CMtNoteNew::OnBnClickedBtnQuit)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMtNoteNew ��Ϣ�������


void CMtNoteNew::OnBnClickedBtnNoteNew()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_parentNode.IsEmpty())
	{
		MessageBox(_T("�ϼ��ڵ㲻��Ϊ�գ�"));
		return;
	}
	if(m_nodeNew.IsEmpty())
	{
		MessageBox(_T("�½��ڵ㲻��Ϊ�գ�"));
		return;
	}
	if(m_nodeNew == m_parentNode)
	{
		MessageBox(_T("�½��ڵ㲻�ܺ��ϼ��ڵ�������ͬ��"));
		return;
	}
	if(!((-1 == m_parentNode.Find(_T("\\")))
		&&(-1 == m_parentNode.Find(_T("|")))
		&&(-1 == m_parentNode.Find(_T("<")))
		&&(-1 == m_parentNode.Find(_T(">")))
		))
	{
		MessageBox(_T("�ϼ��ڵ㲻�ܰ���'\\','|','<','>'�������ַ���"));
		return;
	}
	if(!((-1 == m_nodeNew.Find(_T("\\")))
		&&(-1 == m_nodeNew.Find(_T("|")))
		&&(-1 == m_nodeNew.Find(_T("<")))
		&&(-1 == m_nodeNew.Find(_T(">")))
		))
	{
		MessageBox(_T("�½��ڵ㲻�ܰ���'\\','|','<','>'�������ַ���"));
		return;
	}
	if(m_parentNode.GetLength()>25 ||m_nodeNew.GetLength()>25)
	{
		MessageBox(_T("�ڵ����Ʋ��ܴ���25���ַ���"));
		return;
	}
	m_pMtSetProp->m_parentNodeName = m_parentNode;
	m_pMtSetProp->m_nodeNameNew = m_nodeNew;
	//void* dlg = m_pMtSetProp;
	m_pMtSetProp->SendMessage(WM_REQNOTENEW_MtSetProp,0,0);
	CDialogEx::OnOK();
}





void CMtNoteNew::OnBnClickedBtnQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


HBRUSH CMtNoteNew::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
