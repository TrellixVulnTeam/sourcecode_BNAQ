// һ���ؼ�����ʵ�ֵ����нӿ�

#include "stdafx.h"
#include "..\..\Inc\ICtrlInterface.h"

ICtrlInterface::ICtrlInterface(IUiFeatureKernel *pUiKernel) : IControlBase(pUiKernel)
{
}

ICtrlInterface::~ICtrlInterface()
{
}

// �ؼ���Ҫ�����һЩ�Զ������Ϣ����Ϣ�����ϻ��ɶԻ�����������ؼ�����
int ICtrlInterface::OnCtrlNotify(int nMsgId, WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}

// Builderˢ�����ԣ��˺�����ֻҪ���¼��ؿؼ����Լ���
void ICtrlInterface::OnBuilderRefreshProp(IPropertyBase* pPropBase)
{
}

// ������
void ICtrlInterface::OnMouseEnter(POINT pt)
{
}

// ����Ƴ�
void ICtrlInterface::OnMouseLeave(POINT pt)
{
}

// ����ƶ�
void ICtrlInterface::OnMouseMove(POINT pt)
{
}

// ���������
void ICtrlInterface::OnLButtonDown(POINT pt)
{
}

// ������̧��
void ICtrlInterface::OnLButtonUp(POINT pt)
{
}

// ������˫��
void ICtrlInterface::OnLButtonDbClick(POINT pt)
{
}

// ����ڿؼ��ڲ��϶��ؼ�
void ICtrlInterface::OnMouseDragging(POINT pt)
{
}

// ����Ҽ����
void ICtrlInterface::OnRButtonDown(POINT pt)
{
}

// �ƶ������ÿؼ�λ��
void ICtrlInterface::OnSize()
{
}

// �ƶ����ڿ�ʼ
void ICtrlInterface::OnEnterSizeMove()
{
}

// �ƶ����ڽ���
void ICtrlInterface::OnExitSizeMove()
{
}

// �ؼ�ȡ�ý��㣬ͨ��Tab����ת������ؼ�
void ICtrlInterface::OnSetFocus()
{
}

// �ؼ�ʧȥ����
void ICtrlInterface::OnKillFocus()
{
}

// �ؼ�ȡ�ü���������Ϣ
void ICtrlInterface::OnChar(WPARAM wParam, LPARAM lParam)
{
}

// �ؼ�ȡ�ü���������Ϣ
void ICtrlInterface::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
}

// �ؼ�ȡ�ü���������Ϣ
void ICtrlInterface::OnKeyUp(WPARAM wParam, LPARAM lParam)
{
}

// ���ܵ�Ĭ�ϻس�����ִ�пؼ�����
void ICtrlInterface::OnDefaultEnterCtrl()
{
}

// ���ƿؼ��Ķ����������Ҫ����ˢ�½��棬����true�����򷵻�false
// �˺����ɶ�ʱ��������ÿ100���봥��һ��
bool ICtrlInterface::OnDrawAnimation()
{
	return false;
}

// ��ʱ��
void ICtrlInterface::OnTimer(UINT nTimerId)
{
}

// ��������Ϣ
void ICtrlInterface::OnVScroll(UINT nSBCode, UINT nPos, IControlBase* pScrollBar)
{
}

void ICtrlInterface::OnHScroll(UINT nSBCode, UINT nPos, IControlBase* pScrollBar)
{
}

// ��������Ϣ
void ICtrlInterface::OnMouseWheel(WPARAM wParam, LPARAM lParam)
{
}

// ����Ƿ������˿ؼ�ָ����RGN����Ĭ�Ϸ���true�������ؼ�����RGN����
bool ICtrlInterface::OnCheckMouseInRgn(POINT pt, int nMouseMsgId)
{
	return true;
}

// �����Ի�������Ի����ϵĿؼ�����ʼ�����
void ICtrlInterface::OnWindowFinalCreate()
{
}

// ��һ���ؼ������������ӿؼ���ʱ��ϵͳ�ᷢ�ʹ���������ӿؼ�����Ϣ
void ICtrlInterface::OnCreateSubControl(bool bIsCreate)
{
}

// �����Ի��򼴽��ر�
void ICtrlInterface::OnWindowClose()
{
}

// ���ÿؼ����
IPropertyCursor* ICtrlInterface::OnSetCursor(POINT pt)
{
	return NULL;
}

// ����϶�����������̧����ꡣpDragCtrl����ק��Դ�ؼ�
void ICtrlInterface::OnDragStop(IControlBase* pDragCtrl, POINT pt, WPARAM wParam, LPARAM lParam)
{
}

// ȡ�ÿؼ�֮����ק�����ݲ������ڴ����� OnDragStop ��Ϣ��ᱻ����
void ICtrlInterface::OnGetDragParam(WPARAM& wParam, LPARAM& lParam)
{
}

// �û��Զ���ǿ������ʼ
void ICtrlInterface::OnUserDefHighAnimationBegin()
{
}

// �û��Զ���ǿ�������ƽӿڣ�hWndDc���ؼ����ڵĴ���DC
void ICtrlInterface::OnUserDefHighAnimationDraw(CDrawingImage &CtrlAnimationMemDc, HDC &hWndDc)
{
}

// �û��Զ���ǿ��������
void ICtrlInterface::OnUserDefHighAnimationEnd()
{
}

// �յ���Ҫ��ջ��ƻ������Ϣ
void ICtrlInterface::OnClearDrawMemoryDc()
{
}

// ��ʼ��¡��������Clone�������룬����������� CAN_NOT_CLONE ���򲻽��п�¡����
int ICtrlInterface::OnBeforeClone(WPARAM wParam)
{
	return S_OK;
}

void ICtrlInterface::OnAfterClone(IControlBase* pCloneCtrl, WPARAM lParam)
{

}

// ��һ���ؼ���TabOrder���Ա�������֮��ͬʱ�˿ؼ��õ����㣬���ڻὫ����Ϣ
// ͨ������������͸�ע������Ҫȡ�ý�����Ϣ�Ŀؼ�
void ICtrlInterface::OnContrlFocusChange(IControlBase* pFocusCtrl)
{

}

// һ���ؼ��������һ���ؼ����ӿؼ������Ҵ˿ؼ���ͨ��CreateSubContrl���������ģ���ô����ؼ��ĸ��ؼ���Clone��ʱ�򣬵�����ӿؼ�Ҳ��Clone��ɺ󣬻��ܵ�����Ϣ����
void ICtrlInterface::OnCreateSubControlCloneEnd()
{

}
