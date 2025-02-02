#pragma once
#include "featurebaselist.h"
#include "..\..\Inc\IPropertyImage.h"
#include "..\..\Inc\IPropertyImageBase.h"
#include "..\..\Inc\IUiFeatureKernel.h"
#include "..\..\Inc\IPropertySkinManager.h"

class CImageBasePropEditDlg;
class CLocalImageList;
class CImageBaseNameList : public CFeatureBaseList
{
public:
	CImageBaseNameList(void);
	virtual ~CImageBaseNameList(void);

	void OnDeleteImageBaseProp();
	bool OnModifyImageBaseProp(CString strName);
	bool OnCreateImageBaseProp(CString strName);
	IPropertyImageBase * GetSelectImageBase(int &nSeleItem);
	void Init(IUiFeatureKernel* pUiKernel, CImageBasePropEditDlg *pImgBaseDlg, CLocalImageList* pLocalImg, IPropertyImage* pParentImgProp);
	void RefreshImageBaseShow();

public:
	IPropertyImageBase* m_pSelectImgBaseProp;

protected:
	virtual COLORREF OnGetCellBkColor(int nRow, int nColum);
	void LoadImageBaseProp();
	virtual void OnSelectItem();

private:
	IUiFeatureKernel* m_pUiKernel;
	CImageBasePropEditDlg *m_pImgBaseDlg;
	CLocalImageList* m_pLocalImgList;
	IPropertyImage* m_pParentImgProp;
};
