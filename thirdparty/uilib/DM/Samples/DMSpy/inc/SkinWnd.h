//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: SkinWnd.h 
// File Des:  �����Ӵ��ڲ���
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-2-2	1.0		
//-------------------------------------------------------
#pragma once

class CSkinWnd:public DMHWnd
{
public:
	CSkinWnd();
	~CSkinWnd();

	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
	//---------------------------------------------------
	// Function Des: �¼��ַ�ϵ�к���
	// Input Parameter:
	// Output Parameter:
	// return:
	//---------------------------------------------------
	DMCode OnClose();

	DMCode OnChangeSkin1();
	DMCode OnChangeSkin2();
	DMCode OnChangeSkin3();


protected:
	DECLARE_MESSAGE_MAP()// ��MFC��Ϣӳ���
	DECLARE_EVENT_MAP()

public:
	wchar_t					m_szCurThemes[100];

};
