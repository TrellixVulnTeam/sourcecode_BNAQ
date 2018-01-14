
#pragma once
#include "..\..\Inc\Control\ICtrlRollAdvertisement.h"
#include <vector>
using namespace ATL;


class ICtrlRollAdvertisementImpl : public ICtrlRollAdvertisement
{
public:
	ICtrlRollAdvertisementImpl(IUiFeatureKernel *pUiKernel);
	virtual ~ICtrlRollAdvertisementImpl();

	virtual bool Clear();
	virtual bool AddAdvertisement(ROLL_ADVERTISEMENT_ITEM &AdvertisementeInfo);
	virtual bool IsEmpty();
	virtual void SetShowTime(int nTime);

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

	// ���ÿؼ����
	virtual IPropertyCursor* OnSetCursor(POINT pt);
	// ��ʱ��
	virtual void OnTimer(UINT nTimerId);
	// ���������
	virtual void OnLButtonDown(POINT pt);
	// ������̧��
	virtual void OnLButtonUp(POINT pt);
	// ����Ƿ������˿ؼ�ָ����RGN����Ĭ�Ϸ���true�������ؼ�����RGN����
	virtual bool OnCheckMouseInRgn(POINT pt, INT nMouseMsgId);
	// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
	virtual LRESULT ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam);

	// ������
	virtual void OnMouseEnter(POINT pt);
	// ����Ƴ�
	virtual void OnMouseLeave(POINT pt);


private:
	void BeginTimer();
	void EndTimer();
	void SetCurrentAdvertisementeInfo(int nNum);
	bool GetCurrentAdvertisementInfo(ROLL_ADVERTISEMENT_ITEM **ppAdvertisementeInfo);
	bool GetAdvertisementInfo(ROLL_ADVERTISEMENT_ITEM **ppAdvertisementeInfo, int nNum);
	void KillGunDongTimer();
	void BeginGunDongTimer();
	void DrawCurrentAdvertisement(CDrawingBoard &DrawBoard, RECT DrawRct);
	bool CopyStringData(WCHAR* pszFrom, WCHAR** ppszTo);
	bool ReleaseStringData(WCHAR** ppszRelease);

private:
	IPropertyCursor* m_pPropCursor;
	IPropertyFont* m_pPropFont_Normal;
	IPropertyFont* m_pPropFont_Hover;
	IPropertyFont* m_pPropFont_Down;
	IPropertyInt* m_pPropGunDongTimeCtns;

	ROLL_ADVERTISEMENT_VEC m_AdvertisementVec;
	int m_nOldAdvertisement;
	int m_nCurrentAdvertisenment;
	int m_nChangeTimerId;
	int m_nTimeCtns;
	bool m_bIsLButtonDown;
	RECT m_TextRct;

	int m_nAnimationTimerId;
	RECT m_OldAdvertisementRct;
	RECT m_CurrentAdvertisementRct;
};
