// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://go.microsoft.com/fwlink/?LinkId=238214��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// BM.h : BM Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CBMApp:
// �йش����ʵ�֣������ BM.cpp
//
#include "Sock.h"

class CBMApp : public CWinAppEx
{
public:
	CBMApp();


// ��д
public:
	virtual BOOL LoginInitInstance();   //�ڵ�¼�ɹ�֮���ʼ������� ����ʾ������
	virtual BOOL InitInstance();		//Ĭ�ϳ�ʼ������
	virtual int ExitInstance();			

// ʵ��
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
public:
	static HMODULE hMod ;         //������Ҫ��ʹ����rich edit2.0 control�ؼ� ��Ҫ��ʼ��
	//CSock   m_sockOnly;             
	SOCKET	m_sHost;		  //ȫ��Ψһһ��ʵ������sock����
public:
	void        InitSocket();       //��ʼ���׽���
	
};

extern CBMApp theApp;
