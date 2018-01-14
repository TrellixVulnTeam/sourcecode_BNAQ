#include "DMSpyAfx.h"
#include "MainWnd.h"
#include "DUIFindBtn.h"
DUIWindow* g_pMainWnd = NULL;

int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	OleInitialize(NULL);
	DMCode iErr = DM_ECODE_OK;
	DMApp theApp(hInstance);
	iErr = theApp.SetDefRegObj(L"DMResFolderImpl",DMREG_Res);// ����ʹ�����õ��ļ��н���Res��ʽ
	iErr = theApp.LoadResPack((WPARAM)(L"DMRes"),NULL,NULL); // ·���������������Ŀ¼
	iErr = theApp.InitGlobal();								 // ��ʼ��ָ����ȫ��skin��style��Ĭ������
	iErr = theApp.Register(DMRegHelperT<DUIFindBtn>(),true);
	DMSmartPtrT<CMainWnd> pMainWnd;
	if (DMSUCCEEDED(iErr))
	{
		pMainWnd.Attach(new CMainWnd());
		pMainWnd->DM_CreateWindow(L"dui_spy");				// ����������
		pMainWnd->SendMessage(WM_INITDIALOG);
		pMainWnd->CenterWindow();
		pMainWnd->ShowWindow(SW_SHOW);
		g_pMainWnd = pMainWnd;

		theApp.Run(pMainWnd->GetSafeHwnd());				// ���е�ǰ�̵߳���Ϣѭ������������Ϣ���й�����
		g_pMainWnd = NULL;
	}
	return (int) 0;
}