#pragma once
#include "IScrollBarPainter.h"


class IScrollBarPainterImpl : public IScrollBarPainter
{
public:
	IScrollBarPainterImpl(ICtrlScrollBarImpl* pScrollBar);
	virtual ~IScrollBarPainterImpl();
public:
	// ���ƿؼ�
	virtual void OnPaint(CDrawingBoard &DstDc);
	// ������
	virtual void OnMouseEnter(POINT pt);
	// ����Ƴ�
	virtual void OnMouseLeave(POINT pt);
	// ����ƶ�
	virtual void OnMouseMove(POINT pt);
	// ���������
	virtual void OnLButtonDown(POINT pt);
	// ������̧��
	virtual void OnLButtonUp(POINT pt);
	// ������˫��
	virtual void OnLButtonDbClick(POINT pt);
	// ��������Ϣ
	virtual void OnMouseWheel(WPARAM wParam, LPARAM lParam);
	// �ƶ������ÿؼ�λ��
	virtual void OnSize();
	// ����϶��ؼ�
	virtual void OnMouseDragging(POINT pt);
	// ���ƿؼ��Ķ����������Ҫ����ˢ�½��棬����true�����򷵻�false
	// �˺����ɶ�ʱ��������ÿ100���봥��һ��
	virtual bool OnDrawAnimation();
	// ��ʱ��
	virtual void OnTimer(UINT nTimerId);

private:
	void DrawHorizontalScrollBar(CDrawingBoard &DstDc);
	void DrawVerticalScrollBar(CDrawingBoard &DstDc);
	void DrawPageLeftImage(CDrawingBoard &DstDc, SBSTATE state);
	void DrawPageRightImage(CDrawingBoard &DstDc, SBSTATE state);
	void DrawHThumbImage(CDrawingBoard &DstDc, SBSTATE state);
	void DrawPageUpImage(CDrawingBoard &DstDc, SBSTATE state);
	void DrawPageDownImage(CDrawingBoard &DstDc, SBSTATE state);
	void DrawVThumbImage(CDrawingBoard &DstDc, SBSTATE state);
	void SetVSBElementsPos(RECT parent);
	void SetHSBElementsPos(RECT parent);
	void MoveThumb();
	void DragThumb(POINT pt);
	void ChangeScrollBarStyle(SBSTATE state);

protected:
	void SetScrollBarElementsPos(bool bShow = TRUE);

private:

	int							m_nHThumbHeight;
	int							m_nHThumbWidth;	
	int							m_nVThumbHeight;
	int							m_nVThumbWidth;
	int							m_nTimerId;
	int							m_nDistant;

	RECT						m_rctHThumb;
	RECT						m_rctPageLeft;
	RECT						m_rctPageRight;
	RECT						m_rctVThumb;
	RECT						m_rctPageUp;
	RECT						m_rctPageDown;

	POINT						m_ptCurrent;
};
