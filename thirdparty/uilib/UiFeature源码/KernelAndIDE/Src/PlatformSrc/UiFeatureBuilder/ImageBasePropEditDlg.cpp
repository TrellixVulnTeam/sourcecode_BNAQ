// ImageBasePropEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UiFeatureBuilder.h"
#include "ImageBasePropEditDlg.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "ImageAnimationSettingDlg.h"

#define MAX_PIX					(50000)
// CImageBasePropEditDlg dialog

IMPLEMENT_DYNAMIC(CImageBasePropEditDlg, CDialog)

CImageBasePropEditDlg::CImageBasePropEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageBasePropEditDlg::IDD, pParent)
	, m_nShowAreaTop(0)
	, m_nShowAreaLeft(0)
	, m_nShowAreaBottom(0)
	, m_nShowAreaRight(0)
	, m_nJggLeft(0)
	, m_nJggTop(0)
	, m_nJggRight(0)
	, m_nJggBottom(0)
	, m_nSelelShowImgType(0)
{
	m_pImageView = NULL;
	m_pUiKernel = NULL;
	m_pParentImgProp = NULL;
}

CImageBasePropEditDlg::~CImageBasePropEditDlg()
{
	SAFE_DELETE(m_pImageView);
}

void CImageBasePropEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDS_FRAME_1, m_Static_1);
	DDX_Control(pDX, IDS_FRAME_2, m_Static_2);
	DDX_Control(pDX, IDS_FRAME_3, m_Static_3);
	DDX_Control(pDX, IDL_IMAGEBASE_NAME_LIST, m_ImageBaseList);
	DDX_Control(pDX, IDL_LOCAL_IMAGE_LIST, m_LocalImageList);
	DDX_Text(pDX, IDE_SHOW_AREA_TOP, m_nShowAreaTop);
	DDX_Text(pDX, IDE_SHOW_AREA_LEFT, m_nShowAreaLeft);
	DDX_Text(pDX, IDE_SHOW_AREA_BOTTOM, m_nShowAreaBottom);
	DDX_Text(pDX, IDE_SHOW_AREA_RIGHT, m_nShowAreaRight);
	DDX_Text(pDX, IDE_JJG_LEFT, m_nJggLeft);
	DDX_Text(pDX, IDE_JJG_TOP, m_nJggTop);
	DDX_Text(pDX, IDE_JJG_RIGHT, m_nJggRight);
	DDX_Text(pDX, IDE_JJG_BOTTOM, m_nJggBottom);
	DDX_Control(pDX, IDC_XIANSHIBILI_COMBO, m_ShowBiLi_Combo);
	DDX_Radio(pDX, IDR_PINGPU, m_nSelelShowImgType);
	DDX_Control(pDX, IDC_DRAW_MID_AREA_CHECKBOX, m_Jgg_MidDrawCheckBox);
	DDX_Control(pDX, IDC_STATIC_1, m_Staitc_4);
	DDX_Control(pDX, IDS_FRAME_4, m_Static_5);
	DDX_Control(pDX, IDC_NOT_ALPHA_DRAW_CHK, m_NotAlphaDrawChkBtn);
}


BEGIN_MESSAGE_MAP(CImageBasePropEditDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CImageBasePropEditDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDB_NEW_IMAGEBASE, &CImageBasePropEditDlg::OnBnClickedNewImagebase)
	ON_BN_CLICKED(IDB_DELETE_IMAGEBASE, &CImageBasePropEditDlg::OnBnClickedDeleteImagebase)
	ON_BN_CLICKED(IDB_EDIT_IMAGEBASE, &CImageBasePropEditDlg::OnBnClickedEditImagebase)
	ON_BN_CLICKED(IDCANCEL, &CImageBasePropEditDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDB_GET_LOCAL_IMAGE, &CImageBasePropEditDlg::OnBnClickedGetLocalImage)
	ON_BN_CLICKED(IDB_DELETE_LOCAL_IMAGE, &CImageBasePropEditDlg::OnBnClickedDeleteLocalImage)
	ON_BN_CLICKED(IDR_PINGPU, &CImageBasePropEditDlg::OnBnClickedPingpu)
	ON_BN_CLICKED(IDR_QUANLASHEN, &CImageBasePropEditDlg::OnBnClickedQuanlashen)
	ON_BN_CLICKED(IDR_JJG, &CImageBasePropEditDlg::OnBnClickedJjg)
	ON_NOTIFY(UDN_DELTAPOS, IDS_SHOW_AREA_LEFT, &CImageBasePropEditDlg::OnDeltaposShowAreaLeft)
	ON_NOTIFY(UDN_DELTAPOS, IDS_SHOW_AREA_TOP, &CImageBasePropEditDlg::OnDeltaposShowAreaTop)
	ON_NOTIFY(UDN_DELTAPOS, IDS_SHOW_AREA_RIGHT, &CImageBasePropEditDlg::OnDeltaposShowAreaRight)
	ON_NOTIFY(UDN_DELTAPOS, IDS_SHOW_AREA_BOTTOM, &CImageBasePropEditDlg::OnDeltaposShowAreaBottom)
	ON_NOTIFY(UDN_DELTAPOS, IDS_JJG_LEFT, &CImageBasePropEditDlg::OnDeltaposJjgLeft)
	ON_NOTIFY(UDN_DELTAPOS, IDS_JJG_TOP, &CImageBasePropEditDlg::OnDeltaposJjgTop)
	ON_NOTIFY(UDN_DELTAPOS, IDS_JJG_BOTTOM, &CImageBasePropEditDlg::OnDeltaposJjgBottom)
	ON_NOTIFY(UDN_DELTAPOS, IDS_JJG_RIGHT, &CImageBasePropEditDlg::OnDeltaposJjgRight)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDB_ANMATION_IMAGE_SETTING, &CImageBasePropEditDlg::OnBnClickedAnmationImageSetting)
	ON_BN_CLICKED(IDB_TIHUAN_LOCAL_IMAGE, &CImageBasePropEditDlg::OnBnClickedTihuanLocalImage)
	ON_EN_KILLFOCUS(IDE_SHOW_AREA_TOP, &CImageBasePropEditDlg::OnEnKillfocusShowAreaTop)
	ON_EN_KILLFOCUS(IDE_SHOW_AREA_LEFT, &CImageBasePropEditDlg::OnEnKillfocusShowAreaLeft)
	ON_EN_KILLFOCUS(IDE_SHOW_AREA_BOTTOM, &CImageBasePropEditDlg::OnEnKillfocusShowAreaBottom)
	ON_EN_KILLFOCUS(IDE_SHOW_AREA_RIGHT, &CImageBasePropEditDlg::OnEnKillfocusShowAreaRight)
	ON_EN_KILLFOCUS(IDE_JJG_LEFT, &CImageBasePropEditDlg::OnEnKillfocusJjgLeft)
	ON_EN_KILLFOCUS(IDE_JJG_TOP, &CImageBasePropEditDlg::OnEnKillfocusJjgTop)
	ON_EN_KILLFOCUS(IDE_JJG_BOTTOM, &CImageBasePropEditDlg::OnEnKillfocusJjgBottom)
	ON_EN_KILLFOCUS(IDE_JJG_RIGHT, &CImageBasePropEditDlg::OnEnKillfocusJjgRight)
	ON_BN_CLICKED(IDC_DRAW_MID_AREA_CHECKBOX, &CImageBasePropEditDlg::OnBnClickedDrawMidAreaCheckbox)
	ON_BN_CLICKED(IDC_NOT_ALPHA_DRAW_CHK, &CImageBasePropEditDlg::OnBnClickedNotAlphaDrawChk)
END_MESSAGE_MAP()


// CImageBasePropEditDlg message handlers

void CImageBasePropEditDlg::SetChildPos()
{
	if (!::IsWindow(m_hWnd))
		return;

	CRect WndRct;
	this->GetClientRect(&WndRct);

	CRect CtrlRct(0, 0, 0, 0);
	if (::IsWindow(m_Static_1.m_hWnd))
	{
		CtrlRct.SetRectEmpty();
		CtrlRct.left = 11;
		CtrlRct.right = CtrlRct.left + 218;
		CtrlRct.top = 11;
		CtrlRct.bottom = WndRct.bottom - 11;
		m_Static_1.MoveWindow(&CtrlRct);
	}

	if (::IsWindow(m_ImageBaseList.m_hWnd))
	{
		CtrlRct.SetRectEmpty();
		CtrlRct.left = 20;
		CtrlRct.right = CtrlRct.left + 200;
		CtrlRct.top = 70;
		CtrlRct.bottom = WndRct.bottom - 20;
		m_ImageBaseList.MoveWindow(&CtrlRct);
	}

	if (::IsWindow(m_Static_2.m_hWnd))
	{
		CtrlRct.SetRectEmpty();
		CtrlRct.left = 240;
		CtrlRct.right = WndRct.right - 11;
		CtrlRct.top = 11;
		CtrlRct.bottom = WndRct.bottom - 11;
		m_Static_2.MoveWindow(&CtrlRct);
	}

	if (::IsWindow(m_Static_3.m_hWnd))
	{
		CtrlRct.SetRectEmpty();
		CtrlRct.left = 249;
		CtrlRct.right = CtrlRct.left + 191;
		CtrlRct.top = 308;
		CtrlRct.bottom = WndRct.bottom - 20;
		m_Static_3.MoveWindow(&CtrlRct);
	}

	if (::IsWindow(m_LocalImageList.m_hWnd))
	{
		CtrlRct.SetRectEmpty();
		CtrlRct.left = 256;
		CtrlRct.right = CtrlRct.left + 179;
		CtrlRct.top = 359;
		CtrlRct.bottom = WndRct.bottom - 30;
		m_LocalImageList.MoveWindow(&CtrlRct);
	}

	if (::IsWindow(m_Staitc_4.m_hWnd))
	{
		CtrlRct.SetRectEmpty();
		CtrlRct.right = WndRct.right;
		CtrlRct.left = CtrlRct.right - 235;
		CtrlRct.top = 0;
		CtrlRct.bottom = CtrlRct.top + 15;
		m_Staitc_4.MoveWindow(&CtrlRct);
	}

	if (m_pImageView != NULL && ::IsWindow(m_pImageView->m_hWnd))
	{
		CtrlRct.SetRectEmpty();
		CtrlRct.left = 450;
		CtrlRct.right = WndRct.right - 20;
		CtrlRct.top = 115;
		CtrlRct.bottom = WndRct.bottom - 18;
		m_pImageView->MoveWindow(&CtrlRct);
	}

	if (::IsWindow(m_Static_5.m_hWnd))
	{
		CtrlRct.SetRectEmpty();
		CtrlRct.left = 450;
		CtrlRct.right = WndRct.right - 22;
		CtrlRct.top = 20;
		CtrlRct.bottom = CtrlRct.top + 50;
		m_Static_5.MoveWindow(&CtrlRct);
	}
}

BOOL CImageBasePropEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_pImageView = new CImageBaseView(this);
	if (m_pImageView != NULL)
	{
		CRect ViewRct(0, 0, 0, 0);
		m_pImageView->MoveWindow(ViewRct);
		m_pImageView->ShowWindow(SW_SHOW);
	}
	SetChildPos();

	SetImageEditEnableStyle(false);

	((CSpinButtonCtrl*)this->GetDlgItem(IDS_SHOW_AREA_LEFT))->SetRange32(0, 0);
	((CSpinButtonCtrl*)this->GetDlgItem(IDS_SHOW_AREA_TOP))->SetRange32(0, 0);
	((CSpinButtonCtrl*)this->GetDlgItem(IDS_SHOW_AREA_RIGHT))->SetRange32(0, MAX_PIX);
	((CSpinButtonCtrl*)this->GetDlgItem(IDS_SHOW_AREA_BOTTOM))->SetRange32(0, MAX_PIX);
	((CSpinButtonCtrl*)this->GetDlgItem(IDS_JJG_LEFT))->SetRange32(0, MAX_PIX);
	((CSpinButtonCtrl*)this->GetDlgItem(IDS_JJG_TOP))->SetRange32(0, MAX_PIX);
	((CSpinButtonCtrl*)this->GetDlgItem(IDS_JJG_RIGHT))->SetRange32(0, MAX_PIX);
	((CSpinButtonCtrl*)this->GetDlgItem(IDS_JJG_BOTTOM))->SetRange32(0, MAX_PIX);

	m_ShowBiLi_Combo.InsertString(0, _T("100%"));
	m_ShowBiLi_Combo.InsertString(1, _T("200%"));
	m_ShowBiLi_Combo.InsertString(2, _T("400%"));
	m_ShowBiLi_Combo.InsertString(3, _T("600%"));
	m_ShowBiLi_Combo.InsertString(4, _T("800%"));
	m_ShowBiLi_Combo.InsertString(5, _T("1000%"));
	m_ShowBiLi_Combo.SetCurSel(0);

	m_Jgg_MidDrawCheckBox.SetCheck(0);

	m_ImageBaseList.Init(m_pUiKernel, this, &m_LocalImageList, m_pParentImgProp);
	m_LocalImageList.Init(m_pUiKernel, this, &m_ImageBaseList, m_pImageView);

	m_ImageBaseList.SetFocus();
	this->UpdateData(FALSE);
	return TRUE;
}

void CImageBasePropEditDlg::RefreshImageBaseView()
{
	if (m_pImageView != NULL)
		m_pImageView->RedrawWindow();
}

void CImageBasePropEditDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	SetChildPos();
}

void CImageBasePropEditDlg::OnBnClickedCancel()
{
	OnBnClickedOk();
}

void CImageBasePropEditDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	CDialog::OnGetMinMaxInfo(lpMMI);

	if (lpMMI != NULL)
	{
		lpMMI->ptMinTrackSize.x = 966;
		lpMMI->ptMinTrackSize.y = 666;
	}
}

void CImageBasePropEditDlg::SetNewDeltaposValue(int nPos, int &nSetValue, LONG &nPropValue)
{
	nSetValue = nPos;

	if (nSetValue < 0)
		nSetValue = 0;

	nPropValue = (LONG)nSetValue;
	RefreshImageBaseView();
}

void CImageBasePropEditDlg::ResetDeltaposRange()
{
	if (!::IsWindow(m_hWnd))
		return;

	((CSpinButtonCtrl*)this->GetDlgItem(IDS_SHOW_AREA_LEFT))->SetRange32(0, m_nShowAreaRight);
	((CSpinButtonCtrl*)this->GetDlgItem(IDS_SHOW_AREA_LEFT))->RedrawWindow();

	((CSpinButtonCtrl*)this->GetDlgItem(IDS_SHOW_AREA_RIGHT))->SetRange32(m_nShowAreaLeft, MAX_PIX);
	((CSpinButtonCtrl*)this->GetDlgItem(IDS_SHOW_AREA_RIGHT))->RedrawWindow();

	((CSpinButtonCtrl*)this->GetDlgItem(IDS_SHOW_AREA_TOP))->SetRange32(0, m_nShowAreaBottom);
	((CSpinButtonCtrl*)this->GetDlgItem(IDS_SHOW_AREA_TOP))->RedrawWindow();

	((CSpinButtonCtrl*)this->GetDlgItem(IDS_SHOW_AREA_BOTTOM))->SetRange32(m_nShowAreaTop, MAX_PIX);
	((CSpinButtonCtrl*)this->GetDlgItem(IDS_SHOW_AREA_BOTTOM))->RedrawWindow();

	((CSpinButtonCtrl*)this->GetDlgItem(IDS_JJG_RIGHT))->SetRange32(0, (m_nShowAreaRight - m_nShowAreaLeft) / 2 + 1);
	((CSpinButtonCtrl*)this->GetDlgItem(IDS_JJG_RIGHT))->RedrawWindow();

	((CSpinButtonCtrl*)this->GetDlgItem(IDS_JJG_LEFT))->SetRange32(0, (m_nShowAreaRight - m_nShowAreaLeft) / 2 + 1);
	((CSpinButtonCtrl*)this->GetDlgItem(IDS_JJG_LEFT))->RedrawWindow();

	((CSpinButtonCtrl*)this->GetDlgItem(IDS_JJG_BOTTOM))->SetRange32(0, (m_nShowAreaBottom - m_nShowAreaTop) / 2 + 1);
	((CSpinButtonCtrl*)this->GetDlgItem(IDS_JJG_BOTTOM))->RedrawWindow();

	((CSpinButtonCtrl*)this->GetDlgItem(IDS_JJG_TOP))->SetRange32(0, (m_nShowAreaBottom - m_nShowAreaTop) / 2 + 1);
	((CSpinButtonCtrl*)this->GetDlgItem(IDS_JJG_TOP))->RedrawWindow();
}

void CImageBasePropEditDlg::OnDeltaposShowAreaLeft(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	*pResult = 0;
	if (pNMUpDown == NULL || m_ImageBaseList.m_pSelectImgBaseProp == NULL || m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp() == NULL)
		return;

	pNMUpDown->iPos += pNMUpDown->iDelta;
	IMAGE_BASE_PROP* pSelImgProp = m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp();
	SetNewDeltaposValue(pNMUpDown->iPos, m_nShowAreaLeft, pSelImgProp->RectInImage.left);
	ResetDeltaposRange();
}

void CImageBasePropEditDlg::OnDeltaposShowAreaRight(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	*pResult = 0;
	if (pNMUpDown == NULL || m_ImageBaseList.m_pSelectImgBaseProp == NULL || m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp() == NULL)
		return;

	pNMUpDown->iPos += pNMUpDown->iDelta;
	IMAGE_BASE_PROP* pSelImgProp = m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp();
	SetNewDeltaposValue(pNMUpDown->iPos, m_nShowAreaRight, pSelImgProp->RectInImage.right);
	ResetDeltaposRange();
}

void CImageBasePropEditDlg::OnDeltaposShowAreaTop(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	*pResult = 0;
	if (pNMUpDown == NULL || m_ImageBaseList.m_pSelectImgBaseProp == NULL || m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp() == NULL)
		return;

	pNMUpDown->iPos += pNMUpDown->iDelta;
	IMAGE_BASE_PROP* pSelImgProp = m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp();
	SetNewDeltaposValue(pNMUpDown->iPos, m_nShowAreaTop, pSelImgProp->RectInImage.top);
	ResetDeltaposRange();
}

void CImageBasePropEditDlg::OnDeltaposShowAreaBottom(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	*pResult = 0;
	if (pNMUpDown == NULL || m_ImageBaseList.m_pSelectImgBaseProp == NULL || m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp() == NULL)
		return;

	pNMUpDown->iPos += pNMUpDown->iDelta;
	IMAGE_BASE_PROP* pSelImgProp = m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp();
	SetNewDeltaposValue(pNMUpDown->iPos, m_nShowAreaBottom, pSelImgProp->RectInImage.bottom);
	ResetDeltaposRange();
}

void CImageBasePropEditDlg::OnDeltaposJjgLeft(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	*pResult = 0;
	if (pNMUpDown == NULL || m_ImageBaseList.m_pSelectImgBaseProp == NULL || m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp() == NULL)
		return;

	IMAGE_BASE_PROP* pSelImgProp = m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp();
	SetNewDeltaposValue(pNMUpDown->iPos, m_nJggLeft, pSelImgProp->jggInfo.left);
}

void CImageBasePropEditDlg::OnDeltaposJjgTop(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	*pResult = 0;
	if (pNMUpDown == NULL || m_ImageBaseList.m_pSelectImgBaseProp == NULL || m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp() == NULL)
		return;

	IMAGE_BASE_PROP* pSelImgProp = m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp();
	SetNewDeltaposValue(pNMUpDown->iPos, m_nJggTop, pSelImgProp->jggInfo.top);
}

void CImageBasePropEditDlg::OnDeltaposJjgBottom(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	*pResult = 0;
	if (pNMUpDown == NULL || m_ImageBaseList.m_pSelectImgBaseProp == NULL || m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp() == NULL)
		return;

	IMAGE_BASE_PROP* pSelImgProp = m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp();
	SetNewDeltaposValue(pNMUpDown->iPos, m_nJggBottom, pSelImgProp->jggInfo.bottom);
}

void CImageBasePropEditDlg::OnDeltaposJjgRight(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	*pResult = 0;
	if (pNMUpDown == NULL || m_ImageBaseList.m_pSelectImgBaseProp == NULL || m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp() == NULL)
		return;

	IMAGE_BASE_PROP* pSelImgProp = m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp();
	SetNewDeltaposValue(pNMUpDown->iPos, m_nJggRight, pSelImgProp->jggInfo.right);
}

void CImageBasePropEditDlg::OnBnClickedPingpu()
{
	this->UpdateData(TRUE);
	SetJggEditCtrlStyle(FALSE);

	if (m_ImageBaseList.m_pSelectImgBaseProp != NULL && m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp() != NULL)
		m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp()->ImgShowType = (IMAGE_SHOW_TYPE)m_nSelelShowImgType;

	RefreshImageBaseView();
}

void CImageBasePropEditDlg::OnBnClickedQuanlashen()
{
	this->UpdateData(TRUE);
	SetJggEditCtrlStyle(FALSE);

	if (m_ImageBaseList.m_pSelectImgBaseProp != NULL && m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp() != NULL)
		m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp()->ImgShowType = (IMAGE_SHOW_TYPE)m_nSelelShowImgType;

	RefreshImageBaseView();
}

void CImageBasePropEditDlg::OnBnClickedJjg()
{
	this->UpdateData(TRUE);
	SetJggEditCtrlStyle(TRUE);

	if (m_ImageBaseList.m_pSelectImgBaseProp != NULL && m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp() != NULL)
		m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp()->ImgShowType = (IMAGE_SHOW_TYPE)m_nSelelShowImgType;

	RefreshImageBaseView();
}

void CImageBasePropEditDlg::SetJggEditCtrlStyle(bool bEnable)
{
	if (!::IsWindow(m_hWnd))
		return;

	this->GetDlgItem(IDC_DRAW_MID_AREA_CHECKBOX)->EnableWindow(bEnable);
	this->GetDlgItem(IDE_JJG_LEFT)->EnableWindow(bEnable);
	this->GetDlgItem(IDS_JJG_LEFT)->EnableWindow(bEnable);
	this->GetDlgItem(IDE_JJG_TOP)->EnableWindow(bEnable);
	this->GetDlgItem(IDS_JJG_TOP)->EnableWindow(bEnable);
	this->GetDlgItem(IDE_JJG_RIGHT)->EnableWindow(bEnable);
	this->GetDlgItem(IDS_JJG_RIGHT)->EnableWindow(bEnable);
	this->GetDlgItem(IDE_JJG_BOTTOM)->EnableWindow(bEnable);
	this->GetDlgItem(IDS_JJG_BOTTOM)->EnableWindow(bEnable);
}

void CImageBasePropEditDlg::SetImageEditEnableStyle(bool bEnable)
{
	if (bEnable)
	{
		// 九宫格状态
		SetJggEditCtrlStyle(m_nSelelShowImgType == IST_JGG_LASHEN);
	}
	else
	{
		// 九宫格状态
		SetJggEditCtrlStyle(false);
	}

	this->GetDlgItem(IDB_EDIT_IMAGEBASE)->EnableWindow(bEnable);
	this->GetDlgItem(IDE_SHOW_AREA_LEFT)->EnableWindow(bEnable);
	this->GetDlgItem(IDS_SHOW_AREA_LEFT)->EnableWindow(bEnable);
	this->GetDlgItem(IDE_SHOW_AREA_TOP)->EnableWindow(bEnable);
	this->GetDlgItem(IDS_SHOW_AREA_TOP)->EnableWindow(bEnable);
	this->GetDlgItem(IDE_SHOW_AREA_RIGHT)->EnableWindow(bEnable);
	this->GetDlgItem(IDS_SHOW_AREA_RIGHT)->EnableWindow(bEnable);
	this->GetDlgItem(IDE_SHOW_AREA_BOTTOM)->EnableWindow(bEnable);
	this->GetDlgItem(IDS_SHOW_AREA_BOTTOM)->EnableWindow(bEnable);
	this->GetDlgItem(IDR_PINGPU)->EnableWindow(bEnable);
	this->GetDlgItem(IDR_QUANLASHEN)->EnableWindow(bEnable);
	this->GetDlgItem(IDR_JJG)->EnableWindow(bEnable);
	this->GetDlgItem(IDB_TIHUAN_LOCAL_IMAGE)->EnableWindow(bEnable);
	this->GetDlgItem(IDB_ANMATION_IMAGE_SETTING)->EnableWindow(bEnable);
	this->GetDlgItem(IDB_IMAGE_EFFECT)->EnableWindow(bEnable);

	// 动画图片的时候，设置相关的显示
	if (m_pParentImgProp != NULL && m_pParentImgProp->GetImageBaseProp() != NULL)
	{
		IMAGE_BASE_PROP *pImgProp = m_pParentImgProp->GetImageBaseProp()->GetImageProp();
		if (pImgProp != NULL)
		{
			if (pImgProp->ImgPlayType == IPT_GIF || pImgProp->ImgPlayType == IPT_IMAGE_XULIE)
			{
				this->GetDlgItem(IDR_PINGPU)->EnableWindow(FALSE);
				this->GetDlgItem(IDR_JJG)->EnableWindow(FALSE);
				this->GetDlgItem(IDC_DRAW_MID_AREA_CHECKBOX)->EnableWindow(FALSE);
				this->GetDlgItem(IDE_JJG_LEFT)->EnableWindow(FALSE);
				this->GetDlgItem(IDS_JJG_LEFT)->EnableWindow(FALSE);
				this->GetDlgItem(IDE_JJG_TOP)->EnableWindow(FALSE);
				this->GetDlgItem(IDS_JJG_TOP)->EnableWindow(FALSE);
				this->GetDlgItem(IDE_JJG_RIGHT)->EnableWindow(FALSE);
				this->GetDlgItem(IDS_JJG_RIGHT)->EnableWindow(FALSE);
				this->GetDlgItem(IDE_JJG_BOTTOM)->EnableWindow(FALSE);
				this->GetDlgItem(IDS_JJG_BOTTOM)->EnableWindow(FALSE);
				m_nSelelShowImgType = 1;
				this->UpdateData(FALSE);
				pImgProp->ImgShowType = IST_ALL_LASHEN;
			}
		}
	}
}

void CImageBasePropEditDlg::OnBnClickedOk()
{
	if (m_pParentImgProp == NULL)
	{
		OnOK();
		return;
	}

	int nSelItem = -1;
	IPropertyImageBase* pImgBase = GetSelectImageBase(nSelItem);
	if (pImgBase == NULL)
	{
		OnOK();
		return;
	}

	IPropertyImageBase* pOldImgBase = m_pParentImgProp->GetImageBaseProp();
	if (pOldImgBase != NULL)
	{
		// 当前使用计数器-1
		pOldImgBase->SetActivePropetry(false);
	}

	// 当前使用计数器+1
	pImgBase->SetActivePropetry(true);
	m_pParentImgProp->SetImageBaseProp(pImgBase);
	m_pParentImgProp->SetRelevancyPropName((WCHAR*)pImgBase->GetObjectName());

	OnOK();
}

void CImageBasePropEditDlg::InitImageBaseShow(IUiFeatureKernel* pUiKernel, IPropertyImage* pParentImgProp)
{
	m_pUiKernel = pUiKernel;
	m_pParentImgProp = pParentImgProp;
}

IPropertyImageBase* CImageBasePropEditDlg::GetSelectImageBase(int &nSeleItem)
{
	return m_ImageBaseList.GetSelectImageBase(nSeleItem);
}

void CImageBasePropEditDlg::OnBnClickedNewImagebase()
{
	m_ModifyImgDlg.SetWindowInfomation(_T("新建图片属性名称"));
	if (m_ModifyImgDlg.DoModal() != IDOK)
		return;

	CString strName;
	m_ModifyImgDlg.GetPropBaseName(strName);
	if (strName.GetLength() <= 0 || FindNameInImageBaseNameList(strName))
		return;

	if (!m_ImageBaseList.OnCreateImageBaseProp(strName))
	{
		AfxMessageBox(_T("创建图片属性失败！"), MB_OK | MB_ICONERROR);
		return;
	}
}

bool CImageBasePropEditDlg::FindNameInImageBaseNameList(CString &strName)
{
	for (int i = 1; i < m_ImageBaseList.GetItemCount(); i++)
	{
		CString strComName = m_ImageBaseList.GetItemText(i, 1);
		if (strComName.CompareNoCase(strName) == 0)
		{
			m_ImageBaseList.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
			CString strInfo(_T(""));
			strInfo.Format(_T("已经存在名为【%s】的图片属性！"), strComName);
			AfxMessageBox(strInfo, MB_OK | MB_ICONERROR);
			return true;
		}
	}

	return false;
}

void CImageBasePropEditDlg::OnBnClickedEditImagebase()
{
	int nSelItem = -1;
	IPropertyImageBase* pImgBase = m_ImageBaseList.GetSelectImageBase(nSelItem);
	if (pImgBase == NULL)
	{
		AfxMessageBox(_T("请选择需要编辑的图片属性！"), MB_OK | MB_ICONERROR);
		return;
	}

	m_ModifyImgDlg.SetWindowInfomation(_T("修改图片属性名称"));
	if (m_ModifyImgDlg.DoModal() != IDOK)
		return;

	CString strName;
	m_ModifyImgDlg.GetPropBaseName(strName);
	if (strName.GetLength() <= 0 || FindNameInImageBaseNameList(strName))
		return;

	m_ImageBaseList.OnModifyImageBaseProp(strName);
}

void CImageBasePropEditDlg::OnBnClickedDeleteImagebase()
{
	if (AfxMessageBox(_T("确定要删除选择的图片属性吗？"), MB_OKCANCEL | MB_ICONWARNING) != IDOK)
		return;

	m_ImageBaseList.OnDeleteImageBaseProp();
}

void CImageBasePropEditDlg::OnBnClickedGetLocalImage()
{
	// 打开图片文件
	CFileDialog ImageFileSelDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ENABLESIZING,
		_T("图片 Files (*.bmp;*.jpg;*.jpeg;*.gif;*.png)|*.bmp;*.jpg;*.jpeg;*.gif;*.png;)||"), NULL);
	ImageFileSelDlg.DoModal();

	CString strFilePath = ImageFileSelDlg.GetPathName();
	CString strFileName = ImageFileSelDlg.GetFileTitle();
	strFileName += _T(".");
	strFileName += ImageFileSelDlg.GetFileExt();

	if (strFilePath.GetLength() <= 0 || strFileName.GetLength() <= 0)
		return;

	for (int i = 0; i < m_LocalImageList.GetItemCount(); i++)
	{
		CString strComName = m_LocalImageList.GetItemText(i, 1);
		if (strComName.CompareNoCase(strFileName) == 0)
		{
			m_LocalImageList.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
			CString strInfo(_T(""));
			strInfo.Format(_T("已经存在名为【%s】的图片！"), strFileName);
			AfxMessageBox(strInfo, MB_OK | MB_ICONERROR);
			return;
		}
	}

	m_LocalImageList.OnLoadLocalImage(strFilePath, strFileName);
}

void CImageBasePropEditDlg::OnEnKillfocusShowAreaTop()
{
	this->UpdateData(TRUE);

	if (m_ImageBaseList.m_pSelectImgBaseProp == NULL || m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp() == NULL)
		return;

	if (m_nShowAreaTop < 0)
		m_nShowAreaTop = 0;
	if (m_nShowAreaTop > m_nShowAreaBottom)
		m_nShowAreaTop = m_nShowAreaBottom;
	this->UpdateData(FALSE);

	IMAGE_BASE_PROP* pSelImgProp = m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp();
	pSelImgProp->RectInImage.top = m_nShowAreaTop;

	RefreshImageBaseView();
	ResetDeltaposRange();
}

void CImageBasePropEditDlg::OnEnKillfocusShowAreaLeft()
{
	this->UpdateData(TRUE);

	if (m_ImageBaseList.m_pSelectImgBaseProp == NULL || m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp() == NULL)
		return;

	if (m_nShowAreaLeft < 0)
		m_nShowAreaLeft = 0;
	if (m_nShowAreaLeft > m_nShowAreaRight)
		m_nShowAreaLeft = m_nShowAreaRight;
	this->UpdateData(FALSE);

	IMAGE_BASE_PROP* pSelImgProp = m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp();
	pSelImgProp->RectInImage.left = m_nShowAreaLeft;

	RefreshImageBaseView();
	ResetDeltaposRange();
}

void CImageBasePropEditDlg::OnEnKillfocusShowAreaBottom()
{
	this->UpdateData(TRUE);

	if (m_ImageBaseList.m_pSelectImgBaseProp == NULL || m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp() == NULL)
		return;

	if (m_nShowAreaBottom < 0)
		m_nShowAreaBottom = 0;
	if (m_nShowAreaBottom < m_nShowAreaTop)
		m_nShowAreaBottom = m_nShowAreaTop;
	this->UpdateData(FALSE);

	IMAGE_BASE_PROP* pSelImgProp = m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp();
	pSelImgProp->RectInImage.bottom = m_nShowAreaBottom;

	RefreshImageBaseView();
	ResetDeltaposRange();
}

void CImageBasePropEditDlg::OnEnKillfocusShowAreaRight()
{
	this->UpdateData(TRUE);

	if (m_ImageBaseList.m_pSelectImgBaseProp == NULL || m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp() == NULL)
		return;

	if (m_nShowAreaRight < 0)
		m_nShowAreaRight = 0;
	if (m_nShowAreaRight < m_nShowAreaLeft)
		m_nShowAreaRight = m_nShowAreaLeft;
	this->UpdateData(FALSE);

	IMAGE_BASE_PROP* pSelImgProp = m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp();
	pSelImgProp->RectInImage.right = m_nShowAreaRight;

	RefreshImageBaseView();
	ResetDeltaposRange();
}

void CImageBasePropEditDlg::OnEnKillfocusJjgLeft()
{
	this->UpdateData(TRUE);

	if (m_ImageBaseList.m_pSelectImgBaseProp == NULL || m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp() == NULL)
		return;

	if (m_nJggLeft < 0)
		m_nJggLeft = 0;
	if (m_nJggLeft > ((m_nShowAreaRight - m_nShowAreaLeft) / 2 + 1))
		m_nJggLeft = ((m_nShowAreaRight - m_nShowAreaLeft) / 2 + 1);
	this->UpdateData(FALSE);

	IMAGE_BASE_PROP* pSelImgProp = m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp();
	pSelImgProp->jggInfo.left = m_nJggLeft;

	RefreshImageBaseView();
}

void CImageBasePropEditDlg::OnEnKillfocusJjgRight()
{
	this->UpdateData(TRUE);

	if (m_ImageBaseList.m_pSelectImgBaseProp == NULL || m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp() == NULL)
		return;

	if (m_nJggRight < 0)
		m_nJggRight = 0;
	if (m_nJggRight > ((m_nShowAreaRight - m_nShowAreaLeft) / 2 + 1))
		m_nJggRight = ((m_nShowAreaRight - m_nShowAreaLeft) / 2 + 1);
	this->UpdateData(FALSE);


	IMAGE_BASE_PROP* pSelImgProp = m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp();
	pSelImgProp->jggInfo.right = m_nJggRight;

	RefreshImageBaseView();
}

void CImageBasePropEditDlg::OnEnKillfocusJjgTop()
{
	this->UpdateData(TRUE);

	if (m_ImageBaseList.m_pSelectImgBaseProp == NULL || m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp() == NULL)
		return;

	if (m_nJggTop < 0)
		m_nJggTop = 0;
	if (m_nJggTop > ((m_nShowAreaBottom - m_nShowAreaTop) / 2 + 1))
		m_nJggTop = ((m_nShowAreaBottom - m_nShowAreaTop) / 2 + 1);
	this->UpdateData(FALSE);

	IMAGE_BASE_PROP* pSelImgProp = m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp();
	pSelImgProp->jggInfo.top = m_nJggTop;

	RefreshImageBaseView();
}

void CImageBasePropEditDlg::OnEnKillfocusJjgBottom()
{
	this->UpdateData(TRUE);

	if (m_ImageBaseList.m_pSelectImgBaseProp == NULL || m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp() == NULL)
		return;

	if (m_nJggBottom < 0)
		m_nJggBottom = 0;
	if (m_nJggBottom > ((m_nShowAreaBottom - m_nShowAreaTop) / 2 + 1))
		m_nJggBottom = ((m_nShowAreaBottom - m_nShowAreaTop) / 2 + 1);
	this->UpdateData(FALSE);

	IMAGE_BASE_PROP* pSelImgProp = m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp();
	pSelImgProp->jggInfo.bottom = m_nJggBottom;

	RefreshImageBaseView();
}

void CImageBasePropEditDlg::RefreshJggPropToMember(IMAGE_BASE_PROP* pImgProp)
{
	if (pImgProp == NULL)
		return;

	m_nShowAreaLeft = pImgProp->RectInImage.left;
	m_nShowAreaTop = pImgProp->RectInImage.top;
	m_nShowAreaBottom = pImgProp->RectInImage.bottom;
	m_nShowAreaRight = pImgProp->RectInImage.right;
	m_nJggLeft = pImgProp->jggInfo.left;
	m_nJggTop = pImgProp->jggInfo.top;
	m_nJggRight = pImgProp->jggInfo.right;
	m_nJggBottom = pImgProp->jggInfo.bottom;
	m_Jgg_MidDrawCheckBox.SetCheck(pImgProp->bIsDrawJggMid ? 1 : 0);

	this->UpdateData(FALSE);
}

void CImageBasePropEditDlg::OnBnClickedAnmationImageSetting()
{
	if (m_pParentImgProp == NULL || m_pParentImgProp->GetImageBaseProp() == NULL)
		return;

	CImageAnimationSettingDlg ImgAnimationDlg;
	ImgAnimationDlg.SetImageBase(m_pParentImgProp->GetImageBaseProp());
	ImgAnimationDlg.DoModal();
	SetImageEditEnableStyle(true);
}

// 响应“替换图片”
void CImageBasePropEditDlg::OnBnClickedTihuanLocalImage()
{
}

// 响应“非Alpha融合绘制”
void CImageBasePropEditDlg::OnBnClickedNotAlphaDrawChk()
{
}

void CImageBasePropEditDlg::SetSelectImageBaseFromListSelect(IPropertyImageBase* pSelectImgBaseProp)
{
	if (m_pParentImgProp != NULL)
	{
		m_pParentImgProp->SetImageBaseProp(pSelectImgBaseProp);
		if (pSelectImgBaseProp != NULL)
			m_pParentImgProp->SetRelevancyPropName((WCHAR*)pSelectImgBaseProp->GetObjectName());
		else
			m_pParentImgProp->SetRelevancyPropName(NULL);
	}
}

void CImageBasePropEditDlg::OnBnClickedDrawMidAreaCheckbox()
{
	if (m_pParentImgProp == NULL)
		return;

	if (m_ImageBaseList.m_pSelectImgBaseProp == NULL || m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp() == NULL)
		return;

	IMAGE_BASE_PROP* pSelImgProp = m_ImageBaseList.m_pSelectImgBaseProp->GetImageProp();
	pSelImgProp->bIsDrawJggMid = (m_Jgg_MidDrawCheckBox.GetCheck() == 1);
}

void CImageBasePropEditDlg::OnBnClickedDeleteLocalImage()
{
	m_LocalImageList.OnDeleteLocalImage();
}

CImageBaseView* CImageBasePropEditDlg::GetImageBaseView()
{
	return m_pImageView;
}
