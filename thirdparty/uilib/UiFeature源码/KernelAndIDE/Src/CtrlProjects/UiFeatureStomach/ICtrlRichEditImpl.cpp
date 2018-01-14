
#include "StdAfx.h"
#include "ICtrlRichEditImpl.h"

ICtrlRichEdit::ICtrlRichEdit(IUiFeatureKernel *pUiKernel) : ICtrlInterface(pUiKernel) {}

ICtrlRichEditImpl::ICtrlRichEditImpl(IUiFeatureKernel *pUiKernel) : ICtrlRichEdit(pUiKernel)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_RICH_EDIT);

	// �˿ؼ�����ҪTips���ԣ�����xml��Ϣ���Ż����ܣ�ɾ�����д��룬���±���ؼ����˿ؼ��ͻ�֧��ϵͳTips
	m_bHaveSysTipsProp = false;
	m_pTextHost = NULL;
}

ICtrlRichEditImpl::~ICtrlRichEditImpl()
{
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlRichEditImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	return true;
}

// ��ʼ���ؼ�
void ICtrlRichEditImpl::OnCreate()
{
	if (m_pWindowBase == NULL)
		return;

	CREATESTRUCT createS;
	memset(&createS, 0, sizeof(CREATESTRUCT));

	createS.style = ES_MULTILINE;

	if (!CreateHost(m_pWindowBase->GetSafeHandle(), &createS, dynamic_cast<CHostCallBack*>(this), &m_pTextHost))
		return;
}

// �ؼ���ʼ�����
void ICtrlRichEditImpl::OnFinalCreate()
{
}

// ���ٿؼ�
void ICtrlRichEditImpl::OnDestroy()
{
}

// ���ƿؼ�
void ICtrlRichEditImpl::OnPaint(CDrawingBoard &DrawBoard)
{
}

// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
LRESULT ICtrlRichEditImpl::ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}

//@cmember Notify host of events
HRESULT ICtrlRichEditImpl::TxNotify(DWORD iNotify, void *pv)
{

	return S_OK;
}

// �ؼ�ȡ�ý��㣬ͨ��Tab����ת������ؼ�
void ICtrlRichEditImpl::OnSetFocus()
{
	if (m_pTextHost == NULL || m_pWindowBase == NULL)
		return;

	m_pWindowBase->RegisterWindowMessageControl(dynamic_cast<IControlBase*>(this));
}

// �ؼ�ʧȥ����
void ICtrlRichEditImpl::OnKillFocus()
{
	m_pWindowBase->RegisterWindowMessageControl(NULL);
}

// �ƶ������ÿؼ�λ��
void ICtrlRichEditImpl::OnSize()
{
	if (m_pTextHost != NULL)
	{
	}
}

// �ؼ���Ҫ�����һЩ�Զ������Ϣ����Ϣ�����ϻ��ɶԻ�����������ؼ�����
int ICtrlRichEditImpl::OnCtrlNotify(int nMsgId, WPARAM wParam, LPARAM lParam)
{
	if (m_pTextHost == NULL || m_pWindowBase == NULL)
		return S_FALSE;

	m_pTextHost->TxWindowProc(m_pWindowBase->GetSafeHandle(), nMsgId, wParam, lParam);
	return S_OK;
}
