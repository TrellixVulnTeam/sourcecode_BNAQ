#pragma once
#include "..\ICtrlInterface.h"	//�����ؼ��ӿ��ļ�

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_SPLITBAR							(L"SplitBar")

class _declspec(novtable) ICtrlSplitBar : public ICtrlInterface
{
public:
	ICtrlSplitBar(IUiFeatureKernel *pUiKernel);

	//���÷ָ����ؼ������ͣ�bHorzΪTRUEʱ��ʾˮƽ�ָ���������Ϊ��ֱ�ָ���
	virtual void SetSplitterType(bool bHorz) = 0;

	//����ˮƽ�ָ����������Сֵ��nTopMinΪ����������Сֵ,nBottomMinΪ�ײ��������Сֵ
	virtual void SetSplitterHorzMin(int nTopMin, int nBottomMin) = 0;

	//���ô�ֱ�ָ����������Сֵ,nLeftMinΪ���������Сֵ,nRightMinΪ�Ҳ��������Сֵ
	virtual void SetSplitterVertMin(int nLeftMin, int nRightMin) = 0;

	//��ȡ���������Сֵ
	virtual int GetTopLeftMin() = 0;

	//��ȡ�׻�������Сֵ
	virtual int GetBottomRightMin() = 0;

	//��ȡͼ��ĳ���
	virtual int GetGraphLength() = 0;

	//����ͼ��ĳ���
	virtual void SetGraphLength(int nGraphLength, bool bRedraw) = 0;

};