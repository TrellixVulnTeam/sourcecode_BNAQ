
#include "StdAfx.h"
#include "ICtrl_XXXX_Impl.h"

ICtrl_XXXX_::ICtrl_XXXX_(IUiFeatureKernel *pUiKernel) : ICtrlInterface(pUiKernel) {}

ICtrl_XXXX_Impl::ICtrl_XXXX_Impl(IUiFeatureKernel *pUiKernel) : ICtrl_XXXX_(pUiKernel)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_BASE_PANEL);

	// �˿ؼ�����ҪTips���ԣ�����xml��Ϣ���Ż����ܣ�ɾ�����д��룬���±���ؼ����˿ؼ��ͻ�֧��ϵͳTips
	m_bHaveSysTipsProp = false;
}

ICtrl_XXXX_Impl::~ICtrl_XXXX_Impl()
{
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrl_XXXX_Impl::CreateControlPropetry(bool bIsNewCtrl)
{
	return true;
}

// ��ʼ���ؼ�
void ICtrl_XXXX_Impl::OnCreate()
{
}

// �ؼ���ʼ�����
void ICtrl_XXXX_Impl::OnFinalCreate()
{
}

// ���ٿؼ�
void ICtrl_XXXX_Impl::OnDestroy()
{
}

// ���ƿؼ�
void ICtrl_XXXX_Impl::OnPaint(CDrawingBoard &DrawBoard)
{
}

// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
LRESULT ICtrl_XXXX_Impl::ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}
