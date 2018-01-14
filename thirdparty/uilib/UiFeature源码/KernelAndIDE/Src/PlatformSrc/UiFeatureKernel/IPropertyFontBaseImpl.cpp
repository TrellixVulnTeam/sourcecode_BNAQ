
#include "stdafx.h"
#include "IPropertyFontBaseImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\IUiFeatureKernel.h"
#include "..\..\Inc\IUiEngine.h"

#include <atlstr.h>
using namespace ATL;

#pragma warning(disable:4244)

//////////////////////////////////////////////////////////////////////////
// �ı�ϵͳ���Ի���ר�õ���
class CChineseLanguageEnv
{
public:
	CChineseLanguageEnv(void)
	{
		m_lcid = GetThreadLocale();
		SetThreadLocale(MAKELCID(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED), SORT_CHINESE_PRC));
	}

	~CChineseLanguageEnv(void)
	{
		SetThreadLocale(m_lcid);
	}

private:
	LCID m_lcid;
};
//////////////////////////////////////////////////////////////////////////

IPropertyFontBaseImpl::IPropertyFontBaseImpl(IUiFeatureKernel* pUiKernel) : IPropertyFontBase(pUiKernel)
{
	SetObjectType(_T(PROP_TYPE_FONT_BASE_NAME));
	SetObjectName(L"Ĭ�����壺���壬12");

	m_bIsActiveProp = true;

	m_bRecreatePicText = true;
	m_FontProp.bIsZhiLiText = false;
	m_FontProp.bIsPicText = false;
	m_FontProp.FontColor = 0;

	memset(&m_FontProp.Font, 0, sizeof(LOGFONTA));
	m_FontProp.Font.lfHeight = 12;
	m_FontProp.Font.lfWidth = 0;
	m_FontProp.Font.lfEscapement = 0;
	m_FontProp.Font.lfOrientation = 0;
	m_FontProp.Font.lfWeight = FW_NORMAL;
	m_FontProp.Font.lfItalic = 0;
	m_FontProp.Font.lfUnderline = 0;
	m_FontProp.Font.lfStrikeOut = 0;
	m_FontProp.Font.lfCharSet = GB2312_CHARSET;
	m_FontProp.Font.lfOutPrecision = OUT_DEFAULT_PRECIS;
	m_FontProp.Font.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	m_FontProp.Font.lfQuality = PROOF_QUALITY;
	m_FontProp.Font.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
	wcscpy_s(m_FontProp.Font.lfFaceName, LF_FACESIZE, L"����");

	m_FontProp.HAligning = FAL_LEFT_TOP;
	m_FontProp.VAligning = FAL_MIDDLE;
	m_FontProp.ShowMode = FSM_ONE_ROW_NO_POINT;
	m_FontProp.FontEffect = FE_NONE;
}

IPropertyFontBaseImpl::~IPropertyFontBaseImpl()
{

}

bool IPropertyFontBaseImpl::IsRightData()
{
	return true;
}

FONT_PROP* IPropertyFontBaseImpl::GetFontProp()
{
	return &m_FontProp;
}

void IPropertyFontBaseImpl::SetFontProp(FONT_PROP *pFontProp)
{
	if (pFontProp == NULL)
		return;

	m_FontProp = *pFontProp;
}

bool IPropertyFontBaseImpl::ReadPropertyFromXmlNode(xml_node* pXmlNode)
{
	if (pXmlNode == NULL)
		return false;

	const WCHAR * psz_id = XmlGetAttrValue(pXmlNode, _T(SKIN_OBJECT_ID));
	const WCHAR * psz_name = XmlGetAttrValue(pXmlNode, L"name");
	if (psz_id == NULL || psz_name == NULL)
		return false;

	xml_node Logfont = pXmlNode->child(L"logfont");
	xml_node Mode = pXmlNode->child(L"mode");
	if (!Logfont || !Mode)
		return false;

	// logfont
	const WCHAR * psz_lfFaceName = XmlGetAttrValue(&Logfont, L"lfFaceName");
	const WCHAR * psz_lfHeight = XmlGetAttrValue(&Logfont, L"lfHeight");
	const WCHAR * psz_lfWidth = XmlGetAttrValue(&Logfont, L"lfWidth");
	const WCHAR * psz_lfEscapement = XmlGetAttrValue(&Logfont, L"lfEscapement");
	const WCHAR * psz_lfOrientation = XmlGetAttrValue(&Logfont, L"lfOrientation");
	const WCHAR * psz_lfWeight = XmlGetAttrValue(&Logfont, L"lfWeight");
	const WCHAR * psz_lfItalic = XmlGetAttrValue(&Logfont, L"lfItalic");
	const WCHAR * psz_lfUnderline = XmlGetAttrValue(&Logfont, L"lfUnderline");
	const WCHAR * psz_lfStrikeOut = XmlGetAttrValue(&Logfont, L"lfStrikeOut");
	const WCHAR * psz_lfCharSet = XmlGetAttrValue(&Logfont, L"lfCharSet");
	const WCHAR * psz_lfOutPrecision = XmlGetAttrValue(&Logfont, L"lfOutPrecision");
	const WCHAR * psz_lfClipPrecision = XmlGetAttrValue(&Logfont, L"lfClipPrecision");
	const WCHAR * psz_lfQuality = XmlGetAttrValue(&Logfont, L"lfQuality");
	const WCHAR * psz_lfPitchAndFamily = XmlGetAttrValue(&Logfont, L"lfPitchAndFamily");

	// mode
	const WCHAR * psz_color = XmlGetAttrValue(&Mode, L"color");
	const WCHAR * psz_VAligning = XmlGetAttrValue(&Mode, L"VAligning");
	const WCHAR * psz_HAligning = XmlGetAttrValue(&Mode, L"HAligning");
	const WCHAR * psz_ShowMode = XmlGetAttrValue(&Mode, L"ShowMode");
	const WCHAR * psz_Effect = XmlGetAttrValue(&Mode, L"Effect");

	if (psz_lfPitchAndFamily == NULL || psz_color == NULL || psz_lfFaceName == NULL || psz_lfHeight == NULL || psz_lfWidth == NULL || 
		psz_lfEscapement == NULL || psz_lfOrientation == NULL || psz_lfWeight == NULL || psz_lfItalic == NULL || psz_lfUnderline == NULL || 
		psz_lfStrikeOut == NULL || psz_lfCharSet == NULL || psz_lfOutPrecision == NULL || psz_lfClipPrecision == NULL || psz_lfQuality == NULL ||
		psz_VAligning == NULL || psz_HAligning == NULL || psz_ShowMode == NULL || psz_Effect == NULL)
		return false;

	SetObjectId(_wtoi(psz_id));
	SetObjectName(psz_name);

	// logfont
	wcscpy_s(m_FontProp.Font.lfFaceName, LF_FACESIZE, psz_lfFaceName);
	m_FontProp.Font.lfHeight = _wtoi(psz_lfHeight);
	m_FontProp.Font.lfWidth = _wtoi(psz_lfWidth);
	m_FontProp.Font.lfEscapement = _wtoi(psz_lfEscapement);
	m_FontProp.Font.lfOrientation = _wtoi(psz_lfOrientation);
	m_FontProp.Font.lfWeight = _wtoi(psz_lfWeight);
	m_FontProp.Font.lfItalic = _wtoi(psz_lfItalic);
	m_FontProp.Font.lfUnderline = _wtoi(psz_lfUnderline);
	m_FontProp.Font.lfStrikeOut = _wtoi(psz_lfStrikeOut);
	m_FontProp.Font.lfCharSet = _wtoi(psz_lfCharSet);
	m_FontProp.Font.lfOutPrecision = _wtoi(psz_lfOutPrecision);
	m_FontProp.Font.lfClipPrecision = _wtoi(psz_lfClipPrecision);
	m_FontProp.Font.lfQuality = _wtoi(psz_lfQuality);
	m_FontProp.Font.lfPitchAndFamily = _wtoi(psz_lfPitchAndFamily);

	// mode
	m_FontProp.FontColor = _wtoi(psz_color);
	m_FontProp.HAligning = (FONT_ALIGNING)_wtoi(psz_HAligning);
	m_FontProp.VAligning = (FONT_ALIGNING)_wtoi(psz_VAligning);
	m_FontProp.ShowMode = (FONT_SHOW_MODE)_wtoi(psz_ShowMode);
	m_FontProp.FontEffect = _wtoi(psz_Effect);

	return true;
}

// д��xml
bool IPropertyFontBaseImpl::AppendToXmlNode(xml_document &XmlStrObj, xml_node* pParentXmlNode)
{
	// �������Ч���ԣ���д��XML
	if (!GetActivePropetry())
		return true;

	if (pParentXmlNode == NULL)
		return false;

	xml_node PropNode = pParentXmlNode->append_child(L"item");
	if (!PropNode)
		return false;

	AddIntAttrToNode(&PropNode, _T(SKIN_OBJECT_ID), (int)GetObjectId());
	AddStringAttrToNode(&PropNode, L"name", GetObjectName());

	xml_node Node_logfont = PropNode.append_child(L"logfont");
	if (!Node_logfont)
		return false;

	AddStringAttrToNode(&Node_logfont, L"lfFaceName", m_FontProp.Font.lfFaceName);
	AddIntAttrToNode(&Node_logfont, L"lfHeight", m_FontProp.Font.lfHeight);
	AddIntAttrToNode(&Node_logfont, L"lfWidth", m_FontProp.Font.lfWidth);
	AddIntAttrToNode(&Node_logfont, L"lfEscapement", m_FontProp.Font.lfEscapement);
	AddIntAttrToNode(&Node_logfont, L"lfOrientation", m_FontProp.Font.lfOrientation);
	AddIntAttrToNode(&Node_logfont, L"lfWeight", m_FontProp.Font.lfWeight);
	AddIntAttrToNode(&Node_logfont, L"lfItalic", m_FontProp.Font.lfItalic);
	AddIntAttrToNode(&Node_logfont, L"lfUnderline", m_FontProp.Font.lfUnderline);
	AddIntAttrToNode(&Node_logfont, L"lfStrikeOut", m_FontProp.Font.lfStrikeOut);
	AddIntAttrToNode(&Node_logfont, L"lfCharSet", m_FontProp.Font.lfCharSet);
	AddIntAttrToNode(&Node_logfont, L"lfOutPrecision", m_FontProp.Font.lfOutPrecision);
	AddIntAttrToNode(&Node_logfont, L"lfClipPrecision", m_FontProp.Font.lfClipPrecision);
	AddIntAttrToNode(&Node_logfont, L"lfQuality", m_FontProp.Font.lfQuality);
	AddIntAttrToNode(&Node_logfont, L"lfPitchAndFamily", m_FontProp.Font.lfPitchAndFamily);

	xml_node Node_mode = PropNode.append_child(L"mode");
	if (!Node_mode)
		return false;

	AddIntAttrToNode(&Node_mode, L"color", m_FontProp.FontColor);
	AddIntAttrToNode(&Node_mode, L"VAligning", m_FontProp.VAligning);
	AddIntAttrToNode(&Node_mode, L"HAligning", m_FontProp.HAligning);
	AddIntAttrToNode(&Node_mode, L"ShowMode", m_FontProp.ShowMode);
	AddIntAttrToNode(&Node_mode, L"Effect", m_FontProp.FontEffect);

	return true;
}

// �Ƿ���ָ����Ч
bool IPropertyFontBaseImpl::GetEffectState(FONT_EFFECT FontEffect)
{
	UINT nSet = (m_FontProp.FontEffect & FontEffect);
	return (nSet != 0);
}

void IPropertyFontBaseImpl::SetEffect(FONT_EFFECT FontEffect, bool bSet)
{
	if (bSet)
		m_FontProp.FontEffect |= FontEffect;
	else
		m_FontProp.FontEffect &= (~FontEffect);
}

// ��������
bool IPropertyFontBaseImpl::DrawFontText(CDrawingBoard &DstDc, LPCWSTR pszOutText, RECT DstRct)
{
	if (m_FontProp.bIsPicText)
	{
		return DrawPictureText(DstDc, pszOutText, DstRct);
	}
	else
	{
		if (GetEffectState(FE_SHADOW))
		{
			// ��Ӱ����
			return DrawShadowText(DstDc, pszOutText, DstRct);
		}
		else
		{
			return DrawToBoard(DstDc, pszOutText, DstRct);
		}
	}
}

// ����ͼƬ����
bool IPropertyFontBaseImpl::DrawPictureText(CDrawingBoard &DstDc, LPCWSTR pszOutText, RECT DstRct)
{
	if (RECT_WIDTH(DstRct) <= 0 || RECT_HEIGHT(DstRct) <= 0 || pszOutText == NULL || wcslen(pszOutText) <= 0 || this->GetUiKernel() == NULL)
		return false;

	RECT PicTextRct = {0, 0, RECT_WIDTH(DstRct), RECT_HEIGHT(DstRct)};

	if (m_bRecreatePicText)
		m_PicTextBorad.Delete();

	if (m_PicTextBorad.Create(RECT_WIDTH(PicTextRct), RECT_HEIGHT(PicTextRct), false, false))
	{
		bool bRet = false;
		if (GetEffectState(FE_SHADOW))
		{
			// ��Ӱ����
			bRet = DrawShadowText(m_PicTextBorad, pszOutText, PicTextRct);
		}
		else
		{
			bRet = DrawToBoard(m_PicTextBorad, pszOutText, PicTextRct);
		}

		if (!bRet)
			return false;
	}

	if (m_PicTextBorad.GetSafeHdc() == NULL)
		return false;

	m_bRecreatePicText = false;
	return m_PicTextBorad.AlphaBlendTo(DstDc, DstRct, PicTextRct, this->GetUiKernel());
}

// ���Ƶ�ָ���ڴ�DC��
bool IPropertyFontBaseImpl::DrawToBoard(CDrawingBoard &DstDc, LPCWSTR pszOutText, RECT DstRct)
{
	return DrawToBoardBranch(DstDc, pszOutText, DstRct, false);
}

// �������ֻ��߼��������������
bool IPropertyFontBaseImpl::DrawToBoardBranch(CDrawingBoard &DstDc, LPCWSTR pszOutText, RECT &DstRct, bool bIsMeasureString)
{
	CChineseLanguageEnv languageEnv;

	if (pszOutText == NULL || wcslen(pszOutText) <= 0 || IS_RECT_EMPTY(DstRct) || DstDc.GetSafeHdc() == NULL)
		return false;

	// ���ڱ༭���������Ĳ���ϵͳ������ֱ�����õģ���������Ҳֱ��ʹ�����charset
	m_FontProp.Font.lfCharSet = GB2312_CHARSET;

	Graphics DoGrap(DstDc.GetSafeHdc());

	// ����
	Gdiplus::Font TextFont(DstDc.GetSafeHdc(), &(m_FontProp.Font));
	// ������ɫ
	SolidBrush textBrush(Color(MAX_ALPHA, GetRValue(m_FontProp.FontColor), GetGValue(m_FontProp.FontColor), GetBValue(m_FontProp.FontColor)));

	Gdiplus::StringFormat strFormat;
	// ������� & ����»�������
	strFormat.SetHotkeyPrefix(HotkeyPrefixNone);
	// ������ʾЧ������������ʾ��Χ�ڣ�����µ�һ�����ֻ�������ϰ벿�֣���һ�н����ᱻ��ʾ
	strFormat.SetFormatFlags(StringFormatFlagsLineLimit);

	// ���ô�ֱ����ģʽ
	if (m_FontProp.VAligning == FAL_RIGHT_BOTTOM)
	{
		// ��ֱ����
		strFormat.SetLineAlignment(StringAlignmentFar);
	}
	else if (m_FontProp.VAligning == FAL_MIDDLE)
	{
		// ��ֱ����
		strFormat.SetLineAlignment(StringAlignmentCenter);
	}
	else
	{
		// ��ֱ����
		strFormat.SetLineAlignment(StringAlignmentNear);
	}

	// ����ˮƽ����
	if (m_FontProp.HAligning == FAL_RIGHT_BOTTOM)
	{
		// ˮƽ����
		strFormat.SetAlignment(StringAlignmentFar);
	}
	else if (m_FontProp.HAligning == FAL_MIDDLE)
	{
		// ˮƽ����
		strFormat.SetAlignment(StringAlignmentCenter);
	}
	else
	{
		// ˮƽ����
		strFormat.SetAlignment(StringAlignmentNear);
	}

	// GDI+Ĭ��������ʾ��ĩβ����...
	if (m_FontProp.ShowMode != FSM_MULTI_ROW)
	{
		// ��������ʾ
		strFormat.SetFormatFlags(StringFormatFlagsNoWrap);
		// ��������ʾ��Ĭ��ĩβ����...
		if (m_FontProp.ShowMode == FSM_ONE_ROW_POINT)
		{
			// ������ʾ��������ʾ��Χ��ʾ...
			strFormat.SetTrimming(StringTrimmingEllipsisCharacter);
		}
	}

	RectF OutFct;
	OutFct.X = DstRct.left;
	OutFct.Y = DstRct.top;
	OutFct.Width = RECT_WIDTH(DstRct);
	OutFct.Height = RECT_HEIGHT(DstRct);

	// win7 ���������壨�磺�źڣ���ʾ����Ӱ����
	DoGrap.SetTextRenderingHint(TextRenderingHintAntiAliasGridFit);

	if (bIsMeasureString)
	{
		// ��Ҫ����ո��ȣ�����StringFormat.MeasureTrailingSpacesö��ֵ��������Ҫ����ո��ȣ���ɺ���
		strFormat.SetFormatFlags(StringFormatFlagsMeasureTrailingSpaces);

		//// �����Ǽ������������С
		//PointF originPt;
		//originPt.X = originPt.Y = 0.0;
		//RectF getRctF;
		//getRctF.X = getRctF.Y = getRctF.Width = getRctF.Height = 0.0;
		//DoGrap.MeasureString(pszOutText, wcslen(pszOutText), &TextFont, originPt, &strFormat, &getRctF);
		//DstRct.left = (int)getRctF.X;
		//DstRct.right = DstRct.left + (int)getRctF.Width;
		//DstRct.top = (int)getRctF.Y;
		//DstRct.bottom = DstRct.top + (int)getRctF.Height;

		GraphicsPath path;
		FontFamily fontfamily;
		TextFont.GetFamily(&fontfamily);
		path.AddString(pszOutText, -1, &fontfamily, TextFont.GetStyle(), TextFont.GetSize(), PointF(0, 0), &strFormat);
		RectF rcBound;
		path.GetBounds(&rcBound);
		INIT_RECT(DstRct);
		DstRct.right = rcBound.Width;
		DstRct.bottom = rcBound.Height;
		return true;
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���¿�ʼʱ�������
	DoGrap.DrawString(pszOutText, wcslen(pszOutText), &TextFont, OutFct, &strFormat, &textBrush);

	if (GetEffectState(FE_OBSCURE))
	{
		// ģ������
	}

	return true;
}

// ȡ�û������ֵľ��δ�С
bool IPropertyFontBaseImpl::GetTextDrawRect(CDrawingBoard* pDstBoard, LPCWSTR pszDrawText, RECT &DrawRect, RECT &RectInDc)
{
	INIT_RECT(DrawRect);
	INIT_RECT(RectInDc);

	if (pszDrawText == NULL || wcslen(pszDrawText) <= 0 || pDstBoard == NULL || pDstBoard->GetDcSize().cx <= 0 || pDstBoard->GetDcSize().cy <= 0)
		return false;

	RECT drawRct;
	INIT_RECT(drawRct);
	SIZE dcSize = pDstBoard->GetDcSize();
	drawRct.right = dcSize.cx;
	drawRct.bottom = dcSize.cy;
	if (!DrawToBoardBranch(*pDstBoard, pszDrawText, drawRct, true))
		return false;

	DrawRect = drawRct;
	RectInDc = DrawRect;

	// ������DC�е�λ��

	// ���еľͲ�������
	if (m_FontProp.ShowMode == FSM_MULTI_ROW)
		return true;

	int nW = RECT_WIDTH(DrawRect);
	int nH = RECT_HEIGHT(DrawRect);

	// ���ô�ֱ����ģʽ
	if (m_FontProp.VAligning == FAL_RIGHT_BOTTOM)
	{
		// ��ֱ����
		RectInDc.bottom = dcSize.cy;
		RectInDc.top = RectInDc.bottom - nH;
	}
	else if (m_FontProp.VAligning == FAL_MIDDLE)
	{
		// ��ֱ����
		RectInDc.top = (dcSize.cy - nH) / 2;
		RectInDc.bottom = RectInDc.top + nH;
	}
	else
	{
		// ��ֱ����
		RectInDc.top = 0;
		RectInDc.bottom = RectInDc.top + nH;
	}

	// ����ˮƽ����
	if (m_FontProp.HAligning == FAL_RIGHT_BOTTOM)
	{
		// ˮƽ����
		RectInDc.right = dcSize.cx;
		RectInDc.left = RectInDc.right - nW;
	}
	else if (m_FontProp.HAligning == FAL_MIDDLE)
	{
		// ˮƽ����
		RectInDc.left = (dcSize.cx - nW) / 2;
		RectInDc.right = RectInDc.left + nW;
	}
	else
	{
		// ˮƽ����
		RectInDc.left = 0;
		RectInDc.right = RectInDc.left + nW;
	}

	if (RectInDc.left < 0)
		RectInDc.left = 0;

	if (RectInDc.right > dcSize.cx)
		RectInDc.right = dcSize.cx;

	if (RectInDc.top < 0)
		RectInDc.top = 0;

	if (RectInDc.bottom > dcSize.cy)
		RectInDc.bottom = dcSize.cy;

	return true;
}

// ������Ӱ���ֵ�ָ���ڴ�DC��
bool IPropertyFontBaseImpl::DrawShadowText(CDrawingBoard &DstDc, LPCWSTR pszOutText, RECT DstRct)
{
	if (!GetEffectState(FE_SHADOW) || DstDc.GetSafeHdc() == NULL || pszOutText == NULL || wcslen(pszOutText) <= 0 ||
		GetUiKernel() == NULL || GetUiKernel()->GetUiEngine() == NULL)
		return false;

	// ���ڱ༭���������Ĳ���ϵͳ������ֱ�����õģ���������Ҳֱ��ʹ�����charset
	m_FontProp.Font.lfCharSet = GB2312_CHARSET;

	DWORD dwFlags = 0;

	// ���ô�ֱ����ģʽ
	if (m_FontProp.VAligning == FAL_RIGHT_BOTTOM)
	{
		// ��ֱ����
		dwFlags |= DT_BOTTOM;
	}
	else if (m_FontProp.VAligning == FAL_MIDDLE)
	{
		// ��ֱ����
		dwFlags |= DT_VCENTER;
	}
	else
	{
		// ��ֱ����
		dwFlags |= DT_TOP;
	}

	// ����ˮƽ����
	if (m_FontProp.HAligning == FAL_RIGHT_BOTTOM)
	{
		// ˮƽ����
		dwFlags |= DT_RIGHT;
	}
	else if (m_FontProp.HAligning == FAL_MIDDLE)
	{
		// ˮƽ����
		dwFlags |= DT_CENTER;
	}
	else
	{
		// ˮƽ����
		dwFlags |= DT_LEFT;
	}

	// GDI+Ĭ��������ʾ��ĩβ����...
	if (m_FontProp.ShowMode != FSM_MULTI_ROW)
	{
		// ��������ʾ
		dwFlags |= DT_SINGLELINE;
		// ��������ʾ��Ĭ��ĩβ����...
		if (m_FontProp.ShowMode == FSM_ONE_ROW_POINT)
		{
		//	// ������ʾ��������ʾ��Χ��ʾ...
		//	dwFlags |= DT_WORDBREAK;
		}
	}
	else
	{
		// �Զ�����
		dwFlags |= DT_WORDBREAK | DT_EDITCONTROL;
	}

	::SetBkMode(DstDc.GetSafeHdc(), TRANSPARENT);

	LOGFONTW* pFont = &m_FontProp.Font;
	HFONT hNewFont = ::CreateFontW(pFont->lfHeight, pFont->lfWidth, pFont->lfEscapement, pFont->lfOrientation, pFont->lfWeight, pFont->lfItalic, pFont->lfUnderline, pFont->lfStrikeOut,
		pFont->lfCharSet, pFont->lfOutPrecision, pFont->lfClipPrecision, pFont->lfQuality, pFont->lfPitchAndFamily, pFont->lfFaceName);
	HFONT hOldFont = (HFONT)::SelectObject(DstDc.GetSafeHdc(), hNewFont);

	bool bRet = (GetUiKernel()->GetUiEngine()->DrawShadowText(DstDc.GetSafeHdc(), pszOutText, wcslen(pszOutText), &DstRct, dwFlags, m_FontProp.FontColor, RGB(0, 0, 0), 0, 0) != 0);

	::SelectObject(DstDc.GetSafeHdc(), hOldFont);
	::DeleteObject(hNewFont);

//	if (bRet)
//	{
//		// ����GDI��aplhaֵ
//		CMmxBase Mmx;
//		RECT SetRct = {0, 0, DstDc.GetDcSize().cx, DstDc.GetDcSize().cy};
//		Mmx.BGRA32_CoverAlpha(DstDc.GetBits(), DstDc.GetDcSize(), SetRct, 0, 255);
//	}

	return bRet;
}

// ����ͼƬ�����ػ��־��������ɺ󣬽����´λ��Ƶ�ʱ�����´���ͼƬ����
void IPropertyFontBaseImpl::SetPictureTextRedrawSign()
{
	m_bRecreatePicText = true;
}

// ����һ�����Կ�¡
bool IPropertyFontBaseImpl::Clone(IPropertyBase* pFromPropBase)
{
	if (!IsSameTypePropetry(dynamic_cast<IPropertyBase*>(this), pFromPropBase))
		return false;

	IPropertyFontBaseImpl* pFromProp = dynamic_cast<IPropertyFontBaseImpl*>(pFromPropBase);
	if (pFromProp == NULL)
		return false;

	memcpy(&m_FontProp, &(pFromProp->m_FontProp), sizeof(FONT_PROP));
	return true;
}
