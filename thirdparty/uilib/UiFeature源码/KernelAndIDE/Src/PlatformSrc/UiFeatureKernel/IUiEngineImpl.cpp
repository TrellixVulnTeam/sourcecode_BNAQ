
#include "StdAfx.h"
#include "IUiEngineImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"


IUiEngineImpl::IUiEngineImpl(void)
{
	m_Blend.BlendOp = AC_SRC_OVER;
	m_Blend.BlendFlags = 0;
	m_Blend.AlphaFormat = AC_SRC_ALPHA;
	m_Blend.SourceConstantAlpha = 255;

	m_hMsimg32Dll = NULL;
	AlphaBlendImpl = NULL;
	TransparentBltImpl = NULL;
	GradientFillImpl = NULL;

	m_hComctl32Dll = NULL;
	DrawShadowTextImpl = NULL;

	LoadImpl();
}

IUiEngineImpl::~IUiEngineImpl(void)
{
	AlphaBlendImpl = NULL;
	TransparentBltImpl = NULL;
	GradientFillImpl = NULL;
	SAFE_FREE_LIBRARY(m_hMsimg32Dll);

	DrawShadowTextImpl = NULL;
	SAFE_FREE_LIBRARY(m_hComctl32Dll);
}

void IUiEngineImpl::LoadImpl()
{
	m_hMsimg32Dll = ::LoadLibraryW(L"msimg32.dll");
	if (m_hMsimg32Dll != NULL)
	{
		AlphaBlendImpl = (PFNALPHABLEND)GetProcAddress(m_hMsimg32Dll, ("AlphaBlend"));
		TransparentBltImpl = (PFNTRANSPARENTBLT)GetProcAddress(m_hMsimg32Dll, ("TransparentBlt"));
		GradientFillImpl = (PFNGRADIENTFILL)GetProcAddress(m_hMsimg32Dll, ("GradientFill"));
	}

	m_hComctl32Dll = ::LoadLibraryW(L"comctl32.dll");
	if (m_hComctl32Dll != NULL)
	{
		DrawShadowTextImpl = (PDRAWSHADOWTEXT)GetProcAddress(m_hComctl32Dll, ("DrawShadowText"));
	}
}

bool IUiEngineImpl::AlphaBlend(CDrawingBoard &DestMemDc, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest,
						CDrawingBoard &SrcMemDc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, BLENDFUNCTION *pBlendFunction)
{
	if (AlphaBlendImpl == NULL || !IS_SAFE_HANDLE(DestMemDc.GetSafeHdc()) || !IS_SAFE_HANDLE(SrcMemDc.GetSafeHdc()))
		return false;

	BLENDFUNCTION Blend;
	if (pBlendFunction != NULL)
		Blend = *pBlendFunction;
	else
		Blend = m_Blend;

	return (AlphaBlendImpl(DestMemDc.GetSafeHdc(), nXOriginDest, nYOriginDest, nWidthDest, nHeightDest,
		SrcMemDc.GetSafeHdc(), nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, Blend) == TRUE);
}

bool IUiEngineImpl::AlphaBlend(CDrawingBoard &DestMemDc, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest,
						CDrawingBoard &SrcMemDc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, int nAlpha)
{
	if (AlphaBlendImpl == NULL || !IS_SAFE_HANDLE(DestMemDc.GetSafeHdc()) || !IS_SAFE_HANDLE(SrcMemDc.GetSafeHdc()))
		return false;

	if (nAlpha < 0)
		nAlpha = 0;

	if (nAlpha > 255)
		nAlpha = 255;

	BLENDFUNCTION Blend = m_Blend;
	Blend.SourceConstantAlpha = nAlpha;

	return (AlphaBlendImpl(DestMemDc.GetSafeHdc(), nXOriginDest, nYOriginDest, nWidthDest, nHeightDest,
		SrcMemDc.GetSafeHdc(), nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, Blend) == TRUE);
}

bool IUiEngineImpl::AlphaBlend(HDC DestMemDc, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest,
							   CDrawingBoard &SrcMemDc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, int nAlpha)
{
	if (AlphaBlendImpl == NULL || !IS_SAFE_HANDLE(DestMemDc) || !IS_SAFE_HANDLE(SrcMemDc.GetSafeHdc()))
		return false;

	if (nAlpha < 0)
		nAlpha = 0;

	if (nAlpha > 255)
		nAlpha = 255;

	BLENDFUNCTION Blend = m_Blend;
	Blend.SourceConstantAlpha = nAlpha;

	return (AlphaBlendImpl(DestMemDc, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest,
		SrcMemDc.GetSafeHdc(), nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, Blend) == TRUE);
}

// ������Ӱ����
int IUiEngineImpl::DrawShadowText(HDC hdc, LPCWSTR pszText, UINT cch, const RECT *pRect, DWORD dwFlags,
						   COLORREF crText, COLORREF crShadow, int ixOffset, int iyOffset)
{
	if (DrawShadowTextImpl == NULL || hdc == NULL || pszText == NULL || wcslen(pszText) <= 0 || pRect == NULL || IS_RECT_EMPTY(*pRect))
		return 0;

	return DrawShadowTextImpl(hdc, pszText, cch, pRect, dwFlags, crText, crShadow, ixOffset, iyOffset);
}

bool IUiEngineImpl::BitBlt(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop)
{
	return (::BitBlt(hdc, x, y, cx, cy, hdcSrc, x1, y1, rop) == TRUE);
}

bool IUiEngineImpl::StretchBlt(HDC hdcDest, int xDest, int yDest, int wDest, int hDest, HDC hdcSrc, int xSrc, int ySrc, int wSrc, int hSrc, DWORD rop)
{
	return (::StretchBlt(hdcDest, xDest, yDest, wDest, hDest, hdcSrc, xSrc, ySrc, wSrc, hSrc, rop) == TRUE);
}
