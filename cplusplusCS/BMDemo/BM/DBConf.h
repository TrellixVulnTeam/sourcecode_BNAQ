#ifndef DBCONF_H_H_H_H
#define DBCONF_H_H_H_H

#pragma once
#include "afxwin.h"


// CDBConf �Ի���

class CDBConf : public CDialogEx
{
	DECLARE_DYNAMIC(CDBConf)

public:
	CDBConf(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDBConf();

// �Ի�������
	enum { IDD = IDD_DLG_DBCONF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDbnew();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnLoginContinue();
	virtual BOOL OnInitDialog();
	void WriteToText(CString& strToWtrite,CString& writeToPath);		//��str д��path·�����ļ��� ����ԭ�е�
	BOOL ReadFromTxt(CString& path,CString& result);
	void WriteCombToFile(void* comb, CString path);				//���˿�д��MyPort.text�ļ���
	BOOL LoadComb(void* ptr,CString& path);       //���ı��ļ��м���combox ������
public:
	
	CComboBox m_DBName;
	CComboBox m_ip;
	CComboBox m_port;
	//int m_portDefault;        /////��û���ļ�����ʱ�ͼ���һ��Ĭ�ϵĶ˿�
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


#endif