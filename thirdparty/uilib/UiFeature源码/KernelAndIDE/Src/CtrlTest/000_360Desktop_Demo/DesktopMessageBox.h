
#pragma once
#include "..\..\inc\CUiFeatureWindow.h"
#include "..\..\inc\Control\ICtrlShadowButton.h"
#include "..\..\inc\Control\ICtrlStatic.h"
#include "..\..\inc\Control\ICtrlImageBox.h"
#include <winuser.h>
#include <atlstr.h>
using namespace ATL;

// �����ǲ���ģ̬�ķ�ʽ���� CDesktopMessageBox ��ʱ�������Ҫ CDesktopMessageBox �ķ���ֵ������Ҫ�̳�����ӿڽ��лص�
class CNotDoModalMessageBoxCallBack
{
public:
	virtual void NDMMsgBoxCallBack(int nMsgId, int nMsgReturn) = 0;
};

class CDesktopMessageBox : public CUiFeatureWindow
{
public:
	CDesktopMessageBox();
	virtual ~CDesktopMessageBox();

	// dwMsgBoxType ����Ϊ���к�����
	// MB_OKCANCEL��MB_OK ��ѡһ
	// MB_ICONINFORMATION��MB_ICONWARNING��MB_ICONERROR ��ѡһ
	// ��������������
	// ����ֵΪ��IDOK��IDCANCEL ������һ��
	DWORD MessageBox(HWND hParent, IUiFeatureKernel* pUiKernel, LPCWSTR pszSkinPath, LPCWSTR pszMsgTitle, LPCWSTR pszMsgInfo,
		DWORD dwMsgBoxType = MB_OK | MB_ICONINFORMATION, INT nDlgIconId = 0,
		BOOL IsDoModal = TRUE, int nMsgId = 0, CNotDoModalMessageBoxCallBack* pNDMCallBack = NULL);

protected:
	// �ؼ����͸����ڵ���Ϣ�ӿ�
	virtual LRESULT OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam);
	// �����ڵ���Ϣ������
	virtual LRESULT WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	// WM_CREATE���Ի����ʼ��	
	virtual void OnCreate();

	virtual void OnKeyDown(int nVirtKey, int nFlag);
	void EndMessageBox(DWORD nReturn);

private:
	HWND m_hParent;
	HICON m_DlgIcon;
	INT m_nDlgIconId;

	DWORD m_dwThreadId;
	DWORD m_dwMsgBoxType;
	DWORD m_dwMsgReturn;
	DWORD m_dwMsgIconType;
	CStringW m_strMsgTitle;
	CStringW m_strMsgInfo;

	BOOL m_bIsDoModal;
	int m_nMsgId;
	CNotDoModalMessageBoxCallBack* m_pNDMCallBack;

	ICtrlShadowButton* m_pOk2Btn;

	ICtrlShadowButton* m_pCloseBtn;
	ICtrlShadowButton* m_pCancelBtn;
	ICtrlShadowButton* m_pOkBtn;
	ICtrlStatic* m_pTitle;
	ICtrlStatic* m_pInfomation;

	ICtrlImageBox* m_IconI;
	ICtrlImageBox* m_IconW;
	ICtrlImageBox* m_IconE;
};
