#pragma once
#include "UiFeaturePropertyGrid.h"
#include "..\..\Inc\IUiFeatureKernel.h"
#include "..\..\Inc\IFeatureObject.h"

class CPropertyViewCtrl;
class CPropetryDialogGridProperty : public CUiFeaturePropertyGrid
{
public:
	CPropetryDialogGridProperty(const CString& strName, const COleVariant& varValueconst, CString& strInfo);
	virtual ~CPropetryDialogGridProperty();

	void InitDialogPropetry(CPropertyViewCtrl *pPropView, IUiFeatureKernel* pUiKernel, OBJECT_TYPE_ID ObjType);

protected:
	virtual BOOL HasButton() const { return TRUE; }
	virtual void OnClickButton(CPoint point);
	void ImageBaseDialog();
	void CursorBaseDialog();
	void FontBaseDialog();
	void RefreshMainView();

private:
	IUiFeatureKernel* m_pUiKernel;
	OBJECT_TYPE_ID m_ObjType;
	CPropertyViewCtrl *m_pPropViewList;
};
