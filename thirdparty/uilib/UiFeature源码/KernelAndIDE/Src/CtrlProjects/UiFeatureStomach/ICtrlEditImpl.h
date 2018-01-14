
#pragma once
#include "..\..\Inc\Control\ICtrlEdit.h"
#include "..\..\Inc\IPropertyImage.h"
#include "EditWindow.h"

class ICtrlEditImpl : public ICtrlEdit
{
public:
	ICtrlEditImpl(IUiFeatureKernel *pUiKernel);
	virtual ~ICtrlEditImpl();

	// �ɼ�����
	virtual void SetVisible(bool bVisible, bool bSetChild = false);

	virtual LPCWSTR GetEditText();
	virtual void SetEditText(LPCWSTR pszText);
	virtual void SetEditFocus();

	// ȡ��Edit�йܴ��ڵľ��
	virtual HWND GetWindowHwnd();
	// ȡ��Edit���ڵľ��
	virtual HWND GetEditHwnd();
	virtual void EnableEditWindow(BOOL bEnable);
	virtual void SetReadOnly(BOOL bReadOnly);

	// �жϵ�ǰedit�Ƿ�õ����뽹��
	virtual bool IsForegroundWindow();

	virtual void GetEditRemindText(CStringW &strText);
	virtual void SetEditRemindText(WCHAR *pszText);
	virtual void SetEditToRemindText();

	virtual void SetEditAutoVScroll(bool bVScroll);
	virtual void SetEditAutoHScroll(bool bHScroll);
	virtual void SetEditMultiLine(bool bMultiline = false);

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
	// �ؼ���Ҫ�����һЩ�Զ������Ϣ����Ϣ�����ϻ��ɶԻ�����������ؼ�����
	virtual int OnCtrlNotify(int nMsgId, WPARAM wParam, LPARAM lParam);
	// �ƶ������ÿؼ�λ��
	virtual void OnSize();
	// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
	virtual LRESULT ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam);

private:
	RECT GetEditWindowRect();

private:
	CEditWindow m_EditWnd;
	IPropertyImage* m_pPropEditBackgroundImg;
	IPropertyGroup* m_pPropMargins;
	IPropertyInt*	m_pPropLeft;
	IPropertyInt*	m_pPropTop;
	IPropertyInt*	m_pPropRight;
	IPropertyInt*	m_pPropBottom;
};
