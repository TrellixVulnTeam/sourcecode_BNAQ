
#include "StdAfx.h"
#include "ICtrlAndroidListImpl.h"

ICtrlAndroidList::ICtrlAndroidList(IUiFeatureKernel *pUiKernel) : ICtrlInterface(pUiKernel) {}

ICtrlAndroidListImpl::ICtrlAndroidListImpl(IUiFeatureKernel *pUiKernel) : ICtrlAndroidList(pUiKernel)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_ANDROID_LIST);

	// �˿ؼ�����ҪTips���ԣ�����xml��Ϣ���Ż����ܣ�ɾ�����д��룬���±���ؼ����˿ؼ��ͻ�֧��ϵͳTips
	m_bHaveSysTipsProp = false;
}

ICtrlAndroidListImpl::~ICtrlAndroidListImpl()
{
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlAndroidListImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	return true;
}

// ��ʼ���ؼ�
void ICtrlAndroidListImpl::OnCreate()
{
}

// �ؼ���ʼ�����
void ICtrlAndroidListImpl::OnFinalCreate()
{
}

// ���ٿؼ�
void ICtrlAndroidListImpl::OnDestroy()
{
}

// ���ƿؼ�
void ICtrlAndroidListImpl::OnPaint(CDrawingBoard &DrawBoard)
{
}

// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
LRESULT ICtrlAndroidListImpl::ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}

// ��һ���ؼ������������ӿؼ���ʱ��ϵͳ�ᷢ�ʹ���������ӿؼ�����Ϣ
void ICtrlAndroidListImpl::OnCreateSubControl(bool bIsCreate)
{

}

// ���� ListItem �е�һ���ӿؼ������ڳ�����ؼ��ĵط�
void ICtrlAndroidListImpl::Gone(IControlBase* pGoneCtrl)
{

}

// ����/��ʾ ListItem �е�һ���ӿؼ����� gone �Ŀؼ�Ҳ������ʾ����������ռ��ԭ�����ڳ����Ŀռ�
void ICtrlAndroidListImpl::Visible(IControlBase* pCtrl, bool bVisible)
{

}

// �� UiFeatureBuilder ����Ƴ����� ListItem ��ģ�壬������ʱ̬һ��Ҫ��ʾ���ٸ�
int ICtrlAndroidListImpl::GetTempletColumnCount()
{
	return 1;
}

// �����б��Ƿ�Ϊ��
bool ICtrlAndroidListImpl::IsEmpty()
{
	return true;
}
