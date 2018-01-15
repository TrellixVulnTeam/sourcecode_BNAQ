/*!
 @file		ISingleton.h
 @author    kongxilong
 @param		Email: hzkongxilong@163.org
 @param		Copyright (c) 2016 
 @date		2016-6-5
 @brief		�����ӿ�
	   
 */

#pragma once

#include <list>
#include <map>

/************************************************************

һ�ֲ������ĵ���ģʽ��ʵ�� �Ƚ�������ʵ�ַ�ʽ��ʹ��ģ�� 
����ģ���мд���̬���� ����dll�Ƿǳ���ʵ�ֵ� ��ʹ�ú�ʵ�ְ�

ʹ�õ���ģʽ�ķ�����
1��������������󲿷�ʹ�ú� DECLARE_SINGLETON_CLASS(CLASSNAME)
2����ʵ���ļ��г�ʼ����̬ȫ��ʵ���������� ʵ��GetInstance������SafeRelease����
*************************************************************/

#define SAFE_RELEASE(p)   {if(!(p)) delete (p); (p) = NULL;}


class  CLocker
{
public: 
	inline CLocker() 
	{ 
		m_hMutex = CreateMutex(NULL,FALSE,NULL); 
	} 
	inline ~CLocker() 
	{ 
		if (IsLock())
		{
			Unlock();
		}
		CloseHandle(m_hMutex); 
	} 
	inline void Lock() 
	{ 
		m_bLocked = TRUE; 
		WaitForSingleObject(m_hMutex, INFINITE); 	
	} 

	inline void Unlock() 
	{ 
		if(IsLock())
		{
			m_bLocked = FALSE; 
			ReleaseMutex(m_hMutex);
		}
	} 
	inline BOOL IsLock()
	{ 
		return m_bLocked == TRUE;
	}
private: 
	HANDLE m_hMutex;
	BOOL   m_bLocked;
};
/*!
 @brief ISingletonBase  ���е�������̳еĽӿ�
*/
struct  ISingletonBase
{
	virtual void OnStart() = 0;    //���ڳ�ʼ������ģʽʱ��ʼ��
	virtual void OnQuit() = 0;     //�����˳�����ʱ�������е�����
	virtual void SafeRelease() = 0;
	virtual int  GetSingletonID() = 0;
};

//�����Ĺ��������  ���ڴ˻����� ʵ�ֵ�������ʽ�Ĺ�����  
class  SingletonManagerBase
{
public:
	virtual void  RegisterSingleton(ISingletonBase* pISingletonInterface)
	{
		ASSERT(pISingletonInterface != NULL);
		//CSingleLock lock(&m_listMutex);
		m_listLocker.Lock();
		int id = pISingletonInterface->GetSingletonID();
		m_mapSingletons[id] = pISingletonInterface;
		m_listLocker.Unlock();
		//ע���ʱ���Զ����ó�ʼ������ 
		pISingletonInterface->OnStart();
	}
	virtual void  UnRegisterSingleton(ISingletonBase* pISingletonInterface)
	{
		ASSERT(pISingletonInterface != NULL);
		m_listLocker.Lock();
		std::map<int,ISingletonBase*>::iterator it = m_mapSingletons.begin();
		for(; it != m_mapSingletons.end(); ++it)
		{
			if(it->second == pISingletonInterface)
			{
				m_mapSingletons.erase(it);
				break;
			}
		}
		m_listLocker.Unlock();
		//ȡ��ע���ʱ���Զ����������� ��ɾ��������Դ
		pISingletonInterface->OnQuit();
		pISingletonInterface->SafeRelease();
	}
	virtual void  RemoveAllSingletons()
	{
		m_listLocker.Lock();
		std::map<int,ISingletonBase* >::iterator it = m_mapSingletons.begin();
		for(; it != m_mapSingletons.end(); ++it)
		{
			ISingletonBase* pSingletonClass = it->second;
			pSingletonClass->OnQuit();
			pSingletonClass->SafeRelease();
		}
        m_mapSingletons.clear();
		m_listLocker.Unlock();
	}
	virtual ISingletonBase*  GetSingletonByID(const int& id)
	{
		m_listLocker.Lock();
		std::map<int,ISingletonBase* >::iterator it = m_mapSingletons.begin();
		for(; it != m_mapSingletons.end(); ++it)
		{
			ISingletonBase* pSingletonClass = it->second;
			if(it->first == id)
			{
				return pSingletonClass;
			}
		}
		m_listLocker.Unlock();
		return NULL;
	}
private:
	std::map<int,ISingletonBase*>  m_mapSingletons;
	CLocker  m_listLocker;
};




#define DECLARE_SINGLETON_CLASS(CLASSNAME) \
public:                              \
	static CLASSNAME* GetInstance(); \
    virtual void SafeRelease();      \
private:                             \
	CLASSNAME(void){}                \
	CLASSNAME(const CLASSNAME&){}    \
	CLASSNAME& operator= (const CLASSNAME &){ return *this;} \
public:                              




