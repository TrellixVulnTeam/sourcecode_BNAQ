
#pragma once
#include <assert.h>
#include "..\..\Inc\Control\ICtrlScrollBar.h"

class ICtrlScrollBarImpl;

typedef enum enumSbMode
{
	SBModeWindows = 0,
	SBModeMac,
	SBModeNum
}SBMODE;

typedef enum enumSbState
{
	SBStateInvalid = -1,
	SBStateNormal,
	SBStatePresudoHover,
	SBStateHover,
	SBStateDown,
	//�ڴ�֮ǰ����ScrollBar��״̬
	SBStateNum
}SBSTATE;

typedef enum enumDragType
{
	SBDragPageNone = 0,
	SBDragPageIncrease,
	SBDragPageDecrease,
	SBDragLineIncrease,
	SBDragLineDecrease,
	SBDragThumb,
	SBDragTypeNum
}SBDRAGTYPE;

typedef enum enumType
{
	SBTypeVertical = 0,
	SBTypeHorizontal,
	SBTypeNum
}SBTYPE;

class IScrollBarPainter
{
public:
	// con
	IScrollBarPainter(ICtrlScrollBarImpl* pScrollBar);
	// des
	virtual ~IScrollBarPainter();
public:	 
	virtual bool SetScrollInfo(LPSCROLLINFO lpScrollInfo, bool bRedraw = TRUE);
	virtual int  SetScrollPos(int nPos, bool bRedraw = TRUE);
	virtual void SetScrollRange(int nMinPos, int nMaxPos, bool bRedraw = TRUE);
	virtual bool EnableScrollBar(UINT nArrowFlags = ESB_ENABLE_BOTH);
	virtual bool GetScrollBarInfo(PSCROLLBARINFO pScrollInfo) const;
	virtual bool GetScrollInfo(LPSCROLLINFO lpScrollInfo, UINT nMask = SIF_ALL);
	virtual int  GetScrollPos() const;
	virtual int  GetScrollLimit();
	virtual void GetScrollRange(LPINT lpMinPos, LPINT lpMaxPos) const;
	virtual void ShowScrollBar(bool bShow = TRUE);
	// ���ƿؼ�
	virtual void OnPaint(CDrawingBoard &DstDc) = 0;
	// ������
	virtual void OnMouseEnter(POINT pt) = 0;
	// ����Ƴ�
	virtual void OnMouseLeave(POINT pt) = 0;
	// ����ƶ�
	virtual void OnMouseMove(POINT pt) = 0;
	// ���������
	virtual void OnLButtonDown(POINT pt) = 0;
	// ������̧��
	virtual void OnLButtonUp(POINT pt) = 0;
	// ������˫��
	virtual void OnLButtonDbClick(POINT pt) = 0;
	// ��������Ϣ
	virtual void OnMouseWheel(WPARAM wParam, LPARAM lParam) = 0;
	// �ƶ������ÿؼ�λ��
	virtual void OnSize() = 0;
	// ����϶��ؼ�
	virtual void OnMouseDragging(POINT pt) = 0;
	// ���ƿؼ��Ķ����������Ҫ����ˢ�½��棬����true�����򷵻�false
	// �˺����ɶ�ʱ��������ÿ100���봥��һ��
	virtual bool OnDrawAnimation() = 0;
	// ��ʱ��
	virtual void OnTimer(UINT nTimerId) = 0;

protected:
	virtual void SetScrollBarElementsPos(bool bShow = TRUE) = 0;

protected:
	
	int									m_nMin; 
	int									m_nMax; 
	int									m_nPos; 
	int									m_nTrackPos; 
	int									m_nStartPos;
	UINT								m_nPage;
	UINT								m_nDoubleClickTime;
	ULONG								m_uMouseFlag;
	bool								m_bIsShow;
	SBSTATE								m_enumSBState;
	SBDRAGTYPE							m_enumSBDragType;
	ICtrlScrollBarImpl* 				m_pScrollBar;
};
