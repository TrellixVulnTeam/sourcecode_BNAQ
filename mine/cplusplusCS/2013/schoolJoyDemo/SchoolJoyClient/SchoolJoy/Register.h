#pragma once
//#include "ADOConn.h"

// CRegister �Ի���

class CRegister : public CDialogEx
{
	DECLARE_DYNAMIC(CRegister)

public:
	CRegister(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRegister();

// �Ի�������
	enum { IDD = IDD_DIALOG_Register };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonConfirmregister();
	//void UserInfoTransfer(CString &username,CString &password);
//	CString m_edit_ConfirmPassword;
//	CString m_edit_Password;
	CString m_edit_RUsername;//Add by wqdnan �û���Edit�Ի�������
	CString m_edit_RConfirmPassword;//Add by wqdnan ȷ������Edit�Ի�������
	CString m_edit_RPassword;//Add by wqdnan ����Edit�Ի�������
	static CString username;
	static CString password;
};
