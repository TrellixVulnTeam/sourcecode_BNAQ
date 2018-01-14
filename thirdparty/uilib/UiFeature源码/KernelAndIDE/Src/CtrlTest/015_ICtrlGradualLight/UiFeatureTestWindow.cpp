#include "StdAfx.h"
#include "UiFeatureTestWindow.h"
#include <assert.h>
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include <Shellapi.h>
#include <windows.h>

CUiFeatureTestWindow::CUiFeatureTestWindow()
{
	m_dwMainThreadId = 0;
	m_pBeginFlyBtn = NULL;
	m_pFlyImage = NULL;
	m_pGradualLight = NULL;
	m_pRoolAdver = NULL;
}

CUiFeatureTestWindow::~CUiFeatureTestWindow()
{
}

bool CUiFeatureTestWindow::ShowUiFeatureTestWindow(DWORD dwMainThreadId)
{
	m_dwMainThreadId = dwMainThreadId;

	// ȡ��UI�ں�DLL��·��
	CStringW strKernelDllPath = PathHelperW(_T(NAME_KERNEL_DLL));
	// ȡ��Ƥ������·��
	CStringW strSkinPath = PathHelperW(_T("..\\SkinPackage\\015_ICtrlGradualLight\\015_ICtrlGradualLight.ufd"));

	CRect WndRct(0, 0, 0, 0);
	// ����Ƥ�����������ڣ�������ڴ�СΪ0��������Ƥ�����еĴ�С�Զ����ô��ڵĴ�С��
	// ��һ������ΪƤ��������
	return CreateFeatureWindow(NULL, strKernelDllPath, strSkinPath, L"TestWindow", NULL, WndRct, SW_SHOW, WS_OVERLAPPED | WS_THICKFRAME, NULL);
}

void CUiFeatureTestWindow::OnKeyDown(int nVirtKey, int nFlag)
{
	// ���Գ����¡�Esc�����˳�����
	if (nVirtKey == VK_ESCAPE)
	{
		this->CloseWindow();
		::PostThreadMessage(m_dwMainThreadId, WM_QUIT, 0, 0);
	}
}

// WM_CREATE���Ի����ʼ��	
void CUiFeatureTestWindow::OnCreate()
{
	GET_CONTROL_EX(m_pBeginFlyBtn, ICtrlShadowButton, "ToFly");
	GET_CONTROL_EX(m_pFlyImage, ICtrlStraightLineFlyImage, "FlyImg");
	GET_CONTROL_EX(m_pGradualLight, ICtrlGradualLight, "BLight");
	GET_CONTROL_EX(m_pRoolAdver, ICtrlRollAdvertisement, "RollAdver");
	if (m_pBeginFlyBtn == NULL || m_pFlyImage == NULL || m_pGradualLight == NULL || m_pRoolAdver == NULL)
	{
		assert(false);
		return;
	}

	// ���ź�����Ч��
	m_pGradualLight->Play();

	// ���ù�����Ϣ
	ROLL_ADVERTISEMENT_ITEM adver;
	adver.nId = adver.nConfActive = 1;
	adver.pStrData = L"http://fangshunbao.blog.sohu.com/";
	adver.pStrShowInfo = L"UiFeature�Ĳ��ͣ���ӭ���٣�";
	m_pRoolAdver->AddAdvertisement(adver);

	adver.nId = adver.nConfActive = 2;
	adver.pStrData = L"http://zhuomian.360.cn/";
	adver.pStrShowInfo = L"����һ��360��ȫ�����о�һ�£�����UiFeature�����磡";
	m_pRoolAdver->AddAdvertisement(adver);

	adver.nId = adver.nConfActive = 2;
	adver.pStrData = L"http://zhuomian.360.cn/";
	adver.pStrShowInfo = L"������������һ����360��Ϸ���ӡ��о�һ�£�����UiFeature�����磡";
	m_pRoolAdver->AddAdvertisement(adver);
}

void CUiFeatureTestWindow::UnInitialized()
{
	if (m_pUiKernel != NULL)
		m_pUiKernel->UnInitialized();
}

LRESULT CUiFeatureTestWindow::OnSysCommandClose(WPARAM wParam, LPARAM lParam)
{
	::PostThreadMessage(m_dwMainThreadId, WM_QUIT, 0, 0);
	return S_OK;
}

LRESULT CUiFeatureTestWindow::OnBeginFly(WPARAM wParam, LPARAM lParam)
{
	// �����ť����ʼ���趯��
	if (m_pFlyImage == NULL)
		return S_FALSE;

	RECT beginRct = {0}, endRct = {0};
	m_pFlyImage->GetFlyPostion(beginRct, endRct);
	m_pFlyImage->StartFly(beginRct, endRct);

	return S_OK;
}

LRESULT CUiFeatureTestWindow::OnClickAdrertisement(WPARAM wParam, LPARAM lParam)
{
	ROLL_ADVERTISEMENT_ITEM *pAdvertisementeInfo = (ROLL_ADVERTISEMENT_ITEM *)wParam;
	if (pAdvertisementeInfo == NULL || pAdvertisementeInfo->pStrData == NULL || wcslen(pAdvertisementeInfo->pStrData) <= 0)
		return S_FALSE;

	::ShellExecuteW(NULL, NULL, pAdvertisementeInfo->pStrData, NULL, NULL, SW_SHOWNORMAL);
	return S_OK;
}
