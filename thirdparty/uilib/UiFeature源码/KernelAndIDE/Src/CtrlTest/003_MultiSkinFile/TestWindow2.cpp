#include "StdAfx.h"
#include "TestWindow2.h"
#include <assert.h>
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include <Shellapi.h>
#include <windows.h>

CTestWindow2::CTestWindow2()
{
}

CTestWindow2::~CTestWindow2()
{
}

bool CTestWindow2::ShowTestWindow2()
{
	// ȡ��UI�ں�DLL��·��
	CStringW strKernelDllPath = PathHelperW(_T(NAME_KERNEL_DLL));
	// ȡ��Ƥ������·��
	CStringW strSkinPath = PathHelperW(_T("..\\SkinPackage\\003_MultiSkinFile\\Skin_02.ufd"));

	CRect WndRct(0, 0, 0, 0);
	// ����Ƥ�����������ڣ�������ڴ�СΪ0��������Ƥ�����еĴ�С�Զ����ô��ڵĴ�С��
	// ��һ������ΪƤ��������
	return CreateFeatureWindow("123", strKernelDllPath, strSkinPath, L"Dlg_02", NULL, WndRct, SW_SHOW, WS_OVERLAPPED | WS_THICKFRAME, NULL);
}

void CTestWindow2::OnKeyDown(int nVirtKey, int nFlag)
{
	if (nVirtKey == VK_ESCAPE)
	{
		this->CloseWindow();
	}
}

// �ؼ����͸����ڵ���Ϣ�ӿ�
LRESULT CTestWindow2::OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam)
{
	// ����� OnCtrlMessage ���������ȵ��ø���� OnCtrlMessage ��������ִ���Լ������ڲ��Ĳ���
	CUiFeatureWindow::OnCtrlMessage(pCtrl, nMsgId, wParam, lParam);


	return 0;
}

// �����ڵ���Ϣ������
LRESULT CTestWindow2::WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	return CUiFeatureWindow::WndProc(nMsgId, wParam, lParam);
}

// WM_CREATE���Ի����ʼ��	
void CTestWindow2::OnCreate()
{
}
