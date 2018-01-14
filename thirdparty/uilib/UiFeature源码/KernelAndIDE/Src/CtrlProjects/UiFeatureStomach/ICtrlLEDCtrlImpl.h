#pragma once
#include "..\..\Inc\Control\ICtrlLEDCtrl.h"

class ICtrlLEDCtrlImpl : public ICtrlLEDCtrl
{
public:
	ICtrlLEDCtrlImpl(IUiFeatureKernel *pUiKernel);
	virtual ~ICtrlLEDCtrlImpl();

	virtual void SetText(LPCWSTR pText, bool bRedraw);
	virtual void SetIndexMap(LPCWSTR pText);
	virtual SIZE GetAutoSize();

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
	// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
	virtual LRESULT ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam);

private:
	//��ʼ������
	virtual void CreateVecIndex();
	virtual void CreateMapIndex();

private:
	map<TCHAR,int>	  m_mapIndex;	//�ַ�����ͼƬ������ӳ��
	vector<int>       m_vecIndex;   //��ǰҪ��ʾ����������

	IPropertyImage*	  m_pImageList;			//һ���ɶ��Сͼ��ɵ�����ͼƬ
	IPropertyString*  m_pStrText;			//Ҫ��ʾ��LED����
	IPropertyString*  m_pStrMapIndex;		//���磺0123456789:-
	IPropertyInt*	  m_pImageListCount;	//ͼƬ������һ���ж�����Сͼ��϶���

};