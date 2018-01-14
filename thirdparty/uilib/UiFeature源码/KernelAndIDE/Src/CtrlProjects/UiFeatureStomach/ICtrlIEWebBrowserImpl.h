
#pragma once
#include "..\..\Inc\Control\ICtrlIEWebBrowser.h"
#include "WindowsIe\UiFeatureBrowserWindow.h"


class ICtrlIEWebBrowserImpl : public ICtrlIEWebBrowser
{
public:
	ICtrlIEWebBrowserImpl(IUiFeatureKernel *pUiKernel);
	virtual ~ICtrlIEWebBrowserImpl();

	virtual VOID OpenUrl(LPCWSTR pszUrl);
	virtual LPCWSTR GetUrl();
	// �ɼ�����
	virtual void SetVisible(bool bVisible, bool bSetChild = false);

	// �ؼ���Ҫ�����һЩ�Զ������Ϣ����Ϣ�����ϻ��ɶԻ�����������ؼ�����
	BEGIN_CTRL_NOTIFY
		CTRL_NOTIFY_HANDLER(WM_IE_WEB_CREATE_UIF, OnCreateUiFeatureIeWindow)
		CTRL_NOTIFY_HANDLER(WM_IE_WEB_OPEN_URL, OnOpenUrl)
		CTRL_NOTIFY_HANDLER(WM_MOVE, OnWindowMove)
		CTRL_NOTIFY_HANDLER(WM_SYSCOMMAND, OnSysCommand)
	END_CTRL_NOTIFY

protected:
	// �����ؼ����ڴ��������Լ��Ŀؼ�����
	// bIsNewCtrl��trueʱ˵����Builder���ã��´���һ���ؼ�����Ҫ��ʼ�����Եĸ���Ĭ��ֵ
	// false��˵������Ƥ�����Ѿ���ʼ����ϣ����Դ�����ϵ�ʱ�򣬴�xml�ж�ȡ������ֵ�Ѿ���ֵ����ˣ������ٳ�ʼ��������xml�е�ֵ�ᱻ���
	virtual bool CreateControlPropetry(bool bIsNewCtrl);
	// ��ʼ���ؼ�
	virtual void OnCreate();
	// �ؼ���ʼ�����
	virtual void OnFinalCreate();
	// ���ٿؼ�
	virtual void OnDestroy();
	// ���ƿؼ�
	virtual void OnPaint(CDrawingBoard &DrawBoard);

	// �ƶ������ÿؼ�λ��
	virtual void OnSize();

	// ����ӿڻ��������Ի����ʼ����ɵ�ʱ�����
	// �ؼ�ͨ����������ӿڣ�����������ӿں�����ͨ�������ؼ�������ȡ�õ�ǰ�Ի�����������ؼ���
	virtual void OnWindowFinalCreate();
	// �����Ի��򼴽��ر�
	virtual void OnWindowClose();
	// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
	virtual LRESULT ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam);

	int OnCreateUiFeatureIeWindow(WPARAM wParam, LPARAM lParam);
	int OnOpenUrl(WPARAM wParam, LPARAM lParam);
	int OnWindowMove(WPARAM wParam, LPARAM lParam);
	int OnSysCommand(WPARAM wParam, LPARAM lParam);

private:
	void SetIeWindowPostion();
	BOOL SetIeWindowShow(BOOL* pIsWndVisible);

private:
	IPropertyString* m_pPropUrl;
	CUiFeatureBrowserWindow m_WebWindow;
};
