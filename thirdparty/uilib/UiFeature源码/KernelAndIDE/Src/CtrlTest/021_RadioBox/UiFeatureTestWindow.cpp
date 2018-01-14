#include "StdAfx.h"
#include "UiFeatureTestWindow.h"
#include <assert.h>
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include <Shellapi.h>
#include <windows.h>
#include "..\..\HighQualitySkin\Win32MessageBox\Win32MessageBox.h"

CUiFeatureTestWindow::CUiFeatureTestWindow()
{
	m_dwMainThreadId = 0;
	m_pCheckRadio = NULL;
	m_pshowTip = NULL;
	m_pCockRadio = NULL;
	m_pClearRadio = NULL;
	m_pRehabRadio = NULL;
	m_pRepairRadio = NULL;
	m_pPcClear = NULL;
	m_pFunctionRadio = NULL;
	m_pSoftwareRadio = NULL;
	m_pshowTip2 = NULL;

	m_pRadio3 = NULL;
	m_pRadio2 = NULL;
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
	CStringW strSkinPath = PathHelperW(_T("..\\SkinPackage\\021_RadioBox\\021_RadioBox.ufd"));

	CRect WndRct(0, 0, 0, 0);
	// ����Ƥ�����������ڣ�������ڴ�СΪ0��������Ƥ�����еĴ�С�Զ����ô��ڵĴ�С��
	// ��һ������ΪƤ��������
	return CreateFeatureWindow(NULL, strKernelDllPath, strSkinPath, L"Main", NULL, WndRct, SW_SHOW, WS_OVERLAPPED | WS_THICKFRAME, NULL);
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

// �����ڵ���Ϣ������
LRESULT CUiFeatureTestWindow::WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	return CUiFeatureWindow::WndProc(nMsgId, wParam, lParam);
}

// WM_CREATE���Ի����ʼ��	
void CUiFeatureTestWindow::OnCreate()
{
	/*m_pShowDirBtn = GET_CONTROL(ICtrlShadowButton, "OpenMsgBox");
	if (m_pShowDirBtn == NULL)
	{
		assert(false);
		return;
	}*/

	m_pCheckRadio = GET_CONTROL(ICtrlRadioBox,"CheckRadio");
	if (m_pCheckRadio == NULL)
	{
		assert(false);
		return;
	}

	m_pCockRadio = GET_CONTROL(ICtrlRadioBox,"CockRadio");
	if (m_pCockRadio == NULL)
	{
		assert(false);
		return;
	}

	m_pClearRadio = GET_CONTROL(ICtrlRadioBox,"ClearRadio");
	if (m_pClearRadio == NULL)
	{
		assert(false);
		return;
	}

	m_pRehabRadio = GET_CONTROL(ICtrlRadioBox,"RehabRadio");
	if (m_pRehabRadio == NULL)
	{
		assert(false);
		return;
	}

	m_pRepairRadio = GET_CONTROL(ICtrlRadioBox,"RepairRadio");
	if (m_pRepairRadio == NULL)
	{
		assert(false);
		return;
	}

	m_pPcClear = GET_CONTROL(ICtrlRadioBox,"PcClear");
	if (m_pPcClear == NULL)
	{
		assert(false);
		return;
	}

	m_pFunctionRadio = GET_CONTROL(ICtrlRadioBox,"FunctionRadio");
	if (m_pFunctionRadio == NULL)
	{
		assert(false);
		return;
	}

	m_pSoftwareRadio = GET_CONTROL(ICtrlRadioBox,"SoftwareRadio");
	if (m_pRepairRadio == NULL)
	{
		assert(false);
		return;
	}

	m_pshowTip = GET_CONTROL(ICtrlStatic,"showTip");
	if (m_pshowTip == NULL)
	{
		assert(false);
		return;
	}

	m_pshowTip2 = GET_CONTROL(ICtrlStatic,"showTip2");
	if (m_pshowTip2 == NULL)
	{
		assert(false);
		return;
	}

	m_pRadio3 = GET_CONTROL(ICtrlRadioBox,"radio3");
	if (m_pRadio3 == NULL)
	{
		assert(false);
		return;
	}

	m_pRadio2 = GET_CONTROL(ICtrlRadioBox,"radio2");
	if (m_pRadio2 == NULL)
	{
		assert(false);
		return;
	}
}

void CUiFeatureTestWindow::UnInitialized()
{
	if (m_pUiKernel != NULL)
		m_pUiKernel->UnInitialized();
}

LRESULT CUiFeatureTestWindow::OnCheckRadioClick(WPARAM wParam, LPARAM lParam)
{
	
	if (m_pCheckRadio->GetCheck())
	{
		m_pshowTip->SetText(_T("��������족�ѡ����!"));
	}
	return S_OK;
}

LRESULT CUiFeatureTestWindow::OnCockRadioClick(WPARAM wParam, LPARAM lParam)
{

	if (m_pCockRadio->GetCheck())
	{
		m_pshowTip->SetText(_T("����ɱľ���ѡ����!"));
	}
	return S_OK;
}

LRESULT CUiFeatureTestWindow::OnClearRadioClick(WPARAM wParam, LPARAM lParam)
{

	if (m_pClearRadio->GetCheck())
	{
		m_pshowTip->SetText(_T("�����������ѡ����!"));
	}
	return S_OK;
}

LRESULT CUiFeatureTestWindow::OnRehabRadioClick(WPARAM wParam, LPARAM lParam)
{

	if (m_pRehabRadio->GetCheck())
	{
		m_pshowTip->SetText(_T("���޸�©�����ѡ����!"));
	}
	return S_OK;
}

LRESULT CUiFeatureTestWindow::OnRepairRadioClick(WPARAM wParam, LPARAM lParam)
{

	if (m_pRepairRadio->GetCheck())
	{
		m_pshowTip->SetText(_T("��ϵͳ�޸����ѡ����!"));
	}
	return S_OK;
}


LRESULT CUiFeatureTestWindow::OnPcClearClick(WPARAM wParam, LPARAM lParam)
{

	if (m_pPcClear->GetCheck())
	{
		m_pshowTip->SetText(_T("�����������ѡ����!"));
	}
	return S_OK;
}


LRESULT CUiFeatureTestWindow::OnFunctionRadioClick(WPARAM wParam, LPARAM lParam)
{

	if (m_pFunctionRadio->GetCheck())
	{
		m_pshowTip->SetText(_T("�����ܴ�ȫ���ѡ����!"));
	}
	return S_OK;
}


LRESULT CUiFeatureTestWindow::OnSoftwareRadioClick(WPARAM wParam, LPARAM lParam)
{

	if (m_pSoftwareRadio->GetCheck())
	{
		m_pshowTip->SetText(_T("������ܼҡ��ѡ����!"));
	}
	return S_OK;
}

LRESULT CUiFeatureTestWindow::OnRadio3Click(WPARAM wParam, LPARAM lParam)
{

	if (m_pRadio3->GetCheck())
	{
		m_pshowTip2->SetText(_T("��ѡ��1���ѡ����!"));
	}
	return S_OK;
}

LRESULT CUiFeatureTestWindow::OnRadio2Click(WPARAM wParam, LPARAM lParam)
{

	if (m_pRadio2->GetCheck())
	{
		m_pshowTip2->SetText(_T("��ѡ��2���ѡ����!"));
	}
	return S_OK;
}


LRESULT CUiFeatureTestWindow::OnSysCommandClose(WPARAM wParam, LPARAM lParam)
{
	::PostThreadMessage(m_dwMainThreadId, WM_QUIT, 0, 0);
	return S_OK;
}
