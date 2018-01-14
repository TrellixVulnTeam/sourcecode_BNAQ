//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: MainWnd.h 
// File Des: ������
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-2-2	1.0		
//-------------------------------------------------------
#pragma once
#include "SkinWnd.h"

class CMainWnd:public DMHWnd
{
public:
	CMainWnd();
	~CMainWnd();
	//---------------------------------------------------
	// Function Des: ��Ϣ�ַ�ϵ�к���
	//---------------------------------------------------
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
	void OnSize(UINT nType, CSize size);
	//---------------------------------------------------
	// Function Des: �¼��ַ�ϵ�к���
	// Input Parameter:
	// Output Parameter:
	// return:
	//---------------------------------------------------
	DMCode OnClose();
	DMCode OnMaximize();
	DMCode OnRestore();
	DMCode OnMinimize();
	DMCode OnSkin();
	DMCode OnSpyInitEvent(DMEventArgs *pEvt);
	DMCode OnTreeSelChanged(DMEventArgs *pEvt);

public:// ����
	void InitTreeCtrl(HWND hRootWnd);
	void InsertTreeItem(DMXmlNode &XmlNode,HDMTREEITEM hParentItem);
	void ReflashEditInfo();
	bool HitTest(RECT &rc);

protected:
	DECLARE_MESSAGE_MAP()// ��MFC��Ϣӳ���
	DECLARE_EVENT_MAP()
public:
	DM_BEGIN_MSG_MAP()
	DM_END_MSG_MAP()
	void OnDUITimer(char id);;

public:
	DMSmartPtrT<CSkinWnd>	m_pSkinWnd;
	DUITreeCtrl*            m_pTreeCtrl;
	DUIRichEdit*            m_pTreeEdit;
	DUIStatic*              m_pSearchSta;
	PDMSpyEnum              m_pSpyEnum;
	HWND                    m_hRootWnd;
	bool                    m_bInit;

	// ����
	bool                    m_bHittest;
	bool                    m_bDraw;
	CRect                   m_rcDraw;

};