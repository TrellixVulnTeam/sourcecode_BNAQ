
#include "StdAfx.h"
#include "ICtrlStaticImpl.h"
#include "..\..\Inc\IControlManager.h"
#include "..\..\Inc\ICommonFun.h"

ICtrlStatic::ICtrlStatic(IUiFeatureKernel *pUiKernel) : ICtrlInterface(pUiKernel) {}

ICtrlStaticImpl::ICtrlStaticImpl(IUiFeatureKernel *pUiKernel) : ICtrlStatic(pUiKernel)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_STATIC);

	// �˿ؼ�����ҪTips���ԣ�����xml��Ϣ���Ż����ܣ�ɾ�����д��룬���±���ؼ����˿ؼ��ͻ�֧��ϵͳTips
	m_bHaveSysTipsProp = false;

	m_pPropImage = NULL;
	m_pPropFont = NULL;
	m_pPropText = NULL;
	m_pPorpTextLeftGlow = NULL;	
	m_pPorpTextTopGlow = NULL;		
	m_pPorpTextRightGlow = NULL;
	m_pPorpTextBottomGlow = NULL;
}

ICtrlStaticImpl::~ICtrlStaticImpl()
{

}

// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
LRESULT ICtrlStaticImpl::ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}

// ��ʼ���ؼ�
void ICtrlStaticImpl::OnCreate()
{

}

// �ؼ���ʼ�����
void ICtrlStaticImpl::OnFinalCreate()
{

}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlStaticImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	// ���ñ���ͼƬ�����塢��ʾ��������
	m_pPropImage = (IPropertyImage*)CreatePropetry(NULL, OTID_IMAGE, "Image", "����ͼƬ");
	m_pPropFont = (IPropertyFont*)CreatePropetry(NULL, OTID_FONT, "Font", "����");
	m_pPropText = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "Text", "��ʾ������");
	m_pPorpTextLeftGlow = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "TextLeftGlow", "������߾�");	
	m_pPorpTextTopGlow = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "TextTopGlow", "�����ϱ߾�");	
	m_pPorpTextRightGlow = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "TextRightGlow", "�����ұ߾�");
	m_pPorpTextBottomGlow = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "TextBottomGlow", "�����±߾�");

	if (bIsNewCtrl && m_pWindowBase != NULL)
	{
		// ����Ĭ�ϲ����������Ϣ
		m_pPropBase_RcvMouseMsg->SetValue(false);
	}
	return true;
}

// ���ÿؼ��ı�
bool ICtrlStaticImpl::SetText(LPCWSTR pszText)
{
	if (NULL == pszText)
		return false;

	if (m_pPropText == NULL)
		m_pPropText = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "Text", "", true);

	if (m_pPropText == NULL)
		return false;

	m_pPropText->SetString(pszText);
	return true;
}

LPCWSTR ICtrlStaticImpl::GetText()
{
	if (m_pPropText == NULL)
		return NULL;

	return m_pPropText->GetString();
}

// ���ٿؼ�
void ICtrlStaticImpl::OnDestroy()
{

}

// ���ƿؼ�
void ICtrlStaticImpl::OnPaint(CDrawingBoard &DrawBoard)
{
	if (NULL != m_pPropImage)
		m_pPropImage->DrawImage(DrawBoard, this->GetClientRect());

	if (NULL != m_pPropFont && m_pPropText != NULL && m_pPropText->GetLength() > 0)
	{
		RECT rcText = GetClientRect();
		if (m_pPorpTextLeftGlow)
			rcText.left += m_pPorpTextLeftGlow->GetValue();
		if (m_pPorpTextRightGlow)
			rcText.right -= m_pPorpTextRightGlow->GetValue();
		if (m_pPorpTextTopGlow)
			rcText.top += m_pPorpTextTopGlow->GetValue();
		if (m_pPorpTextBottomGlow)
			m_pPorpTextBottomGlow->GetValue();

		m_pPropFont->DrawFontText(DrawBoard, m_pPropText->GetString(), rcText);
	}
}
