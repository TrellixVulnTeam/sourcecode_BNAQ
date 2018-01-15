// MtAndFctSheet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "MtAndFctSheet.h"


// CMtAndFctSheet

IMPLEMENT_DYNAMIC(CMtAndFctSheet, CPropertySheet)

CMtAndFctSheet::CMtAndFctSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

CMtAndFctSheet::CMtAndFctSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_mtSet);
	AddPage(&m_fctSet);
	//m_test = _T("����");
}

CMtAndFctSheet::~CMtAndFctSheet()
{
}
BOOL CMtAndFctSheet::OnInitDialog()
{
	CPropertySheet::OnInitDialog();
	(CWnd *) GetDlgItem( IDOK )->ShowWindow( FALSE );
	(CWnd *) GetDlgItem( IDCANCEL )->ShowWindow( FALSE );
	(CWnd *) GetDlgItem( ID_APPLY_NOW )->ShowWindow( FALSE );
	//SetCloseBtnEable(FALSE);
	return TRUE;
}

BEGIN_MESSAGE_MAP(CMtAndFctSheet, CPropertySheet)
	//ON_WM_DESTROY()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMtAndFctSheet ��Ϣ�������





void CMtAndFctSheet::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CPropertySheet::OnClose();
}
void CMtAndFctSheet::SetCloseBtnEable(BOOL bEnable)  //TRUE �رհ�ť���� FALSE �رհ�ť������
{
	CMenu *pSysMenu = (CMenu *)GetSystemMenu(FALSE);
    ASSERT(pSysMenu != NULL);
	if(bEnable){
		pSysMenu->EnableMenuItem(SC_CLOSE,MF_ENABLED);
	}else{
		pSysMenu->EnableMenuItem(SC_CLOSE,MF_DISABLED);
	}
}
