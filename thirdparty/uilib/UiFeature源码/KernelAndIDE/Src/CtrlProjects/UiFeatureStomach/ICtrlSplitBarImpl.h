#pragma once
#include "..\..\Inc\Control\ICtrlSplitBar.h"

class ICtrlSplitBarImpl : public ICtrlSplitBar
{
public:
	ICtrlSplitBarImpl(IUiFeatureKernel *pUiKernel);
	virtual ~ICtrlSplitBarImpl();

	BEGIN_CTRL_NOTIFY
		CTRL_NOTIFY_HANDLER(WM_WINDOWPOSCHANGED, OnWindowPosChanged)
	END_CTRL_NOTIFY

	//���÷ָ����ؼ������ͣ�bHorzΪTRUEʱ��ʾˮƽ�ָ���������Ϊ��ֱ�ָ���
	virtual void SetSplitterType(bool bHorz);

	//����ˮƽ�ָ����������Сֵ��nTopMinΪ����������Сֵ,nBottomMinΪ�ײ��������Сֵ
	virtual void SetSplitterHorzMin(int nTopMin, int nBottomMin);

	//���ô�ֱ�ָ����������Сֵ,nLeftMinΪ���������Сֵ,nRightMinΪ�Ҳ��������Сֵ
	virtual void SetSplitterVertMin(int nLeftMin, int nRightMin);

	//��ȡ���������Сֵ
	virtual int GetTopLeftMin();

	//��ȡ�׻�������Сֵ
	virtual int GetBottomRightMin();

	//��ȡͼ��ĳ���
	virtual int GetGraphLength();

	//����ͼ��ĳ���
	virtual void SetGraphLength(int nGraphLength, bool bRedraw);

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
	// ����ƶ�
	virtual void OnMouseMove(POINT pt);
	// ����Ƴ�
	virtual void OnMouseLeave(POINT pt);
	// ���������
	virtual void OnLButtonDown(POINT pt);
	// ������̧��
	virtual void OnLButtonUp(POINT pt);
	// ����ӿڻ��������Ի����ʼ����ɵ�ʱ�����
	// �ؼ�ͨ����������ӿڣ�����������ӿں�����ͨ�������ؼ�������ȡ�õ�ǰ�Ի�����������ؼ���
	virtual void OnWindowFinalCreate();
	// ���ÿؼ����
	virtual IPropertyCursor* OnSetCursor(POINT pt);
	// �ƶ������ÿؼ�λ��
	virtual void OnSize();

	// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
	virtual LRESULT ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam);

	// ����ڿؼ��ڲ��϶��ؼ��������Ϣ�����Դ���ؼ��ڲ���ק�Ķ�����Ҳ���Դ���ͬ�ؼ�֮����קʵ�����ݴ���
	virtual void OnMouseDragging(POINT pt);

	// ����϶�����������̧����ꡣpDragCtrl����ק��Դ�ؼ�
	virtual void OnDragStop(IControlBase* pDragCtrl, POINT pt, WPARAM wParam, LPARAM lParam);

	int OnWindowPosChanged(WPARAM wParam, LPARAM lParam);

	static int FunComp(const void * p1,const void * p2);

private:
	typedef enum enumSplitBarState
	{
		SplitStateInvaild = -1,
		SplitStateNormal,
		SplitStateHot,
		SplitStatePressed,
		SplitStateDisabled,
		RadioStateNum
	}SPLITBARSTATE;

	struct PANEORDER
	{
		int idx;
		IControlBase *pPane;
		int pr;
		int min;
		int sz;
	};

private:
	void ChangeSplitState(SPLITBARSTATE state);
	char* w2c(char *pcstr,const wchar_t *pwstr, size_t len);
	void Relayout();

protected:

	SPLITBARSTATE m_enumSplitSate;
	ULONG				m_mouseFlag;
	IPropertyImage* m_pImage[RadioStateNum];		//����ͼƬ
	IPropertyImage* m_pGraphic[RadioStateNum];		//ͼ��

	//////////////////////////////////////////////////////////////////////////
	IPropertyBool* m_pIsHorz;				//�Ƿ���ˮƽ�ָ���
	IPropertyInt*  m_pSplitSize;			//�ָ����Ŀ�Ȼ��߸߶�
	IPropertyInt*  m_pTopLeftMin;			//��һ�ָ��������Сֵ
	IPropertyInt*  m_pRightBottomMin;		//�ڶ��ָ��������Сֵ
	IPropertyString* m_pTopLeftName;		//��һ�ָ������Panel����
	IPropertyString* m_pRightBottomName;	//�ڶ��ָ������Panel����
	IPropertyInt*  m_pTopLeftSize;			//��һ�ָ�����Ŀ�Ȼ��߸߶�
	IPropertyInt*  m_pRightBottomSize;		//�ڶ��ָ�����Ŀ�Ȼ��߸߶�

	IPropertyInt*  m_pLTPriority;			//��һ�ָ��������ȼ�
	IPropertyInt*  m_pRBPriority;			//�ڶ��ָ��������ȼ�

	IPropertyInt*  m_pGraphLength;			//ͼ��ĳ���

	//////////////////////////////////////////////////////////////////////////
	IPropertyCursor*  m_pCursor;		//��קʱ�Ĺ��,������m_bTracking��ʱ����з���

protected:
	IControlBase* m_pTopLeftPanel;
	IControlBase* m_pRightBottomPanel;

private:
	INT m_nSplitPos;

	//�Ƿ����϶���
	BOOL m_bTracking;

	//��ʼ�����
	POINT m_ptClick;

	int m_iDragBeam;

	BOOL m_bInSplit;
};