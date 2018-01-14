//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DUIListBoxEx.h 
// File Des: ListBox
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-2-26	1.0			
//-------------------------------------------------------
#pragma once
#include "DUIScrollBase.h"
#include "DUIItemPanel.h"

namespace DMAttr
{
	/// <summary>
	///		<see cref="DM::DUIListBoxEx"/>��xml���Զ���
	/// </summary>
	class DUIListBoxExAttr:public DUIScrollBaseAttr
	{
	public:
		static wchar_t* INT_itemheight;                                           ///< ���Ĭ�ϸ߶�,��ֵ��֧�ֶ�̬�仯,ʾ��:itemheight="10"
		static wchar_t* INT_cursel;                                               ///< ��ǰѡ��,ʾ��:cursel="1"
		static wchar_t* COLOR_clritembg;                                          ///< item��ı���ɫ,ʾ��:clritembg="pbgra(ff,ff,ff,ff)"
		static wchar_t* COLOR_clritemselbg;                                       ///< item���ѡ�б���ɫ,ʾ��:clritemselbg="pbgra(ff,ff,ff,ff)"
		static wchar_t* bool_bnodrawbg;                                           ///< ΪQQdemo���ã���ץȡ��������Ȼ����͸��

		static wchar_t* NODE_item;                                                ///< ���� 
		static wchar_t* ITEM_height;                                              ///< ��ĸ߶�(��ѡ),ʾ��:height="10"
		static wchar_t* ITEM_data;                                                ///< �������,ʾ��:data="10"
	};
	DMAttrValueInit(DUIListBoxExAttr,INT_itemheight)DMAttrValueInit(DUIListBoxExAttr,INT_cursel)DMAttrValueInit(DUIListBoxExAttr,COLOR_clritembg)
	DMAttrValueInit(DUIListBoxExAttr,COLOR_clritemselbg)DMAttrValueInit(DUIListBoxExAttr,bool_bnodrawbg)
	DMAttrValueInit(DUIListBoxExAttr,NODE_item)DMAttrValueInit(DUIListBoxExAttr,ITEM_height)
	DMAttrValueInit(DUIListBoxExAttr,ITEM_data)
}

namespace DM
{
	typedef struct stLBITEMEX
	{
		stLBITEMEX(DMXmlNode XmlNode, IDMItemPanelOwner* pItemOwner)
		{
			pPanel.Attach(new DUIItemPanel(XmlNode,pItemOwner));
			lParam   = NULL;
			nHeight  = 0;
		}
		~stLBITEMEX()
		{
			pPanel.Release();
		}
		DMSmartPtrT<DUIItemPanel>       pPanel;     ///< ���
		int								nHeight;	///< �߶�
		LPARAM							lParam;     ///< data
	}LBITEMEX,*LPLBITEMEX;

	/// <summary>
	///		 DUIListBoxEx������ʵ��
	/// </summary>
	class DM_EXPORT DUIListBoxEx:public DUIScrollBase
		,public IDMItemPanelOwner
		,public DMArrayT<LPLBITEMEX>
	{
		DMDECLARE_CLASS_NAME(DUIListBoxEx, DUINAME_ListBoxEx,DMREG_Window)
	public:
		DUIListBoxEx();
		~DUIListBoxEx();

	public:
		//---------------------------------------------------
		// Function Des: �ӿ�
		//---------------------------------------------------
		int InsertItem(int nIndex, DMXmlNode&XmlNode);
		int GetItemHeight(int nIndex) const;
		int GetAllItemHeight();
		int SetAllItemHeight(int cyItemHeight, bool bUpdate = true);
		int SetItemHeight(int nIndex, int cyItemHeight, bool bUpdate = true);
		int GetTopIndex() const;
		int SetTopIndex(int nIndex);
		CRect GetItemRect(int iItem);
		bool SetCurSel(int nIndex);
		int GetCurSel() const;
		void DeleteItem(int iItem);
		void DeleteAllItems(bool bUpdate = true);
		void EnsureVisible(int nIndex);
		LPARAM GetItemData(int nIndex);
		bool SetItemData(int nIndex, LPARAM lParam);


	public:// ���ƣ�������
		virtual void DrawItem(IDMCanvas* pCanvas, CRect& rc, int iItem);
		void RedrawItem(int iItem);

	public:
		DM_BEGIN_MSG_MAP()
			DM_MSG_WM_PAINT(DM_OnPaint)
			DM_MSG_WM_SETFOCUS(DM_OnSetFocus)
			DM_MSG_WM_KILLFOCUS(DM_OnKillFocus)

			MSG_WM_DESTROY(OnDestroy)
			MSG_WM_CHAR(OnChar)
			MSG_WM_SIZE(OnSize)
			MSG_WM_NCCALCSIZE(OnNcCalcSize)
			MSG_WM_MOUSELEAVE(OnMouseLeave)
			MSG_WM_MOUSEWHEEL(OnMouseWheel)
			MSG_WM_KEYDOWN(OnKeyDown)
			MESSAGE_RANGE_HANDLER_EX(WM_MOUSEFIRST,WM_MOUSELAST,OnMouseEvent)
			MESSAGE_RANGE_HANDLER_EX(WM_KEYFIRST,WM_KEYLAST,OnKeyEvent)
			MESSAGE_RANGE_HANDLER_EX(WM_IME_STARTCOMPOSITION,WM_IME_KEYLAST,OnKeyEvent)
			MESSAGE_HANDLER_EX(WM_IME_CHAR,OnKeyEvent)
		DM_END_MSG_MAP()

	public:
		//---------------------------------------------------
		// Function Des: DUI����Ϣ�ַ�ϵ�к���
		//---------------------------------------------------
		void OnDestroy();																	///< �����ڴ˴��ͷ�panel����Ȼpanel�޷��ͷţ���
		void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
		void OnSize(UINT nType,CSize size);
		void DM_OnPaint(IDMCanvas* pCanvas);
		void DM_OnSetFocus();
		void DM_OnKillFocus();
		void OnMouseLeave();
		BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
		void OnKeyDown(TCHAR nChar, UINT nRepCnt, UINT nFlags);
		LRESULT OnNcCalcSize(BOOL bCalcValidRects, LPARAM lParam);
		LRESULT OnMouseEvent(UINT uMsg,WPARAM wParam,LPARAM lParam);
		LRESULT OnKeyEvent(UINT uMsg,WPARAM wParam,LPARAM lParam);

	public:
		//---------------------------------------------------
		// Function Des: IDMItemPanelOwnerʵ��
		//---------------------------------------------------   
		DUIWindow* GetOwnerWindow();   
		DMCode OnSetCapture(DUIItemPanel* pPanel);
		DMCode OnReleaseCapture(DUIItemPanel* pPanel);
		DMCode OnGetPanelRect(DUIItemPanel* pPanel,LPRECT lpRect);							///< ��ʹ��*lpRect��ֵ��

	public:
		//---------------------------------------------------
		// Function Des: �����غ���
		//---------------------------------------------------
		DMCode DV_CreateChildWnds(DMXmlNode &XmlNode);
		DMCode DV_OnUpdateToolTip(CPoint pt, DMToolTipInfo &tipInfo);
		DMCode DV_OnSetCursor(const CPoint &pt);
		UINT DV_OnGetDlgCode(){return DMDLGC_WANTALLKEYS;};
		void OnRangeCurPosChanged(CPoint ptOld,CPoint ptNew);							  ///<  ���¹��λ��

	public:
		void PreArrayObjRemove(const LPLBITEMEX &obj);
		DMCode OnAttributeFinished(LPCWSTR pszAttribute,LPCWSTR pszValue,bool bLoadXml,DMCode iErr);

	public:// ����
		void UpdateItemPanelId(int iFirst=0, int iLast = -1);							  ///< ��������
		void UpdateAllPanelLayout();                                                      ///< ����Panel����
		void ModifyPanelBgClr(DUIItemPanel* pPanel,DMColor &Clr);                         ///< �ı�Panel�ı���ɫ
		int HitTest(CPoint &pt);														  ///< �Զ��޸�pt��λ��Ϊ��Ե�ǰ���ƫ����
		void UpdateScrollRangeSize();

	public:
		DM_BEGIN_ATTRIBUTES()
			DM_INT_ATTRIBUTE(DMAttr::DUIListBoxExAttr::INT_itemheight, m_iDefItemHei, DM_ECODE_OK)
			DM_COLOR_ATTRIBUTE(DMAttr::DUIListBoxExAttr::COLOR_clritembg,m_crItemBg, DM_ECODE_NOXMLLOADREFRESH)
			DM_COLOR_ATTRIBUTE(DMAttr::DUIListBoxExAttr::COLOR_clritemselbg,m_crItemSelBg,DM_ECODE_NOXMLLOADREFRESH)
			DM_bool_ATTRIBUTE(DMAttr::DUIListBoxExAttr::bool_bnodrawbg,m_bNoDrawBg, DM_ECODE_NOXMLLOADREFRESH)
			DM_CUSTOM_ATTRIBUTE(DMAttr::DUIListBoxExAttr::INT_cursel,OnAttributeCurSel)
		DM_END_ATTRIBUTES()
	public:
		DMCode OnAttributeCurSel(LPCWSTR lpszValue, bool bLoadXml);
	public:
		int									   m_iSelItem;						 ///< ��ǰѡ����   
		int									   m_iHoverItem;					 ///< ��ǰͣ����
		int									   m_iDefItemHei;					 ///< ���Ĭ�ϸ߶�
		DMColor								   m_crItemBg; 
		DMColor							       m_crItemSelBg; 
		DMSmartPtrT<DUIItemPanel>			   m_pCapturePanel;					 ///< ��ǰ������setcapture�����,�����ֻ����갴�µ�˲�����ã��������
		bool                                   m_bNoDrawBg;                       
	};
}//namespace DM

