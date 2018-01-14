
#pragma once
#include "..\..\Inc\Control\ICtrlStatic.h"

class ICtrlStaticImpl : public ICtrlStatic
{
public:
	ICtrlStaticImpl(IUiFeatureKernel *pUiKernel);
	virtual ~ICtrlStaticImpl();

	// ���ÿؼ����ı�
	virtual bool SetText(LPCWSTR pszText);
	virtual LPCWSTR GetText();

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
	void OnPaint(CDrawingBoard &DrawBoard);
	// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
	virtual LRESULT ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam);

private:
	IPropertyImage*				m_pPropImage;
	IPropertyFont*				m_pPropFont; 
	IPropertyString*			m_pPropText;
	IPropertyInt*				m_pPorpTextLeftGlow;			// ������߾�
	IPropertyInt*				m_pPorpTextTopGlow;				// �����ϱ߾�
	IPropertyInt*				m_pPorpTextRightGlow;			// �����ұ߾�
	IPropertyInt*				m_pPorpTextBottomGlow;			// �����±߾�
};
