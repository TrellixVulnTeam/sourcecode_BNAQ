//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "..\..\Inc\IPropertyFontBase.h"

class IPropertyFontBaseImpl : public IPropertyFontBase
{
public:
	IPropertyFontBaseImpl(IUiFeatureKernel* pUiKernel);
	virtual ~IPropertyFontBaseImpl();

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(xml_node* pXmlNode);
	// д��xml
	virtual bool AppendToXmlNode(xml_document &XmlStrObj, xml_node* pParentXmlNode);

	// ����������Ϣ
	virtual void SetFontProp(FONT_PROP *pFontProp);
	virtual FONT_PROP* GetFontProp();

	// �Ƿ���ָ����Ч
	virtual bool GetEffectState(FONT_EFFECT FontEffect);
	virtual void SetEffect(FONT_EFFECT FontEffect, bool bSet);

	// ��������
	virtual bool DrawFontText(CDrawingBoard &DstDc, LPCWSTR pszOutText, RECT DstRct);

	// ����ͼƬ�����ػ��־��������ɺ󣬽����´λ��Ƶ�ʱ�����´���ͼƬ����
	virtual void SetPictureTextRedrawSign();

	// ȡ�û������ֵľ��δ�С
	virtual bool GetTextDrawRect(CDrawingBoard* pDstBoard, LPCWSTR pszDrawText, RECT &DrawRect, RECT &RectInDc);
	// ����һ�����Կ�¡
	virtual bool Clone(IPropertyBase* pFromPropBase);

private:
	// ���Ƶ�ָ���ڴ�DC��
	bool DrawToBoard(CDrawingBoard &DstDc, LPCWSTR pszOutText, RECT DstRct);
	// ������Ӱ���ֵ�ָ���ڴ�DC��
	bool DrawShadowText(CDrawingBoard &DstDc, LPCWSTR pszOutText, RECT DstRct);
	// ����ͼƬ����
	bool DrawPictureText(CDrawingBoard &DstDc, LPCWSTR pszOutText, RECT DstRct);
	// �������ֻ��߼��������������
	bool DrawToBoardBranch(CDrawingBoard &DstDc, LPCWSTR pszOutText, RECT &DstRct, bool bIsMeasureString);

private:
	bool m_bRecreatePicText;
	FONT_PROP m_FontProp;
	// ͼƬ�����ڴ�DC
	CDrawingBoard m_PicTextBorad;
};
