
#pragma once
#include "..\ICtrlInterface.h"

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_IE_WEB_BROWSER						(L"IEWebBrowser")

// ����IE���ڵĴ�����Ϣ
#define WM_IE_WEB_CREATE_UIF							(WM_APP + 11)
#define WM_IE_WEB_OPEN_URL								(WM_APP + 12)

class _declspec(novtable) ICtrlIEWebBrowser : public ICtrlInterface
{
public:
	ICtrlIEWebBrowser(IUiFeatureKernel *pUiKernel);
	virtual VOID OpenUrl(LPCWSTR pszUrl) = 0;
	virtual LPCWSTR GetUrl() = 0;
};
