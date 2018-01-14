//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "..\..\Inc\IPropertyImageBase.h"

class CGifImage;
class IPropertyImageBaseImpl : public IPropertyImageBase
{
public:
	IPropertyImageBaseImpl(IUiFeatureKernel* pUiKernel);
	virtual ~IPropertyImageBaseImpl();

	virtual bool GetActivePropetry();

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(xml_node* pXmlNode);
	// д��xml
	virtual bool AppendToXmlNode(xml_document &XmlStrObj, xml_node* pParentXmlNode);

//////////////////////////////////////////////////////////////////////////
	// Builderʹ�ú����������༭״̬��ʹ�ú���

//////////////////////////////////////////////////////////////////////////
	// ��������ͼ������ͼ����ⲿҪ�ͷţ����� IPropertySkinManager::DeleteImageBase() ���ɣ�Ҳ�ɲ��ͷţ��ں˻������һ���ͷ�
	virtual IPropertyImageBaseImpl* CreateThumbnailImage(SIZE sizeThumbnail);
	// ɾ������ͼ
	virtual bool DeleteThumbnailImage(IPropertyImageBase* pImgBase);

	// ����ʱ̬ʹ�ú���
	virtual void SetImageProp(IMAGE_BASE_PROP* pImgProp);
	virtual IMAGE_BASE_PROP* GetImageProp();
	virtual ZIP_FILE * GetZipFile();
	virtual bool SetZipFile(ZIP_FILE *pZipFile, bool bCreateMemDc);
	virtual SIZE GetImageSize();
	// �õ�ͼƬ���ڴ�DC
	virtual CDrawingImage* GetDrawingImage();
	// ����ͼƬ���ڴ�DC
	virtual CDrawingImage* CreateDrawingImage();
	// ��ʼ��Image����Image���ص��ڴ棬����Ĭ����û�м���ͼƬ���ݵ�
	virtual void InitImage();
	// ������������ʱ�����ƶ���
	virtual bool OnDrawAnimation();
	// ����ʹ�ü���
	virtual void AddUseCounts();
	// ��������
	virtual void SubtractUseCounts();
	// ȡ��ʹ�ü���
	virtual int GetUseCounts();

	// ����ͼƬ�����alpha����255����������alphaֵ������
	virtual bool DrawImage(CDrawingBoard &DstDc, RECT DstRct, int nAlpha = 255);
	virtual bool DrawImage(HDC hDc, RECT DstRct, int nAlpha = 255);
	// ����һ�����Կ�¡
	virtual bool Clone(IPropertyBase* pFromPropBase);

private:
	bool DrawImage_AllLaShen(CDrawingBoard &DstDc, RECT DstRct, int nAlpha);
	bool DrawImage_PingPu(CDrawingBoard &DstDc, RECT DstRct, int nAlpha);
	bool DrawImage_JggLaShen(CDrawingBoard &DstDc, RECT DstRct, int nAlpha);

	bool DrawImage_AllLaShen(HDC hDstDc, RECT DstRct, int nAlpha);
	bool DrawImage_PingPu(HDC hDstDc, RECT DstRct, int nAlpha);
	bool DrawImage_JggLaShen(HDC hDstDc, RECT DstRct, int nAlpha);

	bool SetXuLieDrawInTimer();
	bool InitDrawXuLieRect();

	bool SetGifDrawInTimer();
	void InitGifImage();

	bool InitStaticImage();
	void SafeDeleteDrawImage();

private:
	bool m_bIsDrawImgCreate;
	IMAGE_BASE_PROP m_ImageProp;
	CDrawingImage *m_pDrawImg;
	// ��ʹ�õļ�����
	int m_nUseCtns;
	// д��zip�ļ�����Ϣ
	ZIP_FILE *m_pZipFile;

//////////////////////////////////////////////////////////////////////////
	// ����ʹ�ò���
	RECT m_rctXuLieDraw;

//////////////////////////////////////////////////////////////////////////
	CGifImage *m_pGifImg;
	int m_nGifCurFrameTime;
	int m_nGifTimeCtns;

	bool m_bIsTimerDrawEnd;
};
