#include "StdAfx.h"
#include <assert.h>
#include "..\..\Inc\IControlManager.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\ICommonFun.h"

#include "ICtrlScrollBarImpl.h"
#include "IScrollBarPainterImpl.h"

// ����
#define 		SCROLLBAR_NORMAL_IMAGE						"Normal"
#define 		SCROLLBAR_MOUSEHOVER_IMAGE					"MouseHover"
#define 		SCROLLBAR_LBUTTONDOWN_IMAGE					"LButtonDown"
#define 		SCROLLBAR_PRESUDO_MOUSEHOVER_IMAGE			"PresudoMouseHover"

ICtrlScrollBar::ICtrlScrollBar(IUiFeatureKernel *pUiKernel) : ICtrlInterface(pUiKernel) {}

ICtrlScrollBarImpl::ICtrlScrollBarImpl(IUiFeatureKernel *pUiKernel) : ICtrlScrollBar(pUiKernel)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_SCROLLBAR);

	for(int i = 0;i < SBStateNum; i++)
	{
		m_pPropVSBBGImages[i] = NULL;
		m_pPropVSBPageUpImages[i] = NULL;
		m_pPropVSBPageDownImages[i] = NULL;
		m_pPropVSBLineUpImages[i] = NULL;
		m_pPropVSBLineDownImages[i] = NULL;
		m_pPropVSBGotoBottomImages[i] = NULL;
		m_pPropVSBGotoTopImages[i] = NULL;
		m_pPropVSBThumbImages[i] = NULL;
		m_pPropHSBBGImages[i] = NULL;
		m_pPropHSBPageLeftImages[i] = NULL;
		m_pPropHSBPageRightImages[i] = NULL;
		m_pPropHSBLineLeftImages[i] = NULL;
		m_pPropHSBLineRightImages[i] = NULL;
		m_pPropHSBGotoRightImages[i] = NULL;
		m_pPropHSBGotoLeftImages[i] = NULL;
		m_pPropHSBThumbImages[i] = NULL;
	}

	m_pPainter = NULL;
	m_PropType = NULL;
	m_PropOwnerCtrlName = NULL;
	m_pOwnerCtrl = NULL;
	m_pPainter = NULL;
}

ICtrlScrollBarImpl::~ICtrlScrollBarImpl(void)
{
	if(NULL != m_pPainter)
	{
		delete m_pPainter;
		m_pPainter = NULL;
	}
}

bool ICtrlScrollBarImpl::EnableScrollBar(UINT nArrowFlags)
{
	assert(NULL != m_pPainter);

	if(NULL != m_pPainter)
	{
		return m_pPainter->EnableScrollBar(nArrowFlags);
	}
	else
	{
		return false;
	}
}

bool ICtrlScrollBarImpl::GetScrollBarInfo(PSCROLLBARINFO pScrollInfo) const
{
	assert(NULL != m_pPainter);

	if(NULL != m_pPainter)
	{
		return m_pPainter->GetScrollBarInfo(pScrollInfo);
	}
	else
	{
		return false;
	}
}

bool ICtrlScrollBarImpl::GetScrollInfo(LPSCROLLINFO lpScrollInfo,UINT nMask)
{
	assert(NULL != m_pPainter);

	if(NULL != m_pPainter)
	{
		return m_pPainter->GetScrollInfo(lpScrollInfo,nMask);
	}
	else
	{
		return false;
	}
}

int ICtrlScrollBarImpl::GetScrollLimit( )
{
	assert(NULL != m_pPainter);

	if(NULL != m_pPainter)
	{
		return m_pPainter->GetScrollLimit();
	}
	else
	{
		return 0;
	}
}

int ICtrlScrollBarImpl::GetScrollPos( ) const
{
	assert(NULL != m_pPainter);

	if(NULL != m_pPainter)
	{
		return m_pPainter->GetScrollPos();
	}
	else
	{
		return 0;
	}
}

void ICtrlScrollBarImpl::GetScrollRange(LPINT lpMinPos,LPINT lpMaxPos) const
{
	assert(NULL != m_pPainter);

	if(NULL != m_pPainter)
	{
		m_pPainter->GetScrollRange(lpMinPos,lpMaxPos);
	}
}

bool ICtrlScrollBarImpl::SetScrollInfo(LPSCROLLINFO lpScrollInfo,bool bRedraw)
{
	assert(NULL != m_pPainter);

	if(NULL != m_pPainter)
	{
		return m_pPainter->SetScrollInfo(lpScrollInfo,bRedraw);
	}
	else
	{
		return false;
	}
}

int ICtrlScrollBarImpl::SetScrollPos(int nPos,bool bRedraw)
{
	assert(NULL != m_pPainter);

	if(NULL != m_pPainter)
	{
		return m_pPainter->SetScrollPos(nPos,bRedraw);
	}
	else
	{
		return 0;
	}
}

void ICtrlScrollBarImpl::SetScrollRange(int nMinPos,int nMaxPos,bool bRedraw)
{
	assert(NULL != m_pPainter);

	if(NULL != m_pPainter)
	{
		return m_pPainter->SetScrollRange(nMinPos,nMaxPos,bRedraw);
	}
}

void ICtrlScrollBarImpl::ShowScrollBar(bool bShow)
{
	assert(NULL != m_pPainter);

	if(NULL != m_pPainter)
	{
		return m_pPainter->ShowScrollBar(bShow);
	}
}

void ICtrlScrollBarImpl::OnVScroll(UINT nSBCode, UINT nPos, IControlBase* pScrollBar)
{
	if(NULL != m_pOwnerCtrl)
	{
		m_pOwnerCtrl->OnVScroll(nSBCode,nPos,this);
	}
}

void ICtrlScrollBarImpl::OnHScroll(UINT nSBCode, UINT nPos, IControlBase* pScrollBar)
{
	if(NULL != m_pOwnerCtrl)
	{
		m_pOwnerCtrl->OnHScroll(nSBCode,nPos,this);
	}
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlScrollBarImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	//��ֱ������ͼƬ������                                                 
	IPropertyGroup* pVSBImagePropGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "VScrollBarImageGroup", "��ֱScrollBar��ͼƬ��");
	
	// ���ô�ֱ����������ͼƬ
	m_pPropVSBBGImages[SBStateNormal] = (IPropertyImage*)CreatePropetry(pVSBImagePropGroup, OTID_IMAGE, "Background", "����ͼƬ");
	m_pPropVSBBGImages[SBStatePresudoHover] = m_pPropVSBBGImages[SBStateDown] = m_pPropVSBBGImages[SBStateHover] = m_pPropVSBBGImages[SBStateNormal];
	
	// ���ô�ֱ������ThumbͼƬ
	IPropertyGroup* pVSBThumbImagePropGroup = (IPropertyGroup*)CreatePropetry(pVSBImagePropGroup, OTID_GROUP, "ThumbImageGroup", "ThumbͼƬ��");
	m_pPropVSBThumbImages[SBStateNormal] = (IPropertyImage*)CreatePropetry(pVSBThumbImagePropGroup, OTID_IMAGE, SCROLLBAR_NORMAL_IMAGE, "Normal״̬ʱ��ThumbͼƬ");
	m_pPropVSBThumbImages[SBStatePresudoHover] = (IPropertyImage*)CreatePropetry(pVSBThumbImagePropGroup, OTID_IMAGE, SCROLLBAR_PRESUDO_MOUSEHOVER_IMAGE, "����MouseHover״̬ʱ��ThumbͼƬ");
	m_pPropVSBThumbImages[SBStateHover] = (IPropertyImage*)CreatePropetry(pVSBThumbImagePropGroup, OTID_IMAGE, SCROLLBAR_MOUSEHOVER_IMAGE, "Hover״̬ʱ��ThumbͼƬ");
	m_pPropVSBThumbImages[SBStateDown] = (IPropertyImage*)CreatePropetry(pVSBThumbImagePropGroup, OTID_IMAGE, SCROLLBAR_LBUTTONDOWN_IMAGE, "LButtonDown״̬ʱ��ThumbͼƬ");

	// ���ô�ֱ������LineUpͼƬ
	IPropertyGroup* pVSBLineUpImagePropGroup = (IPropertyGroup*)CreatePropetry(pVSBImagePropGroup, OTID_GROUP, "LineUpImageGroup", "LineUpͼƬ��");
	m_pPropVSBLineUpImages[SBStateNormal] = (IPropertyImage*)CreatePropetry(pVSBLineUpImagePropGroup, OTID_IMAGE, SCROLLBAR_NORMAL_IMAGE, "Normal״̬ʱ��LineUpͼƬ");
	m_pPropVSBLineUpImages[SBStatePresudoHover] = (IPropertyImage*)CreatePropetry(pVSBLineUpImagePropGroup, OTID_IMAGE, SCROLLBAR_PRESUDO_MOUSEHOVER_IMAGE, "����MouseHover״̬ʱ��LineUpͼƬ");
	m_pPropVSBLineUpImages[SBStateHover] = (IPropertyImage*)CreatePropetry(pVSBLineUpImagePropGroup, OTID_IMAGE, SCROLLBAR_MOUSEHOVER_IMAGE, "MouseHover״̬ʱ��LineUpͼƬ");
	m_pPropVSBLineUpImages[SBStateDown] = (IPropertyImage*)CreatePropetry(pVSBLineUpImagePropGroup, OTID_IMAGE, SCROLLBAR_LBUTTONDOWN_IMAGE, "LButtonDown״̬ʱ��LineUpͼƬ");

	// ���ô�ֱ������LineDownͼƬ
	IPropertyGroup* pVSBLineDwonImagePropGroup = (IPropertyGroup*)CreatePropetry(pVSBImagePropGroup, OTID_GROUP, "LineDownImageGroup", "LineDownͼƬ��");
	m_pPropVSBLineDownImages[SBStateNormal] = (IPropertyImage*)CreatePropetry(pVSBLineDwonImagePropGroup, OTID_IMAGE, SCROLLBAR_NORMAL_IMAGE, "Normal״̬ʱ��LineDownͼƬ");
	m_pPropVSBLineDownImages[SBStatePresudoHover] = (IPropertyImage*)CreatePropetry(pVSBLineDwonImagePropGroup, OTID_IMAGE, SCROLLBAR_PRESUDO_MOUSEHOVER_IMAGE, "����MouseHover״̬ʱ��LineDownͼƬ");
	m_pPropVSBLineDownImages[SBStateHover] = (IPropertyImage*)CreatePropetry(pVSBLineDwonImagePropGroup, OTID_IMAGE, SCROLLBAR_MOUSEHOVER_IMAGE, "MouseHover״̬ʱ��LineDownͼƬ");
	m_pPropVSBLineDownImages[SBStateDown] = (IPropertyImage*)CreatePropetry(pVSBLineDwonImagePropGroup, OTID_IMAGE, SCROLLBAR_LBUTTONDOWN_IMAGE, "LButtonDown״̬ʱ��LineDownͼƬ");
		
	// ���ô�ֱ������PageUp�����ͼƬ
	m_pPropVSBPageUpImages[SBStateNormal] = m_pPropVSBPageUpImages[SBStatePresudoHover] = m_pPropVSBPageUpImages[SBStateHover] = NULL;
	m_pPropVSBPageUpImages[SBStateDown] = (IPropertyImage*)CreatePropetry(pVSBImagePropGroup, OTID_IMAGE, "PageUp", "PageUpͼƬ");

	// ���ô�ֱ������PageDown�����ͼƬ
	m_pPropVSBPageDownImages[SBStateNormal] = m_pPropVSBPageDownImages[SBStatePresudoHover] = m_pPropVSBPageDownImages[SBStateHover] = NULL;
	m_pPropVSBPageDownImages[SBStateDown] = (IPropertyImage*)CreatePropetry(pVSBImagePropGroup, OTID_IMAGE, "PageDown", "PageDownͼƬ");

	// ˮƽ������ͼƬ������                                     
	IPropertyGroup* pHSBImagePropGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "HScrollBarImageGroup", "ˮƽScrollBar��ͼƬ��");

	// ����ˮƽ����������ͼƬ
	m_pPropHSBBGImages[SBStateNormal] = (IPropertyImage*)CreatePropetry(pHSBImagePropGroup, OTID_IMAGE, "Background", "����ͼƬ");
	m_pPropHSBBGImages[SBStatePresudoHover] = m_pPropHSBBGImages[SBStatePresudoHover] = m_pPropHSBBGImages[SBStateDown] = m_pPropHSBBGImages[SBStateNormal];
	
	// ����ˮƽ������ThumbͼƬ
	IPropertyGroup* pHSBThumbImagePropGroup = (IPropertyGroup*)CreatePropetry(pHSBImagePropGroup, OTID_GROUP, "ThumbImageGroup", "ThumbͼƬ��");
	m_pPropHSBThumbImages[SBStateNormal] = (IPropertyImage*)CreatePropetry(pHSBThumbImagePropGroup, OTID_IMAGE, SCROLLBAR_NORMAL_IMAGE, "Normal״̬ʱ��ThumbͼƬ");
	m_pPropHSBThumbImages[SBStatePresudoHover] = (IPropertyImage*)CreatePropetry(pHSBThumbImagePropGroup, OTID_IMAGE, SCROLLBAR_PRESUDO_MOUSEHOVER_IMAGE, "����MouseHover״̬ʱ��ThumbͼƬ");
	m_pPropHSBThumbImages[SBStateHover] = (IPropertyImage*)CreatePropetry(pHSBThumbImagePropGroup, OTID_IMAGE, SCROLLBAR_MOUSEHOVER_IMAGE, "MouseHover״̬ʱ��ThumbͼƬ");
	m_pPropHSBThumbImages[SBStateDown] = (IPropertyImage*)CreatePropetry(pHSBThumbImagePropGroup, OTID_IMAGE, SCROLLBAR_LBUTTONDOWN_IMAGE, "LButtonDown״̬ʱ��ThumbͼƬ");

	// ����ˮƽ������LineLeftͼƬ
	IPropertyGroup* pHSBLineLeftImagePropGroup = (IPropertyGroup*)CreatePropetry(pHSBImagePropGroup, OTID_GROUP, "LineLeftImageGroup", "LineLeftͼƬ��");
	m_pPropHSBLineLeftImages[SBStateNormal] = (IPropertyImage*)CreatePropetry(pHSBLineLeftImagePropGroup, OTID_IMAGE, SCROLLBAR_NORMAL_IMAGE, "Normal״̬ʱ��LineLeftͼƬ");
	m_pPropHSBLineLeftImages[SBStatePresudoHover] = (IPropertyImage*)CreatePropetry(pHSBLineLeftImagePropGroup, OTID_IMAGE, SCROLLBAR_PRESUDO_MOUSEHOVER_IMAGE, "����MouseHover״̬ʱ��LineLeftͼƬ");
	m_pPropHSBLineLeftImages[SBStateHover] = (IPropertyImage*)CreatePropetry(pHSBLineLeftImagePropGroup, OTID_IMAGE, SCROLLBAR_MOUSEHOVER_IMAGE, "MouseHover״̬ʱ��LineLeftͼƬ");
	m_pPropHSBLineLeftImages[SBStateDown] = (IPropertyImage*)CreatePropetry(pHSBLineLeftImagePropGroup, OTID_IMAGE, SCROLLBAR_LBUTTONDOWN_IMAGE, "LButtonDown״̬ʱ��LineLeftͼƬ");
	
	// ����ˮƽ������LineRightͼƬ
	IPropertyGroup* pHSBLineRightImagePropGroup = (IPropertyGroup*)CreatePropetry(pHSBImagePropGroup, OTID_GROUP, "LineRightImageGroup", "LineRightͼƬ��");
	m_pPropHSBLineRightImages[SBStateNormal] = (IPropertyImage*)CreatePropetry(pHSBLineRightImagePropGroup, OTID_IMAGE, SCROLLBAR_NORMAL_IMAGE, "Normal״̬ʱ��LineRightͼƬ");
	m_pPropHSBLineRightImages[SBStatePresudoHover] = (IPropertyImage*)CreatePropetry(pHSBLineRightImagePropGroup, OTID_IMAGE, SCROLLBAR_PRESUDO_MOUSEHOVER_IMAGE, "����MouseHover״̬ʱ��LineRightͼƬ");
	m_pPropHSBLineRightImages[SBStateHover] = (IPropertyImage*)CreatePropetry(pHSBLineRightImagePropGroup, OTID_IMAGE, SCROLLBAR_MOUSEHOVER_IMAGE, "MouseHover״̬ʱ��LineRightͼƬ");
	m_pPropHSBLineRightImages[SBStateDown] = (IPropertyImage*)CreatePropetry(pHSBLineRightImagePropGroup, OTID_IMAGE, SCROLLBAR_LBUTTONDOWN_IMAGE, "LButtonDown״̬ʱ��LineRightͼƬ");
		
	// ����ˮƽ������PageLeftͼƬ
	m_pPropHSBPageLeftImages[SBStateNormal] = m_pPropHSBPageLeftImages[SBStatePresudoHover] = m_pPropHSBPageLeftImages[SBStateNormal] = m_pPropHSBPageLeftImages[SBStateHover] = NULL;
	m_pPropHSBPageLeftImages[SBStateDown] = (IPropertyImage*)CreatePropetry(pHSBImagePropGroup, OTID_IMAGE, "PageLeft", "PageLeftͼƬ");

	// ����ˮƽ������PageRightͼƬ
	m_pPropHSBPageRightImages[SBStateNormal] = m_pPropHSBPageRightImages[SBStatePresudoHover] = m_pPropHSBPageRightImages[SBStateHover] = NULL;
	m_pPropHSBPageRightImages[SBStateDown] = (IPropertyImage*)CreatePropetry(pHSBImagePropGroup, OTID_IMAGE, "PageRight", "PageRightͼƬ");

	// ���ͣ���ֱ��ˮƽ   
	m_PropType = (IPropertyComboBox*)CreatePropetry(NULL, OTID_COMBOBOX, "Type", "ScrollBar������");
	if(NULL !=m_PropType)
	{
		if (m_pWindowBase->IsDesignMode())
		{
			m_PropType->AppendString(L"Vertical");
			m_PropType->AppendString(L"Horizontal");

			if (m_PropType->GetSelect() < 0 || m_PropType->GetSelect() >= m_PropType->GetDataCounts())
				m_PropType->SetSelect(0);
		}
	}


	// ������ʹ���ߵ�Name     
	m_PropOwnerCtrlName = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "OwnerCtrlName", "ScrollBar��ʹ����");
	
	return true;
}

// ��ʼ���ؼ�
void ICtrlScrollBarImpl::OnCreate()
{
	PrepareScrollBarOwner();
	PrepareScrollBarPainter();
}

// �ؼ���ʼ�����
void ICtrlScrollBarImpl::OnFinalCreate()
{

}

// ���ٿؼ�
void ICtrlScrollBarImpl::OnDestroy()
{
	if(NULL != m_pPainter)
	{
		delete m_pPainter;
		m_pPainter = NULL;
	}
}

// ���ƿؼ�
void ICtrlScrollBarImpl::OnPaint(CDrawingBoard &DrawBoard)
{
	assert(NULL != m_pPainter);

	if(NULL != m_pPainter)
	{
		m_pPainter->OnPaint(DrawBoard);
	}
}

// ������
void ICtrlScrollBarImpl::OnMouseEnter(POINT pt)
{
	assert(NULL != m_pPainter);

	if(NULL != m_pPainter)
	{
		m_pPainter->OnMouseEnter(pt);
	}
}

// ����Ƴ�
void ICtrlScrollBarImpl::OnMouseLeave(POINT pt)
{
	assert(NULL != m_pPainter);

	if(NULL != m_pPainter)
	{
		m_pPainter->OnMouseLeave(pt);
	}
}
// ����ƶ�
void ICtrlScrollBarImpl::OnMouseMove(POINT pt)
{
	assert(NULL != m_pPainter);

	if(NULL != m_pPainter)
	{
		m_pPainter->OnMouseMove(pt);
	}
}

// ���������
void ICtrlScrollBarImpl::OnLButtonDown(POINT pt)
{
	assert(NULL != m_pPainter);

	if(NULL != m_pPainter)
	{
		m_pPainter->OnLButtonDown(pt);
	}
}

// ��������Ϣ
void ICtrlScrollBarImpl::OnMouseWheel(WPARAM wParam, LPARAM lParam)
{
	assert(NULL != m_pOwnerCtrl);

	if(NULL != m_pOwnerCtrl)
	{
		m_pOwnerCtrl->OnMouseWheel(wParam,lParam);
	}
}

// ������̧��
void ICtrlScrollBarImpl::OnLButtonUp(POINT pt)
{
	if(NULL != m_pPainter)
	{
		m_pPainter->OnLButtonUp(pt);
	}
}

void ICtrlScrollBarImpl::OnLButtonDbClick(POINT pt)
{
	if(NULL != m_pPainter)
	{
		m_pPainter->OnLButtonDbClick(pt);
	}
}

// �ؼ�ȡ�ý��㣬ͨ��Tab����ת������ؼ�
void ICtrlScrollBarImpl::OnSetFocus()
{

}

// �ؼ�ʧȥ����
void ICtrlScrollBarImpl::OnKillFocus()
{
	this->RedrawControl(true);
}

// �ƶ������ÿؼ�λ��
void ICtrlScrollBarImpl::OnSize()
{
	if(NULL != m_pPainter)
	{
		m_pPainter->OnSize();
	}
}

// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
LRESULT ICtrlScrollBarImpl::ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}

// ����϶��ؼ�
void ICtrlScrollBarImpl::OnMouseDragging(POINT pt)
{
	assert(NULL != m_pPainter);

	if(NULL != m_pPainter)
	{
		m_pPainter->OnMouseDragging(pt);
	}
}

// ���ƿؼ��Ķ����������Ҫ����ˢ�½��棬����true�����򷵻�false
// �˺����ɶ�ʱ��������ÿ100���봥��һ��
bool ICtrlScrollBarImpl::OnDrawAnimation()
{
	assert(NULL != m_pPainter);

	if(NULL != m_pPainter)
	{
		return m_pPainter->OnDrawAnimation();
	}
	else
	{
		return false;
	}
}

// Builderˢ�����ԣ��˺�����ֻҪ���¼��ؿؼ����Լ���
void ICtrlScrollBarImpl::OnBuilderRefreshProp(IPropertyBase* pPropBase)
{
	PrepareScrollBarOwner();
	PrepareScrollBarPainter();
}

void ICtrlScrollBarImpl::OnTimer(UINT nTimerId)
{
	assert(NULL != m_pPainter);

	if(NULL != m_pPainter)
	{
		return m_pPainter->OnTimer(nTimerId);
	}
}
void ICtrlScrollBarImpl::PrepareScrollBarPainter()
{
	if(NULL == m_pPainter)
	{
		m_pPainter =  new IScrollBarPainterImpl(this);
	}
	else
	{
		if(typeid(IScrollBarPainterImpl) != typeid(*m_pPainter))
		{
			delete m_pPainter;
			m_pPainter = new IScrollBarPainterImpl(this);
		}
	}

	if(NULL != m_pPainter)
	{
		m_pPainter->OnSize();
	}

}

void ICtrlScrollBarImpl::PrepareScrollBarOwner()
{	
	assert(NULL !=m_pWindowBase);
	if(NULL == m_pWindowBase)
		return;

	m_pOwnerCtrl = m_pWindowBase->GetControl(m_PropOwnerCtrlName->GetString());
}
