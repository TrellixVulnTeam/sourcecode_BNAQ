
#pragma once
#include "..\..\Inc\Control\ICtrlPanel.h"

class ICtrlPanelImpl : public ICtrlPanel
{
public:
	ICtrlPanelImpl(IUiFeatureKernel *pUiKernel);
	virtual ~ICtrlPanelImpl();

	virtual IPropertyImageBase* GetBackgroundImage();
	virtual bool SetBackgroundImage(IPropertyImageBase* pNewImageBase);
	// ���ñ���ͼ
	virtual bool SetBackgroundImage(LPCWSTR pszImagePath, bool bReload);
	// ���ö�������
	virtual void SetImageAnimation(PANEL_ANIMATION paType);
	virtual PANEL_ANIMATION GetImageAnimation();
	// �ظ���Ƥ�����е�ͼƬ
	virtual void SetToDefault(bool bRedraw, bool bDeleteOld = true);
	// �Ƿ���ʾ����ָ�뿪��
	virtual void SetIsShowCursor(bool bIsShow);
	// ���ñ���ͼ
	virtual bool SetBackgroundImage(HBITMAP hbmp, bool bReload);
	// ���ùؼ��֣�������������ʱ��������
	virtual void SetKey(LPCWSTR key);
	// getkey
	virtual LPCWSTR GetKey();

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
	// ���ƿؼ��Ķ����������Ҫ����ˢ�½��棬����true�����򷵻�false
	// �˺����ɶ�ʱ��������ÿ100���봥��һ��
	virtual bool OnDrawAnimation();
	// ���ÿؼ����
	virtual IPropertyCursor* OnSetCursor(POINT pt);

	// ������
	virtual void OnMouseEnter(POINT pt);
	// ����Ƴ�
	virtual void OnMouseLeave(POINT pt);
	// ���������
	virtual void OnLButtonDown(POINT pt);
	// ������˫��
	virtual void OnLButtonDbClick(POINT pt);
	// ������̧��
	virtual void OnLButtonUp(POINT pt);
	// ����Ҽ����
	virtual void OnRButtonDown(POINT pt);
	// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
	virtual LRESULT ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam);

private:
	void DrawPhotoFrame(CDrawingBoard &DrawBoard);
	bool CutImageData(CDrawingBoard &MarkDrawBoard, CDrawingBoard &DstDrawBoard);
private:
	IPropertyImage* m_pPropImage;
	IPropertyComboBox* m_pChangeImgAnimation;
	IPropertyImage* m_pPropPhotoFrameImg;
	IPropertyImage* m_pPropMarkPhotoFrameImg;

	IPropertyImageBase* m_pInSkinImgBase;
	IPropertyImageBase* m_pOldImgBase;
	IPropertyImageBase* m_pNewImgBase;
	IPropertyCursor* m_pPropCursor;

	int m_nNewImgAlpha;
	bool m_IsShowCursor;

	CStringW m_key;
};
