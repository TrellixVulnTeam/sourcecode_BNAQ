#pragma once


// CUserReg �Ի���

class CUserReg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserReg)

public:
	CUserReg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserReg();

// �Ի�������
	enum { IDD = IDD_DIALOG_REGISTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
