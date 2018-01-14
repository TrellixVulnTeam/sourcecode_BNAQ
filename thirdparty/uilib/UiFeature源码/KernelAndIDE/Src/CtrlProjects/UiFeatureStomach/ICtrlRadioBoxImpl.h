#pragma once
#include "..\..\Inc\Control\ICtrlRadioBox.h"

class ICtrlRadioBoxImpl : public ICtrlRadioBox
{
public:
	ICtrlRadioBoxImpl(IUiFeatureKernel *pUiKernel);
	virtual ~ICtrlRadioBoxImpl();

	// ��������
	void SetText(LPCWSTR pText, bool bRedraw);

	// ����ѡ������
	void SetCheck(bool bCheck);

	// ȡ��ѡ������
	bool GetCheck();

	//���÷���ID
	virtual void SetGroupID(int nGroupId);

	//��ȡ����ID
	virtual int GetGroupID();

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
	// ���������
	virtual void OnLButtonDown(POINT pt);
	// ������̧��
	virtual void OnLButtonUp(POINT pt);
	// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
	virtual LRESULT ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam);

	// ���ÿؼ����
	virtual IPropertyCursor* OnSetCursor(POINT pt);

private:
	typedef enum enumRadioState
	{
		RadioStateInvaild = -1,
		RadioStateUncheckNormal,
		RadioStateUncheckHot,
		RadioStateUncheckPressed,
		RadioStateUncheckDisabled,
		RadioStateCheckNormal,
		RadioStateCheckHot,
		RadioStateCheckPressed,
		RadioStateCheckDisabled,
		RadioStateNum
	}RADIOSTATE;

private:
	void ChangeRadioState(RADIOSTATE state);

private:
	// ����Ƿ���
	bool				m_bIsLButtonDown;

	ULONG				m_mouseFlag;
	// �Ƿ�check
	bool				m_bCheck;
	RADIOSTATE			m_enumRadioSate;


	//////////////////////////////////////////////////////////////////////////
	IPropertyImage* m_pPropsBack[RadioStateNum];
	IPropertyImage* m_pPropsBox[RadioStateNum];
	IPropertyImage* m_pPropsGraphic[RadioStateNum];
	IPropertyFont* m_pPropsFont[RadioStateNum];

	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	IPropertyString*	m_pPropText;
	IPropertyBool*		m_pShowText;

	//////////////////////////////////////////////////////////////////////////
	IPropertyInt* m_pGroupID;	//����ID

	//////////////////////////////////////////////////////////////////////////
	IPropertyBool*		m_pUpDownMode;
	IPropertyInt*		m_pX;
	IPropertyInt*		m_pY;

	IPropertyInt*		m_pTextOffsetLeft;
	IPropertyInt*		m_pTextOffsetBottom;
	IPropertyInt*		m_pTextOffsetTop;
	IPropertyInt*		m_pTextOffsetRight;

	//////////////////////////////////////////////////////////////////////////
	IPropertyCursor*	m_pCursor;	//���
};