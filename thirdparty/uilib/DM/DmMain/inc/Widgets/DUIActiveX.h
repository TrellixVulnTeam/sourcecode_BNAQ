//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: 
// File Des: 
// File Summary:��ActiveX�£����ڲ�ͣ��ˢ�±���������ӿؼ��п�����ʾ�����ؼ���һ������ʹ��cache����
// ��Ȼ����ˢ��ʱ���ӿؼ��п��ܲ�����£�����ʹ���ϱ���
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-3-5	1.0			
//--------------------------------------------------------
#pragma once
#include "DMActiveXBase.h"

namespace DM
{
	class DM_EXPORT DUIActiveX : public DUIWindow
	{
		DMDECLARE_CLASS_NAME(DUIActiveX, DUINAME_ActiveX,DMREG_Window)
	public:
		explicit DUIActiveX();
		virtual ~DUIActiveX();

	public:
		DM_BEGIN_MSG_MAP()
			DM_MSG_WM_PAINT(DM_OnPaint)
			MESSAGE_RANGE_HANDLER_EX(WM_MOUSEFIRST,WM_MOUSELAST,OnMouseEvent)
			MESSAGE_RANGE_HANDLER_EX(WM_KEYFIRST,WM_KEYLAST,OnKeyEvent)
			MSG_WM_SIZE(OnSize)
			MSG_WM_SHOWWINDOW(OnShowWindow)
		DM_END_MSG_MAP()

	public:
		void OnSize(UINT nType, CSize size);
		void DM_OnPaint(IDMCanvas* pCanvas);
		void OnShowWindow(BOOL bShow, UINT nStatus);
		LRESULT OnMouseEvent(UINT uMsg,WPARAM wp,LPARAM lp);
		LRESULT OnKeyEvent(UINT uMsg,WPARAM wp,LPARAM lp);

	public:
		IUnknown * GetIUnknow();
		UINT DV_OnGetDlgCode(){return DMDLGC_WANTALLKEYS;}

	public:
		DMCode OnAttrClsid(LPCWSTR pszValue, bool bLoadXml);

	public:
		DM_BEGIN_ATTRIBUTES()
			DM_CUSTOM_ATTRIBUTE(L"clsid",OnAttrClsid)
			DM_DWORD_ATTRIBUTE(L"clsctx",m_clsCtx,DM_ECODE_OK)
			DM_bool_ATTRIBUTE(L"delay",m_bDelayInit,DM_ECODE_OK)
		DM_END_ATTRIBUTES()

	public:// ����
		BOOL InitActiveX();
		void SetActiveXVisible(BOOL bVisible);						///< For windowless objects, this method invalid

	protected:
		DMAxContainerImpl			*m_axContainer;
		CLSID						 m_clsid;
		DWORD						 m_clsCtx;
		bool						 m_bDelayInit;  // ������ʾʱ�ż���
		bool                         m_bInit;
	};
}// namespace DM
