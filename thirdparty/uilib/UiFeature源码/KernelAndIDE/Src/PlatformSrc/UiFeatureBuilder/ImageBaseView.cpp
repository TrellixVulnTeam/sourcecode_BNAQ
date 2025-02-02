// ImageBaseView.cpp : implementation file
//

#include "stdafx.h"
#include "UiFeatureBuilder.h"
#include "ImageBaseView.h"
#include "ImageBasePropEditDlg.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\ICommonFun.h"


// 绘制窗口和被选中的控件的边框的8个方块的宽度
#define FANGKUAI_SIZE							(6)
#define FRAME_SIZE_ADD							(20)

// CImageBaseView dialog

//IMPLEMENT_DYNAMIC(CImageBaseView, CDialogViewBase)

CImageBaseView::CImageBaseView(CWnd* pParent) : CDialogViewBase(pParent),
m_ZipFileImgBase(NULL),
m_DrawFangKuai(NULL)
{
	m_pCurShowImgBase = NULL;
	m_pCurZipFile = NULL;
	m_pUiKernel = NULL;
	memset(&m_FangKuai8, 0, sizeof(FANGKUAI_8));

	m_MouseMovePos.x = m_MouseMovePos.y = 0;
	m_LBtnDownPos.x = m_LBtnDownPos.y = 0;
	m_LBtnUpPos.x = m_LBtnUpPos.y = 0;
	m_bIsLButtonDown = false;

	m_nViewCursor = -1;
	m_nMoveFangKuai8Type = SCT_NONE;
	m_bMoveInCtrlFangKuai8 = false;
	m_bCanMoveSel = false;
	m_pEditDlg = NULL;

	InitPropImageBase(m_ZipFileImgBase.GetImageProp());
}

CImageBaseView::~CImageBaseView()
{
}

void CImageBaseView::DoDataExchange(CDataExchange* pDX)
{
	CDialogViewBase::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CImageBaseView, CDialogViewBase)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()


// CImageBaseView message handlers

void CImageBaseView::SetCurrentShowImage(CImageBasePropEditDlg *pEditDlg, IUiFeatureKernel *pUiKernel, IPropertyImageBase *pImgBase, ZIP_FILE *pZipFile)
{
	if (m_DrawFangKuai.GetUiKernel() == NULL)
	{
		m_DrawFangKuai.SetUiKernel(pUiKernel);
		CStringW strPath = PathHelperW(L"ControlsRes\\BuilderWindowFrame.bmp");

		IMAGE_BASE_PROP ImgBase;
		InitPropImageBase(&ImgBase);

		ImgBase.bIsZipFile = false;
		wcscpy_s(ImgBase.strFileName, MAX_PATH, strPath);
		ImgBase.ImgShowType = IST_ALL_LASHEN;
		ImgBase.RectInImage.left = ImgBase.RectInImage.top = 0;
		ImgBase.RectInImage.right = ImgBase.RectInImage.bottom = FANGKUAI_SIZE;
		INIT_RECT(ImgBase.jggInfo);
		m_DrawFangKuai.SetImageProp(&ImgBase);
	}

	m_pEditDlg = pEditDlg;
	m_pUiKernel = pUiKernel;
	m_ZipFileImgBase.SetUiKernel(m_pUiKernel);

	m_pCurShowImgBase = pImgBase;
	m_pCurZipFile = pZipFile;
	m_ZipFileImgBase.SetZipFile(m_pCurZipFile, true);

	CRect WndRct;
	WndRct.SetRectEmpty();
	this->GetClientRect(&WndRct);
	SetScrollBarSize(WndRct.Width(), WndRct.Height());
	this->RedrawWindow();
}

void CImageBaseView::OnDraw()
{
	if (m_pCurZipFile == NULL)
		return;

	// 先绘制图片
	SIZE sizImg = m_ZipFileImgBase.GetImageSize();

	RECT DstRct;
	INIT_RECT(DstRct);
	DstRct.right = sizImg.cx;
	DstRct.bottom = sizImg.cy;

	m_ZipFileImgBase.DrawImage(m_MemDc, DstRct);

	// 再绘制选择方框
	if (m_pCurShowImgBase == NULL)
		return;

	IMAGE_BASE_PROP* pImgProp = m_pCurShowImgBase->GetImageProp();
	if (pImgProp == NULL)
		return;

	m_FangKuai8.EntityRct = pImgProp->RectInImage;

	m_FangKuai8.LeftTop.left = m_FangKuai8.EntityRct.left - FANGKUAI_SIZE;
	m_FangKuai8.LeftTop.top = m_FangKuai8.EntityRct.top - FANGKUAI_SIZE;
	m_FangKuai8.LeftTop.right = m_FangKuai8.LeftTop.left + FANGKUAI_SIZE;
	m_FangKuai8.LeftTop.bottom = m_FangKuai8.LeftTop.top + FANGKUAI_SIZE;
	m_DrawFangKuai.DrawImage(m_MemDc, m_FangKuai8.LeftTop);

	m_FangKuai8.LeftMid.left = m_FangKuai8.EntityRct.left - FANGKUAI_SIZE;
	m_FangKuai8.LeftMid.top = m_FangKuai8.EntityRct.top + (RECT_HEIGHT(m_FangKuai8.EntityRct) / 2) - (FANGKUAI_SIZE / 2);
	m_FangKuai8.LeftMid.right = m_FangKuai8.LeftMid.left + FANGKUAI_SIZE;
	m_FangKuai8.LeftMid.bottom = m_FangKuai8.LeftMid.top + FANGKUAI_SIZE;
	m_DrawFangKuai.DrawImage(m_MemDc, m_FangKuai8.LeftMid);

	m_FangKuai8.LeftBottom.left = m_FangKuai8.EntityRct.left - FANGKUAI_SIZE;
	m_FangKuai8.LeftBottom.top = m_FangKuai8.EntityRct.bottom;
	m_FangKuai8.LeftBottom.right = m_FangKuai8.LeftBottom.left + FANGKUAI_SIZE;
	m_FangKuai8.LeftBottom.bottom = m_FangKuai8.LeftBottom.top + FANGKUAI_SIZE;
	m_DrawFangKuai.DrawImage(m_MemDc, m_FangKuai8.LeftBottom);

	m_FangKuai8.MidTop.left = m_FangKuai8.EntityRct.left + (RECT_WIDTH(m_FangKuai8.EntityRct) / 2) - (FANGKUAI_SIZE / 2);
	m_FangKuai8.MidTop.top = m_FangKuai8.EntityRct.top - FANGKUAI_SIZE;
	m_FangKuai8.MidTop.right = m_FangKuai8.MidTop.left + FANGKUAI_SIZE;
	m_FangKuai8.MidTop.bottom = m_FangKuai8.MidTop.top + FANGKUAI_SIZE;
	m_DrawFangKuai.DrawImage(m_MemDc, m_FangKuai8.MidTop);

	m_FangKuai8.MidBottom.left = m_FangKuai8.EntityRct.left + (RECT_WIDTH(m_FangKuai8.EntityRct) / 2) - (FANGKUAI_SIZE / 2);
	m_FangKuai8.MidBottom.top = m_FangKuai8.EntityRct.bottom;
	m_FangKuai8.MidBottom.right = m_FangKuai8.MidBottom.left + FANGKUAI_SIZE;
	m_FangKuai8.MidBottom.bottom = m_FangKuai8.MidBottom.top + FANGKUAI_SIZE;
	m_DrawFangKuai.DrawImage(m_MemDc, m_FangKuai8.MidBottom);

	m_FangKuai8.RightTop.left = m_FangKuai8.EntityRct.right;
	m_FangKuai8.RightTop.top = m_FangKuai8.EntityRct.top - FANGKUAI_SIZE;
	m_FangKuai8.RightTop.right = m_FangKuai8.RightTop.left + FANGKUAI_SIZE;
	m_FangKuai8.RightTop.bottom = m_FangKuai8.RightTop.top + FANGKUAI_SIZE;
	m_DrawFangKuai.DrawImage(m_MemDc, m_FangKuai8.RightTop);

	m_FangKuai8.RightMid.left = m_FangKuai8.EntityRct.right;
	m_FangKuai8.RightMid.top = m_FangKuai8.EntityRct.top + (RECT_HEIGHT(m_FangKuai8.EntityRct) / 2) - (FANGKUAI_SIZE / 2);
	m_FangKuai8.RightMid.right = m_FangKuai8.RightMid.left + FANGKUAI_SIZE;
	m_FangKuai8.RightMid.bottom = m_FangKuai8.RightMid.top + FANGKUAI_SIZE;
	m_DrawFangKuai.DrawImage(m_MemDc, m_FangKuai8.RightMid);

	m_FangKuai8.RightBottom.left = m_FangKuai8.EntityRct.right;
	m_FangKuai8.RightBottom.top = m_FangKuai8.EntityRct.bottom;
	m_FangKuai8.RightBottom.right = m_FangKuai8.RightBottom.left + FANGKUAI_SIZE;
	m_FangKuai8.RightBottom.bottom = m_FangKuai8.RightBottom.top + FANGKUAI_SIZE;
	m_DrawFangKuai.DrawImage(m_MemDc, m_FangKuai8.RightBottom);

	Graphics DoGrap(m_MemDc.GetSafeHdc());
	Pen LinePen(Color(254, 0, 0, 255));
	DoGrap.DrawLine(&LinePen, m_FangKuai8.EntityRct.left, m_FangKuai8.EntityRct.top, m_FangKuai8.EntityRct.right, m_FangKuai8.EntityRct.top);
	DoGrap.DrawLine(&LinePen, m_FangKuai8.EntityRct.right, m_FangKuai8.EntityRct.top, m_FangKuai8.EntityRct.right, m_FangKuai8.EntityRct.bottom);
	DoGrap.DrawLine(&LinePen, m_FangKuai8.EntityRct.right, m_FangKuai8.EntityRct.bottom, m_FangKuai8.EntityRct.left, m_FangKuai8.EntityRct.bottom);
	DoGrap.DrawLine(&LinePen, m_FangKuai8.EntityRct.left, m_FangKuai8.EntityRct.bottom, m_FangKuai8.EntityRct.left, m_FangKuai8.EntityRct.top);

	if (pImgProp->ImgShowType == IST_JGG_LASHEN)
	{
		Pen JggLine(Color(254, 255, 0, 0));
		if (pImgProp->jggInfo.left > 0)
			DoGrap.DrawLine(&JggLine, m_FangKuai8.EntityRct.left + pImgProp->jggInfo.left, m_FangKuai8.EntityRct.top,
			m_FangKuai8.EntityRct.left + pImgProp->jggInfo.left, m_FangKuai8.EntityRct.bottom);

		if (pImgProp->jggInfo.right > 0)
			DoGrap.DrawLine(&JggLine, m_FangKuai8.EntityRct.right - pImgProp->jggInfo.right, m_FangKuai8.EntityRct.top,
			m_FangKuai8.EntityRct.right - pImgProp->jggInfo.right, m_FangKuai8.EntityRct.bottom);

		if (pImgProp->jggInfo.top > 0)
			DoGrap.DrawLine(&JggLine, m_FangKuai8.EntityRct.left, m_FangKuai8.EntityRct.top + pImgProp->jggInfo.top,
			m_FangKuai8.EntityRct.right, m_FangKuai8.EntityRct.top + pImgProp->jggInfo.top);

		if (pImgProp->jggInfo.bottom > 0)
			DoGrap.DrawLine(&JggLine, m_FangKuai8.EntityRct.left, m_FangKuai8.EntityRct.bottom - pImgProp->jggInfo.bottom,
			m_FangKuai8.EntityRct.right, m_FangKuai8.EntityRct.bottom - pImgProp->jggInfo.bottom);
	}
}

void CImageBaseView::OnSize_SetViewSize(int cx, int cy)
{
	m_rcViewSize = m_rcDlgSize;
	if (m_pCurZipFile == NULL)
		return;

	SIZE sizImg = m_ZipFileImgBase.GetImageSize();
	if (m_rcViewSize.Width() < sizImg.cx + FRAME_SIZE_ADD)
		m_rcViewSize.right = sizImg.cx + FRAME_SIZE_ADD;

	if (m_rcViewSize.Height() < sizImg.cy + FRAME_SIZE_ADD)
		m_rcViewSize.bottom = sizImg.cy + FRAME_SIZE_ADD;
}

void CImageBaseView::OnLButtonDown(UINT nFlags, CPoint point)
{
	::SetCapture(m_hWnd);
	CDialogViewBase::OnLButtonDown(nFlags, point);
//////////////////////////////////////////////////////////////////////////
	if (m_pCurShowImgBase == NULL)
		return;
	m_LBtnDownPos = point;
	m_bIsLButtonDown = true;

	if (m_bCanMoveSel)
	{
		SetViewCursor(UF_IDC_SIZEALL);
		this->RedrawWindow();
		return;
	}
}

void CImageBaseView::OnLButtonUp(UINT nFlags, CPoint point)
{
	::ReleaseCapture();
	CDialogViewBase::OnLButtonUp(nFlags, point);
//////////////////////////////////////////////////////////////////////////
	m_bCanMoveSel = false;
	m_bIsLButtonDown = false;
	m_bMoveInCtrlFangKuai8 = false;

	if (m_pCurShowImgBase == NULL)
		return;
	m_LBtnUpPos = point;
	SetViewCursor(UF_IDC_ARROW);
}

void CImageBaseView::OnMouseMove(UINT nFlags, CPoint point)
{
	CDialogViewBase::OnMouseMove(nFlags, point);
//////////////////////////////////////////////////////////////////////////
	if (m_pCurShowImgBase == NULL)
		return;
	m_MouseMovePos = point;

	if (m_bIsLButtonDown)
	{
		OnMouseMove_LButtonDown(point);
		this->RedrawWindow();
		return;
	}

	CPoint ptTemp = point;
	ptTemp.x += m_nHScrollPos;
	ptTemp.y += m_nVScrollPos;

	// 可以移动选择区域
	if (PtInRect(&(m_FangKuai8.EntityRct), ptTemp))
	{
		m_bCanMoveSel = true;
		return;
	}
	else
	{
		m_bCanMoveSel = false;
	}

	// 选择拉伸区域
	m_nMoveFangKuai8Type = OnMouseMove_FangKuai8(point, false);
	m_bMoveInCtrlFangKuai8 = (m_nMoveFangKuai8Type != SCT_NONE);
	if (m_bMoveInCtrlFangKuai8)
	{
		this->RedrawWindow();
		return;
	}

	this->RedrawWindow();
	SetViewCursor(UF_IDC_ARROW);
}

SIZE_CTRL_TYPE CImageBaseView::OnMouseMove_FangKuai8(CPoint point, bool bIsWnd)
{
	if (m_pCurShowImgBase == NULL)
		return SCT_NONE;

	point.x += m_nHScrollPos;
	point.y += m_nVScrollPos;

	if (PtInRect(&m_FangKuai8.LeftTop, point))
	{
		SetViewCursor(UF_IDC_SIZENWSE);
		return SCT_LEFT_TOP;
	}
	else if (PtInRect(&m_FangKuai8.LeftMid, point))
	{
		SetViewCursor(UF_IDC_SIZEWE);
		return SCT_LEFT_MID;
	}
	else if (PtInRect(&m_FangKuai8.LeftBottom, point))
	{
		SetViewCursor(UF_IDC_SIZENESW);
		return SCT_LEFT_BOTTOM;
	}
	else if (PtInRect(&m_FangKuai8.MidTop, point))
	{
		SetViewCursor(UF_IDC_SIZENS);
		return SCT_MID_TOP;
	}
	else if (PtInRect(&m_FangKuai8.MidBottom, point))
	{
		SetViewCursor(UF_IDC_SIZENS);
		return SCT_MID_BOTTOM;
	}
	else if (PtInRect(&m_FangKuai8.RightTop, point))
	{
		SetViewCursor(UF_IDC_SIZENESW);
		return SCT_RIGHT_TOP;
	}
	else if (PtInRect(&m_FangKuai8.RightMid, point))
	{
		SetViewCursor(UF_IDC_SIZEWE);
		return SCT_RIGHT_MID;
	}
	else if (PtInRect(&m_FangKuai8.RightBottom, point))
	{
		SetViewCursor(UF_IDC_SIZENWSE);
		return SCT_RIGHT_BOTTOM;
	}

	return SCT_NONE;
}

// 设置光标
void CImageBaseView::SetViewCursor(int nCursor)
{
	::ShowCursor(FALSE);
	m_nViewCursor = nCursor;
	::ShowCursor(TRUE);
	::PostMessage(this->m_hWnd, WM_SETCURSOR, NULL, NULL);
}

BOOL CImageBaseView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (m_nViewCursor != -1)
	{
		HCURSOR hCursor = ::LoadCursor(NULL, MAKEINTRESOURCE(m_nViewCursor));
		if (hCursor != NULL)
		{
			HCURSOR hSetCur = ::SetCursor(hCursor);
			if (hSetCur != NULL)
				return TRUE;
		}
	}

	return CDialogViewBase::OnSetCursor(pWnd, nHitTest, message);
}

void CImageBaseView::OnMouseMove_LButtonDown(CPoint point)
{
	if (m_pCurShowImgBase == NULL)
		return;

	IMAGE_BASE_PROP* pImgProp = m_pCurShowImgBase->GetImageProp();
	if (pImgProp == NULL)
		return;

	SIZE sizImg = m_ZipFileImgBase.GetImageSize();
	if (m_bCanMoveSel)
	{
		SetViewCursor(UF_IDC_SIZEALL);

		RECT &SetRect = pImgProp->RectInImage;
		RECT RectInImage;
		INIT_RECT(RectInImage);
		RectInImage.left = point.x - RECT_WIDTH(SetRect) / 2 + m_nHScrollPos;
		if (RectInImage.left < 0)
			RectInImage.left = 0;
		if ((RectInImage.left + RECT_WIDTH(SetRect)) > sizImg.cx)
			RectInImage.left = sizImg.cx - RECT_WIDTH(SetRect);

		RectInImage.right = RectInImage.left + RECT_WIDTH(SetRect);

		RectInImage.top = point.y - RECT_HEIGHT(SetRect) / 2 + m_nVScrollPos;
		if (RectInImage.top < 0)
			RectInImage.top = 0;
		if ((RectInImage.top + RECT_HEIGHT(SetRect)) > sizImg.cy)
			RectInImage.top = sizImg.cy - RECT_HEIGHT(SetRect);

		RectInImage.bottom = RectInImage.top + RECT_HEIGHT(SetRect);

		SetRect = RectInImage;
	}
	else if (m_bMoveInCtrlFangKuai8)
	{
		OnMouseMove_LButtonDown_SizeCtrl(m_nMoveFangKuai8Type, point);
	}
	else
	{
		SetViewCursor(UF_IDC_ARROW);
	}

	if (m_pEditDlg != NULL)
		m_pEditDlg->RefreshJggPropToMember(pImgProp);
}

void CImageBaseView::OnMouseMove_LButtonDown_SizeCtrl(SIZE_CTRL_TYPE nFangKuai8Type, CPoint point)
{
	if (m_nMoveFangKuai8Type == SCT_NONE || m_pCurShowImgBase == NULL)
		return;

	point.x += m_nHScrollPos;
	point.y += m_nVScrollPos;

	IMAGE_BASE_PROP* pImgProp = m_pCurShowImgBase->GetImageProp();
	if (pImgProp == NULL)
		return;

	SIZE sizImg = m_ZipFileImgBase.GetImageSize();
	RECT &SetRect = pImgProp->RectInImage;

	if (nFangKuai8Type == SCT_LEFT_TOP)
	{
		SetRect.left = point.x;
		SetRect.top = point.y;

		// 越界判断
		if (SetRect.left > SetRect.right)
			SetRect.left = SetRect.right;
		if (SetRect.top > SetRect.bottom)
			SetRect.top = SetRect.bottom;
	}
	else if (nFangKuai8Type == SCT_LEFT_MID)
	{
		SetRect.left = point.x;

		// 越界判断
		if (SetRect.left > SetRect.right)
			SetRect.left = SetRect.right;
	}
	else if (nFangKuai8Type == SCT_LEFT_BOTTOM)
	{
		SetRect.left = point.x;
		SetRect.bottom = point.y;

		// 越界判断
		if (SetRect.left > SetRect.right)
			SetRect.left = SetRect.right;
		if (SetRect.bottom < SetRect.top)
			SetRect.bottom = SetRect.top;
	}
	else if (nFangKuai8Type == SCT_MID_TOP)
	{
		SetRect.top = point.y;

		// 越界判断
		if (SetRect.top > SetRect.bottom)
			SetRect.top = SetRect.bottom;
	}
	else if (nFangKuai8Type == SCT_MID_BOTTOM)
	{
		SetRect.bottom = point.y;

		// 越界判断
		if (SetRect.bottom < SetRect.top)
			SetRect.bottom = SetRect.top;
	}
	else if (nFangKuai8Type == SCT_RIGHT_TOP)
	{
		SetRect.right = point.x;
		SetRect.top = point.y;

		// 越界判断
		if (SetRect.right < SetRect.left)
			SetRect.right = SetRect.left;
		if (SetRect.top > SetRect.bottom)
			SetRect.top = SetRect.bottom;
	}
	else if (nFangKuai8Type == SCT_RIGHT_MID)
	{
		SetRect.right = point.x;

		// 越界判断
		if (SetRect.right < SetRect.left)
			SetRect.right = SetRect.left;
	}
	else if (nFangKuai8Type == SCT_RIGHT_BOTTOM)
	{
		SetRect.right = point.x;
		SetRect.bottom = point.y;

		// 越界判断
		if (SetRect.right < SetRect.left)
			SetRect.right = SetRect.left;
		if (SetRect.bottom < SetRect.top)
			SetRect.bottom = SetRect.top;
	}

	if (SetRect.left < 0)
		SetRect.left = 0;
	if (SetRect.right > sizImg.cx)
		SetRect.right = sizImg.cx;
	if (SetRect.top < 0)
		SetRect.top = 0;
	if (SetRect.bottom > sizImg.cy)
		SetRect.bottom = sizImg.cy;
}

IPropertyImageBase * CImageBaseView::GetCurShowImgBase()
{
	return m_pCurShowImgBase;
}

//void CImageBaseView::SetCurShowImgBase(IPropertyImageBase* pImageBase)
//{
//	m_pCurShowImgBase = pImageBase;
//}
