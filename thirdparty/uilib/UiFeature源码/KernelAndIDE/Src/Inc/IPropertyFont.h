//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"
#include "IPropertyFontBase.h"

class _declspec(novtable) IPropertyFont : public IPropertyBase
{
public:
	IPropertyFont(IUiFeatureKernel* pUiKernel);
	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData() = 0;
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(xml_node* pXmlNode) = 0;
	// д��xml
	virtual bool AppendToXmlNode(xml_document &XmlStrObj, xml_node* pParentXmlNode) = 0;

	virtual const WCHAR * GetFontBaseName() = 0;

	// ����������Ϣ
	virtual void SetFontBaseProp(IPropertyFontBase *pFontProp) = 0;
	virtual IPropertyFontBase* GetFontBaseProp() = 0;

	// ��������
	virtual bool DrawFontText(CDrawingBoard &DstDc, LPCWSTR pszOutText, RECT DstRct) = 0;

	// ����ͼƬ�����ػ��־��������ɺ󣬽����´λ��Ƶ�ʱ�����´���ͼƬ����
	virtual void SetPictureTextRedrawSign() = 0;

	// ȡ�û������ֵľ��δ�С
	// DrawRect�����ص�ʵ�ʵ���������ľ��δ�С�����ܻᳬ��DC�Ĵ�С
	// RectInDc��������DC�л��Ƶ�λ�ã����λ�ò���100%��ȷ����ͬ���������ƫ��
	virtual bool GetTextDrawRect(CDrawingBoard* pDstBoard, LPCWSTR pszDrawText, RECT &DrawRect, RECT &RectInDc) = 0;
};
