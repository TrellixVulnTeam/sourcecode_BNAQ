#include "StdAfx.h"
#include "HealthCheck.h"
#include <assert.h>
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include <Shellapi.h>
#include <windows.h>

CHealthCheck::CHealthCheck()
{

}

CHealthCheck::~CHealthCheck()
{

}

bool CHealthCheck::CreateUIWindow(HWND hParent)
{
	// ȡ��UI�ں�DLL��·��
	CStringW strKernelDllPath = PathHelperW(_T(NAME_KERNEL_DLL));
	// ȡ��Ƥ������·��
	CStringW strSkinPath = PathHelperW(_T("..\\SkinPackage\\022_IHwndObj\\022_IHwndObj.ufd"));

	CRect WndRct(0, 0, 0, 0);
	// ����Ƥ�����������ڣ�������ڴ�СΪ0��������Ƥ�����еĴ�С�Զ����ô��ڵĴ�С��
	// ��һ������ΪƤ��������
	return CreateFeatureWindow(NULL, strKernelDllPath, strSkinPath, L"HealthCheck", hParent, WndRct, SW_SHOW, WS_POPUP, (WPARAM)this);
}

void CHealthCheck::OnKeyDown(int nVirtKey, int nFlag)
{
	if (nVirtKey == VK_ESCAPE)
	{
		this->CloseWindow();
	}
}

// �ؼ����͸����ڵ���Ϣ�ӿ�
LRESULT CHealthCheck::OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam)
{
	// ����� OnCtrlMessage ���������ȵ��ø���� OnCtrlMessage ��������ִ���Լ������ڲ��Ĳ���
	CUiFeatureWindow::OnCtrlMessage(pCtrl, nMsgId, wParam, lParam);


	return 0;
}

// �����ڵ���Ϣ������
LRESULT CHealthCheck::WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	return CUiFeatureWindow::WndProc(nMsgId, wParam, lParam);
}

// WM_CREATE���Ի����ʼ��	
void CHealthCheck::OnCreate()
{
}


