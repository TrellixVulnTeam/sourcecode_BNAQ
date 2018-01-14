#include "StdAfx.h"
#include "ICtrlLEDCtrlImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"


ICtrlLEDCtrl::ICtrlLEDCtrl(IUiFeatureKernel *pUiKernel) : ICtrlInterface(pUiKernel) {}

ICtrlLEDCtrlImpl::ICtrlLEDCtrlImpl(IUiFeatureKernel *pUiKernel) : ICtrlLEDCtrl(pUiKernel)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_LEDCTRL);

	// �˿ؼ�����ҪTips���ԣ�����xml��Ϣ���Ż����ܣ�ɾ�����д��룬���±���ؼ����˿ؼ��ͻ�֧��ϵͳTips
	m_bHaveSysTipsProp = false;

	m_pImageList = NULL;
	m_pStrText = NULL;
	m_pStrMapIndex = NULL;
	m_pImageListCount = NULL;

}

ICtrlLEDCtrlImpl::~ICtrlLEDCtrlImpl()
{

}

// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
LRESULT ICtrlLEDCtrlImpl::ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}

// ��ʼ���ؼ�
void ICtrlLEDCtrlImpl::OnCreate()
{
}

// �ؼ���ʼ�����
void ICtrlLEDCtrlImpl::OnFinalCreate()
{

	CreateMapIndex();
	CreateVecIndex();
}

// ���ٿؼ�
void ICtrlLEDCtrlImpl::OnDestroy()
{
}

// ���ƿؼ�
void ICtrlLEDCtrlImpl::OnPaint(CDrawingBoard &DrawBoard)
{

	if (m_vecIndex.size()==0 || m_mapIndex.size()==0)
		return;

	if (m_pImageList->GetDrawingImage()==NULL)
		return;

	if(NULL == m_pStrText || m_pStrText->GetLength()==0)
		return;


	int nSize = (int)m_vecIndex.size();
	RECT rcClient = this->GetClientRect();
	
	IMAGE_BASE_PROP* pImageProp = m_pImageList->GetImageProp();
	RECT imageRect = pImageProp->RectInImage;

	RECT rcItem = rcClient;
	rcItem.right = rcItem.left;
	rcItem.left = rcItem.right - RECT_WIDTH(imageRect);
	rcItem.bottom = RECT_HEIGHT(imageRect);
	
	for (int i = 0; i < nSize; i++)
	{
		::OffsetRect(&rcItem,RECT_WIDTH(imageRect),0);

		//�����ͼ�����򲢻���DrawBoard��ȥ��
		int nIndex = m_vecIndex[i];	//�����ǻ���ͼƬ�����е���һ��
		
		if (nIndex == -1 || nIndex > m_pImageListCount->GetValue())
		{
			return;
		}
		RECT rcPos = {0};
		rcPos.left = RECT_WIDTH(imageRect) * nIndex;
		rcPos.top = 0;
		rcPos.right = rcPos.left + RECT_WIDTH(imageRect);
		rcPos.bottom = rcPos.top + RECT_HEIGHT(imageRect);
		pImageProp->RectInImage = rcPos;
		m_pImageList->SetImageProp(pImageProp);

		m_pImageList->DrawImage(DrawBoard, rcItem);
	}
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlLEDCtrlImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	IPropertyGroup *pGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "LEDGroup", "LED��");
	m_pImageList = (IPropertyImage*)CreatePropetry(pGroup,OTID_IMAGE,"ImageList","һ���ɶ��Сͼ��ɵ�����ͼƬ",true);
	m_pStrText = (IPropertyString*)CreatePropetry(pGroup, OTID_STRING, "Text", "", true);
	m_pStrMapIndex = (IPropertyString*)CreatePropetry(pGroup, OTID_STRING, "MapIndex", "��ͼƬ����һһ��Ӧ���ַ�����", true);
	m_pImageListCount = (IPropertyInt*)CreatePropetry(pGroup, OTID_INT, "ImageListCount", "ͼƬһ���ж�����Сͼ���", true);
	return true;
}


void ICtrlLEDCtrlImpl::SetText(LPCWSTR pText, bool bRedraw)
{
	if(NULL == pText)
		return;

	if(NULL == m_pStrText)
		m_pStrText = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "Text", "", true);

	if (NULL == m_pStrText)
		return;

	m_vecIndex.clear();
	m_pStrText->SetString(pText);
	int nSize = wcslen(pText);
	for (int i = 0; i< nSize; i++)
	{
		if (m_mapIndex.count(pText[i]))
		{
			m_vecIndex.push_back(m_mapIndex[pText[i]]);
		}
		else
		{
			m_vecIndex.push_back(-1);
		}
	}

	RedrawControl(bRedraw);
}


void ICtrlLEDCtrlImpl::SetIndexMap(LPCWSTR pText)
{
	if (pText == NULL || wcslen(pText)==0)
		return;
	
	m_mapIndex.clear();
	
	int nSize = wcslen(pText);
	for (int i = 0; i < nSize; i++)
	{
		m_mapIndex[pText[i]] = i;
	}
}


SIZE ICtrlLEDCtrlImpl::GetAutoSize()
{
	SIZE sz = {0,0};
	if (m_pImageList == NULL)
	{
		return sz;
	}
	//��� = ÿ���ַ�ͼƬ�Ŀ��*�ַ���
	//�߶� = ÿ���ַ�ͼƬ�ĸ߶�
	IMAGE_BASE_PROP* pImageProp = m_pImageList->GetImageProp();
	RECT imageRect = pImageProp->RectInImage;
	int cx = RECT_WIDTH(imageRect) * m_vecIndex.size();
	int cy = RECT_HEIGHT(imageRect);
	sz.cx = cx;
	sz.cy = cy;
	return sz;
}


void ICtrlLEDCtrlImpl::CreateVecIndex()
{
	if(NULL == m_pStrText)
		return;
	
	m_vecIndex.clear();
	LPCWSTR pStrText = m_pStrText->GetString();
	int nSize = wcslen(pStrText);
	if (pStrText == NULL || nSize == 0)
		return;


	for (int i = 0; i< nSize; i++)
	{
		if (m_mapIndex.count(pStrText[i]))
		{
			m_vecIndex.push_back(m_mapIndex[pStrText[i]]);
		}
		else
		{
			m_vecIndex.push_back(-1);
		}
	}
}

void ICtrlLEDCtrlImpl::CreateMapIndex()
{
	if (NULL == m_pStrMapIndex)
		return;

	m_mapIndex.clear();

	LPCWSTR pMapText = m_pStrMapIndex->GetString();
	int nSize = wcslen(pMapText);
	if (pMapText == NULL || nSize == 0)
		return;

	for (int i = 0; i < nSize; i++)
	{
		m_mapIndex[pMapText[i]] = i;
	}

}
