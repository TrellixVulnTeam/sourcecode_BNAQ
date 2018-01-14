//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "..\..\Inc\IPropertyImage.h"

class IPropertyImageImpl : public IPropertyImage
{
public:
	IPropertyImageImpl(IUiFeatureKernel* pUiKernel);
	virtual ~IPropertyImageImpl();

	virtual void SetActivePropetry(bool bIsActive);
	virtual bool GetActivePropetry();

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(xml_node* pXmlNode);
	// д��xml
	virtual bool AppendToXmlNode(xml_document &XmlStrObj, xml_node* pParentXmlNode);

//////////////////////////////////////////////////////////////////////////
	// ��������ͼ������ͼ����ⲿҪ�ͷţ����� DeleteThumbnailImage �� IPropertySkinManager::DeleteThumbnailImage() ���ɣ�Ҳ�ɲ��ͷţ��ں˻������һ���ͷ�
	virtual IPropertyImageBase* CreateThumbnailImage(SIZE sizeThumbnail);
	// ɾ������ͼ
	virtual bool DeleteThumbnailImage(IPropertyImageBase* pImgBase);

	virtual IPropertyImageBase* GetImageBaseProp();
	virtual void SetImageBaseProp(IPropertyImageBase* pNewImgBase);
	virtual const WCHAR * GetImageBaseName();
	virtual SIZE GetImageSize();
	virtual void SetImageProp(IMAGE_BASE_PROP* pImgProp);
	virtual IMAGE_BASE_PROP* GetImageProp();
	// �õ�ͼƬ���ڴ�DC
	virtual CDrawingImage* GetDrawingImage();
	// ����ͼƬ���ڴ�DC
	virtual CDrawingImage* CreateDrawingImage();
	virtual void SetNeedRedraw();
	// ��ʼ��Image����Image���ص��ڴ棬����Ĭ����û�м���ͼƬ���ݵ�
	virtual void InitImage();
	// ������������ʱ�����ƶ���
	virtual bool OnDrawAnimation();

	// ����ͼƬ�����alpha����255����������alphaֵ������
	virtual bool DrawImage(CDrawingBoard &DstDc, RECT DstRct, int nAlpha = 255);
	virtual bool DrawImage(HDC hDc, RECT DstRct, int nAlpha = 255);
	// ����һ�����Կ�¡
	virtual bool Clone(IPropertyBase* pFromPropBase);
};
