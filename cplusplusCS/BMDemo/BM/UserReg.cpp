// UserReg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "UserReg.h"
#include "afxdialogex.h"


// CUserReg �Ի���

IMPLEMENT_DYNAMIC(CUserReg, CDialogEx)

CUserReg::CUserReg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserReg::IDD, pParent)
{

}

CUserReg::~CUserReg()
{
}

void CUserReg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUserReg, CDialogEx)
END_MESSAGE_MAP()


// CUserReg ��Ϣ�������
