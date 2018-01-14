//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"
#include "CDrawingBoard.h"

// ������ʾ��ʽ
enum FONT_SHOW_MODE
{
	// ������ʾ��������ʾ��Χĩβ����ʾ...
	FSM_ONE_ROW_NO_POINT	= 0,
	// ������ʾ��������ʾ��Χ��ʾ...
	FSM_ONE_ROW_POINT		= 1,
	// ������ʾ
	FSM_MULTI_ROW			= 2
};

// ����ģʽ
enum FONT_ALIGNING
{
	// ˮƽ����/��ֱ����
	FAL_LEFT_TOP		= 0,
	// ˮƽ����/��ֱ����
	FAL_MIDDLE			= 1,
	// ˮƽ����/��ֱ����
	FAL_RIGHT_BOTTOM	= 2
};

// ������Ч
enum FONT_EFFECT
{
	FE_NONE			= 0x00000000,
	// ��Ӱ����
	FE_SHADOW		= 0x00000001,
	// ģ������
	FE_OBSCURE		= 0x00000002
};

// ��������
struct FONT_PROP
{
	// �Ƿ�ΪͼƬ����
	bool bIsPicText;
	// �Ƿ�Ϊֱ������
	bool bIsZhiLiText;
	// ������Ϣ
	LOGFONTW Font;
	// ������ɫ
	COLORREF FontColor;
	// ��ֱͣ����Ϣ
	FONT_ALIGNING VAligning;
	// ˮƽͣ����Ϣ
	FONT_ALIGNING HAligning;
	// ��ʾ��ʽ
	FONT_SHOW_MODE ShowMode;
	// ������Ч
	UINT FontEffect;
};

class _declspec(novtable) IPropertyFontBase : public IPropertyBase
{
public:
	IPropertyFontBase(IUiFeatureKernel* pUiKernel);
	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData() = 0;
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(xml_node* pXmlNode) = 0;
	// д��xml
	virtual bool AppendToXmlNode(xml_document &XmlStrObj, xml_node* pParentXmlNode) = 0;

	// ����������Ϣ
	virtual void SetFontProp(FONT_PROP *pFontProp) = 0;
	virtual FONT_PROP* GetFontProp() = 0;

	// �Ƿ���ָ����Ч
	virtual bool GetEffectState(FONT_EFFECT FontEffect) = 0;
	virtual void SetEffect(FONT_EFFECT FontEffect, bool bSet) = 0;

	// ��������
	virtual bool DrawFontText(CDrawingBoard &DstDc, LPCWSTR pszOutText, RECT DstRct) = 0;

	// ����ͼƬ�����ػ��־��������ɺ󣬽����´λ��Ƶ�ʱ�����´���ͼƬ����
	virtual void SetPictureTextRedrawSign() = 0;

	// ȡ�û������ֵľ��δ�С
	// DrawRect�����ص�ʵ�ʵ���������ľ��δ�С�����ܻᳬ��DC�Ĵ�С
	// RectInDc��������DC�л��Ƶ�λ�ã����λ�ò���100%��ȷ����ͬ���������ƫ��
	virtual bool GetTextDrawRect(CDrawingBoard* pDstBoard, LPCWSTR pszDrawText, RECT &DrawRect, RECT &RectInDc) = 0;
};
