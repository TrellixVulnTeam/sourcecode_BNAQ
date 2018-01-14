//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "..\..\Inc\IPropertyFont.h"

class IPropertyFontImpl : public IPropertyFont
{
public:
	IPropertyFontImpl(IUiFeatureKernel* pUiKernel);
	virtual ~IPropertyFontImpl();

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(xml_node* pXmlNode);
	// д��xml
	virtual bool AppendToXmlNode(xml_document &XmlStrObj, xml_node* pParentXmlNode);

	virtual const WCHAR * GetFontBaseName();

	// ����������Ϣ
	virtual void SetFontBaseProp(IPropertyFontBase *pFontProp);
	virtual IPropertyFontBase* GetFontBaseProp();

	// ��������
	virtual bool DrawFontText(CDrawingBoard &DstDc, LPCWSTR pszOutText, RECT DstRct);

	// ����ͼƬ�����ػ��־��������ɺ󣬽����´λ��Ƶ�ʱ�����´���ͼƬ����
	virtual void SetPictureTextRedrawSign();

	// ȡ�û������ֵľ��δ�С
	virtual bool GetTextDrawRect(CDrawingBoard* pDstBoard, LPCWSTR pszDrawText, RECT &DrawRect, RECT &RectInDc);
	// ����һ�����Կ�¡
	virtual bool Clone(IPropertyBase* pFromPropBase);

private:
	void SetNeedRedraw();
};
