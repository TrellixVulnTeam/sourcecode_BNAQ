#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CLogin �Ի���

class CLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogin();

// �Ի�������
	enum { IDD = IDD_DLG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CSplitButton	m_split;
	CComboBox		m_addr;
	CComboBox		m_pos;
	CComboBox		m_username;
	CDateTimeCtrl	m_dateDealNew;
	loginInfo		m_loginInfo_Stru; 
	//BOOL m_bLoginSuccess;     //��¼�Ƿ�ɹ��ı�־
	BOOL   m_bWorking;    //���ڽ��е�¼
public:
	void    SetCloseButton(BOOL b);
	afx_msg void OnBnClickedButtonPwdedit();

	void GoToMainApp();		//��¼�ɹ��� �������������
	
	//afx_msg		void OnBnClickedSplitAddrAdd();
	virtual		BOOL OnInitDialog();
	//void		InitSplit();
	afx_msg		void OnBnClickedBtnLogin();
	afx_msg		LRESULT OnLoginFail(WPARAM wParam, LPARAM lParam);
protected:
	afx_msg		LRESULT OnLoginSuccess(WPARAM wParam, LPARAM lParam);
	afx_msg		LRESULT OnCursorToNormal(WPARAM wParam, LPARAM lParam);
	afx_msg		void OnBnClickedBtnGoBack();


	void	WriteToText(CString& strToWtrite,CString& writeToPath);		//��str д��path·�����ļ��� ����ԭ�е�
	BOOL	ReadFromTxt(CString& path,CString& result);
	void	WriteCombToFile(void* comb, CString path);				//д��text�ļ���
	BOOL	LoadComb(void* ptr,CString& path);       //���ı��ļ��м���combox ������
	BOOL	WriteUserToIni();       //���û���������д�������ļ�
	void	EncryptCode(CString& result);     //����
	void	DecryptCode(CString source,CString& result);    //�����뻹ԭ
	void    LoadUser();       //��ʼ���û���������
	void    RestoreCode(CString& midValue,char& strReturn);   //��ÿ����#��֮����ַ�����ԭΪԭ�����һλ�ַ�
public:
	
	CStatic		m_status;
	CButton		m_remPsw;
	CString		m_password;
	afx_msg void OnCbnSelchangeComboLoginUsername();
	afx_msg void OnCbnEditchangeComboLoginUsername();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

//	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
