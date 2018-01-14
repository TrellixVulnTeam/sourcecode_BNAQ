#pragma once
#include "..\..\Inc\Control\ICtrlCheckBox.h"

class ICtrlCheckBoxImpl : public ICtrlCheckBox
{
public:
	ICtrlCheckBoxImpl(IUiFeatureKernel *pUiKernel);
	virtual ~ICtrlCheckBoxImpl();

	// interface

	// ��������
	void SetText(LPCWSTR pText, bool bRedraw);

	// ����ѡ������
	void SetCheck(bool bCheck);

	// ȡ��ѡ������
	bool GetCheck();

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

private:
	// ����Ƿ���
	bool				m_bIsLButtonDown;
	// �Ƿ�check
	bool				m_bCheck;
	// ͼƬ���ϽǶ�λ��
	IPropertyInt*		m_pImageLeft;
	IPropertyInt*		m_pImageTop;
	// ��ѡ��״̬ͼƬ
	IPropertyImage*		m_pImageNormal;
	IPropertyImage*		m_pImageHover;
	IPropertyImage*		m_pImageDown;
	IPropertyImage*		m_pImageDisbale;
	// ѡ��״̬ͼƬ
	IPropertyImage*		m_pImageCheckNormal;
	IPropertyImage*		m_pImageCheckHover;
	IPropertyImage*		m_pImageCheckDown;
	IPropertyImage*		m_pImageCheckDisbale;
	// ����
	IPropertyString*	m_pPropText;
	// �������ϽǶ�λ��
	IPropertyInt*		m_pTextLeft;
	IPropertyInt*		m_pTextTop;
	// ����
	IPropertyGroup*		m_pPropFontGroup;
	IPropertyFont*		m_pPropFontNormal;
	IPropertyFont*		m_pPropFontHover;
	IPropertyFont*		m_pPropFontDown;
	IPropertyFont*		m_pPropFontDisable;
};