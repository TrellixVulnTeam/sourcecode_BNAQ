
#pragma once
#include "..\ICtrlInterface.h"


// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_ROLL_ADVERTISEMENT						(L"RollAdvertisement")

// NoticeLable �ؼ��򴰿ڷ��͵���Ϣ
enum CTRL_MSG_ROLL_ADVERTISEMENT
{
	CM_ROLL_ADVERTISEMENT_BASE	= 0x10026000,
	// WPARAM ����Ϊ��ROLL_ADVERTISEMENT ��ָ��
	CM_ROLL_ADVERTISEMENT_DOWN,
	// WPARAM ����Ϊ��ROLL_ADVERTISEMENT ��ָ��
	CM_ROLL_ADVERTISEMENT_UP,
};

struct ROLL_ADVERTISEMENT_ITEM
{
	int nId;
	int nConfActive;
	WCHAR* pStrShowInfo;
	WCHAR* pStrData;
	WPARAM wParam;

	ROLL_ADVERTISEMENT_ITEM()
	{
		nId = 0;
		nConfActive = 0;
		pStrShowInfo = pStrData = NULL;
		wParam = NULL;
	};
};
typedef vector<ROLL_ADVERTISEMENT_ITEM*> ROLL_ADVERTISEMENT_VEC;


class ICtrlRollAdvertisement : public ICtrlInterface
{
public:
	ICtrlRollAdvertisement(IUiFeatureKernel *pUiKernel);
	// ������й�����Ϣ
	virtual bool Clear() = 0;
	// ���һ��������Ϣ
	virtual bool AddAdvertisement(ROLL_ADVERTISEMENT_ITEM &AdvertisementeInfo) = 0;
	// ��ǰ���������Ƿ�Ϊ��
	virtual bool IsEmpty() = 0;
	// ���ù�����ʾ��ʱ�䣬��λ��
	virtual void SetShowTime(int nTime) = 0;
};
