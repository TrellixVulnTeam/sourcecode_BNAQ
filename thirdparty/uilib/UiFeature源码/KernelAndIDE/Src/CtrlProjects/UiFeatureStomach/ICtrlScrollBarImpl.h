
#pragma once
#include "..\..\Inc\Control\ICtrlScrollBar.h"

#include "IScrollBarPainterImpl.h"

class ICtrlScrollBarImpl : public ICtrlScrollBar
{
friend class IScrollBarPainterImpl;

public:
	ICtrlScrollBarImpl(IUiFeatureKernel *pUiKernel);
	virtual ~ICtrlScrollBarImpl();

	// Get  SCROLLBARINFO
	virtual bool GetScrollBarInfo(PSCROLLBARINFO pScrollInfo) const;
	// Get  SCROLLINFO
	virtual bool GetScrollInfo(LPSCROLLINFO lpScrollInfo, UINT nMask = SIF_ALL);
	// ���� enable
	virtual bool EnableScrollBar(UINT nArrowFlags = ESB_ENABLE_BOTH);	
	// �õ�����λ��
	virtual int GetScrollPos() const;
	// ���ù�������
	virtual int GetScrollLimit();	
	// �Ƿ���ʾ������
	virtual void ShowScrollBar(bool bShow = TRUE);
	// ���ù���λ��
	virtual int SetScrollPos(int nPos,bool bRedraw = TRUE);
	// ���ù�����Χ
	virtual void SetScrollRange(int nMinPos, int nMaxPos,bool bRedraw = TRUE);
	// �õ�������Χ
	virtual void GetScrollRange(LPINT lpMinPos, LPINT lpMaxPos) const;
	// ���ù��� ��Ϣ
	virtual bool SetScrollInfo(LPSCROLLINFO lpScrollInfo, bool bRedraw = TRUE);

protected:
	// �����ؼ����ڴ��������Լ��Ŀؼ�����
	// bIsNewCtrl��trueʱ˵����Builder���ã��´���һ���ؼ�����Ҫ��ʼ�����Եĸ���Ĭ��ֵ
	// false��˵������Ƥ�����Ѿ���ʼ����ϣ����Դ�����ϵ�ʱ�򣬴�xml�ж�ȡ������ֵ�Ѿ���ֵ����ˣ������ٳ�ʼ��������xml�е�ֵ�ᱻ���
	virtual bool CreateControlPropetry(bool bIsNewCtrl);
	// ��ʼ���ؼ�
	virtual void OnCreate();
	// �ؼ���ʼ�����
	virtual void OnFinalCreate();
	// ���ٿؼ�
	virtual void OnDestroy();
	// ���ƿؼ�
	virtual void OnPaint(CDrawingBoard &DrawBoard);
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
	// �ؼ�ȡ�ý��㣬ͨ��Tab����ת������ؼ�
	virtual void OnSetFocus();
	// �ؼ�ʧȥ����
	virtual void OnKillFocus();
	// ��������Ϣ
	virtual void OnMouseWheel(WPARAM wParam, LPARAM lParam);
	// �ƶ������ÿؼ�λ��
	virtual void OnSize();
	// ����϶��ؼ�
	virtual void OnMouseDragging(POINT pt);
	// ���ƿؼ��Ķ����������Ҫ����ˢ�½��棬����true�����򷵻�false
	// �˺����ɶ�ʱ��������ÿ100���봥��һ��
	virtual bool OnDrawAnimation();
	// Builderˢ�����ԣ��˺�����ֻҪ���¼��ؿؼ����Լ���
	virtual void OnBuilderRefreshProp(IPropertyBase* pPropBase);
	// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
	virtual LRESULT ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam);
	// ��ʱ��
	virtual void OnTimer(UINT nTimerId);
	//��ֱ����������
	virtual void OnVScroll(UINT nSBCode, UINT nPos, IControlBase* pScrollBar);
	//ˮƽ����������
	virtual void OnHScroll(UINT nSBCode, UINT nPos, IControlBase* pScrollBar);

private:
	void PrepareScrollBarPainter();
	void PrepareScrollBarOwner();

private:

	//////////////////////////////////////////////////////////////////////////////
	// ˮƽ����������
	IPropertyImage*		m_pPropHSBLineRightImages[SBStateNum]; 
	IPropertyImage*		m_pPropHSBGotoRightImages[SBStateNum]; 
	IPropertyImage*		m_pPropHSBGotoLeftImages[SBStateNum]; 
	IPropertyImage*		m_pPropHSBThumbImages[SBStateNum];
	IPropertyImage*		m_pPropHSBBGImages[SBStateNum];
	IPropertyImage*		m_pPropHSBPageLeftImages[SBStateNum];
	IPropertyImage*		m_pPropHSBPageRightImages[SBStateNum];
	IPropertyImage*		m_pPropHSBLineLeftImages[SBStateNum]; 

	//////////////////////////////////////////////////////////////////////////////
	// ��ֱ����������
	IPropertyImage*		m_pPropVSBLineDownImages[SBStateNum]; 
	IPropertyImage*		m_pPropVSBGotoBottomImages[SBStateNum]; 
	IPropertyImage*		m_pPropVSBGotoTopImages[SBStateNum]; 
	IPropertyImage*		m_pPropVSBThumbImages[SBStateNum];
	IPropertyImage*		m_pPropVSBBGImages[SBStateNum];
	IPropertyImage*		m_pPropVSBPageUpImages[SBStateNum];
	IPropertyImage*		m_pPropVSBPageDownImages[SBStateNum];
	IPropertyImage*		m_pPropVSBLineUpImages[SBStateNum]; 

	//////////////////////////////////////////////////////////////////////////////

	
	IPropertyComboBox*	m_PropType;				// ������Type���� ��ֱ/ˮƽ
	IPropertyString*	m_PropOwnerCtrlName;	// ��������ʹ���ߵ�����
	IControlBase*		m_pOwnerCtrl;			// ��������ʹ���ߵ�ָ��
	IScrollBarPainter*	m_pPainter;				// ���������ƽӿ�
};
