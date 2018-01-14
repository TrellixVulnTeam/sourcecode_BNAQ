
#pragma once
#include "..\ICtrlInterface.h"

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_SCROLLBAR						(L"ScrollBar")

class _declspec(novtable)ICtrlScrollBar : public ICtrlInterface
{
public:	
	ICtrlScrollBar(IUiFeatureKernel *pUiKernel);
	// Get  SCROLLBARINFO
	virtual bool GetScrollBarInfo(PSCROLLBARINFO pScrollInfo) const = 0;
	// Get  SCROLLINFO
	virtual bool GetScrollInfo(LPSCROLLINFO lpScrollInfo, UINT nMask = SIF_ALL) = 0;
	// ���� enable
	virtual bool EnableScrollBar(UINT nArrowFlags = ESB_ENABLE_BOTH) = 0;	
	// �õ�����λ��
	virtual int GetScrollPos() const = 0;
	// ���ù�������
	virtual int GetScrollLimit() = 0;	
	// �Ƿ���ʾ������
	virtual void ShowScrollBar(bool bShow = TRUE) = 0;
	// ���ù���λ��
	virtual int SetScrollPos(int nPos, bool bRedraw = TRUE) = 0;
	// ���ù�����Χ
	virtual void SetScrollRange(int nMinPos, int nMaxPos, bool bRedraw = TRUE) = 0;
	// �õ�������Χ
	virtual void GetScrollRange(LPINT lpMinPos, LPINT lpMaxPos) const = 0;
	// ���ù��� ��Ϣ
	virtual bool SetScrollInfo(LPSCROLLINFO lpScrollInfo, bool bRedraw = TRUE) = 0;
};
