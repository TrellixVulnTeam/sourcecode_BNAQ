#pragma once
#include "..\..\Inc\Control\ICtrlHwndObj.h"

class ICtrlHwndObjImpl : public ICtrlHwndObj
{
public:
	ICtrlHwndObjImpl(IUiFeatureKernel *pUiKernel);
	virtual ~ICtrlHwndObjImpl();

	// �ؼ���Ҫ�����һЩ�Զ������Ϣ����Ϣ�����ϻ��ɶԻ�����������ؼ�����
	BEGIN_CTRL_NOTIFY
		CTRL_NOTIFY_HANDLER(WM_MOVE, OnWindowMove)
		CTRL_NOTIFY_HANDLER(WM_SYSCOMMAND, OnSysCommand)
	END_CTRL_NOTIFY

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

	virtual BOOL IsHwndExist(HWND hwnd);

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

	int OnWindowMove(WPARAM wParam, LPARAM lParam);
	int OnSysCommand(WPARAM wParam, LPARAM lParam);


private:
	void SetHwndWindowPostion();

private:
	HWND m_theHwnd;			//��ǰ��ʾ�Ĵ��ھ��
	vector<HWND> m_vectorHwnd;	//�����б�

};