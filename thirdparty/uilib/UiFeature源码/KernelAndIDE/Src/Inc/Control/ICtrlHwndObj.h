#pragma once
#include "..\ICtrlInterface.h"	//�����ؼ��ӿ��ļ�

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_HWNDOBJ							(L"HwndObj")

class _declspec(novtable) ICtrlHwndObj : public ICtrlInterface
{
public:
	ICtrlHwndObj(IUiFeatureKernel *pUiKernel);

	//���ô�����HwndObj�����໥��
	virtual BOOL Attach(HWND hwnd);

	//���������HwndObj�İ�
	virtual BOOL Detach(HWND hwnd);

	//������Ż�ȡ�󶨵Ĵ��ھ��
	virtual HWND GetSafeHwnd(int nIndex);

	//��ȡHwndObj��ǰ�󶨵Ĵ��ھ��
	virtual HWND GetBindHwnd();

	//��ʾHideBindWindow���������Ĵ���
	virtual BOOL ShowBindWindow();

	//���ص�ǰ�󶨵Ĵ���
	virtual BOOL HideBindWindow();

	//�ƶ���HwndObj���а󶨵Ĵ��ڵ�ָ������
	virtual void MoveHwndToRect(RECT rect); 

	//���ݴ��ھ������ʾ��HwndObj�󶨵Ĵ���
	virtual BOOL ShowWindow(HWND hwnd);

	//������������ʾ��HwndObj�󶨵Ĵ���
	virtual BOOL ShowWindowByIndex(int nIndex);

	//�жϱ��󶨵Ĵ������е����Ƿ���ڸô��ھ��
	virtual BOOL IsHwndExist(HWND hwnd);

};