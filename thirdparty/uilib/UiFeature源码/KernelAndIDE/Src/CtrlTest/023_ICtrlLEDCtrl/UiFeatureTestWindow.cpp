#include "StdAfx.h"
#include "UiFeatureTestWindow.h"
#include <assert.h>
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include <Shellapi.h>
#include <windows.h>
#include <atltime.h>

CUiFeatureTestWindow::CUiFeatureTestWindow()
{
	m_dwMainThreadId = 0;
	m_pShowTime = NULL;
}

CUiFeatureTestWindow::~CUiFeatureTestWindow()
{
	::KillTimer(this->GetSafeHandle(),IDC_Timer);
}

bool CUiFeatureTestWindow::ShowUiFeatureTestWindow(DWORD dwMainThreadId)
{
	m_dwMainThreadId = dwMainThreadId;

	// ȡ��UI�ں�DLL��·��
	CStringW strKernelDllPath = PathHelperW(_T(NAME_KERNEL_DLL));
	// ȡ��Ƥ������·��
	CStringW strSkinPath = PathHelperW(_T("..\\SkinPackage\\023_ICtrlLEDCtrl\\023_ICtrlLEDCtrl.ufd"));

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

// WM_CREATE���Ի����ʼ��	
void CUiFeatureTestWindow::OnCreate()
{
	m_pShowTime = GET_CONTROL(ICtrlLEDCtrl, "ShowTime");
	if (m_pShowTime == NULL)
	{
		assert(false);
		return;
	}
	::SetTimer(this->GetSafeHandle(),IDC_Timer,1000,NULL);	
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


LRESULT CUiFeatureTestWindow::OnTimer(WPARAM wParam, LPARAM lParam, BOOL bContinue)
{
	CTime Current= CTime::GetCurrentTime();	//ȡ��Ŀǰ��ϵͳʱ��
	long hour, minute, second;	//��������ʱ�����ݵı���
	hour = Current.GetHour();	//ȡ��Ŀǰϵͳʱ���Сʱ
	minute = Current.GetMinute();	//ȡ��Ŀǰϵͳʱ��ķ�������
	second = Current.GetSecond();	//ȡ��Ŀǰϵͳʱ���������
	if (m_pShowTime!=NULL)
	{
		CStringW szText;
		szText.Format(_T("%02d:%02d:%02d"),hour,minute,second);
		
		m_pShowTime->SetText(szText,true);
	}
	return S_OK;
}