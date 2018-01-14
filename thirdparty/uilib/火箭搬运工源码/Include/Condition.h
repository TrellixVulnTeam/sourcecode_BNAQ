
#pragma once

#include "define.h"
#include <windows.h>
#include "TList.h"

enum WaitEvent
{
	CLEAR_EVENT = 0,
	DONE_EVENT,
	WAIT_EVENT,
	ONE_PATH_OBJ_END,
	ALL_FILE_END,
	PAUSE_OP
};

struct EventObj : public ListObj
{
	HANDLE hEvents;
	WaitEvent EventsType;
};

class CEventList : public CTList
{
public:
	CEventList(void) {};
	~CEventList(void) { ClearAll(); };

	EventObj *TopObj(void)
	{
		return (EventObj *)CTList::TopObj();
	};

	EventObj *NextObj(EventObj *pReqObj)
	{
		return (EventObj *)CTList::NextObj(pReqObj);
	};

	EventObj *NewEventObj(WaitEvent EventsType, BOOL bManualReset = FALSE)
	{
		EventObj *pNewObj = new EventObj;
		if (pNewObj != NULL)
		{
			// ���¼���һ���ȴ��߳��ͷ��Ժ�ϵͳ�����Զ����¼�״̬��ԭΪ���ź�״̬����ʼ״̬Ϊ���ź�״̬
			pNewObj->hEvents = ::CreateEvent(NULL, bManualReset, FALSE, NULL);
			if (pNewObj->hEvents == NULL)
			{
				SAFE_DELETE(pNewObj);
			}
			else
			{
				pNewObj->EventsType = EventsType;
				this->AddObj(pNewObj);
			}
		}

		return pNewObj;
	};

	void DelEventObj(EventObj *pReqObj)
	{
		if (pReqObj != NULL)
		{
			this->DelObj(pReqObj);
			SAFE_CLOSE_HANDLE(pReqObj->hEvents);
			SAFE_DELETE(pReqObj);
		}
	};

	void ClearAll()
	{
		while (!this->IsEmpty())
		{
			EventObj *pPathObj = this->TopObj();
			DelEventObj(pPathObj);
		}
	};
};

class Condition
{
protected:
	// �����¼��б�
	CEventList m_EventList;
	// �����ļ����������¼�
	EventObj *m_pOnePathEndEvent;
	// �����ļ����������¼�
	EventObj *m_pAllFileEndEvent;
	// ��ͣ�¼�
	EventObj *m_pPauseEvent;

	HANDLE *m_ahEvents;
	WaitEvent *m_aWaitEventsType;

	CRITICAL_SECTION m_cs;
	int m_nMaxThreads;
	int m_nWaitCnt;

public:
	Condition(void);
	~Condition();

	BOOL Initialize(int _nMaxThreads);
	void UnInitialize(void);

	void Lock(void)
	{
		::EnterCriticalSection(&m_cs);
	};

	void UnLock(void)
	{
		::LeaveCriticalSection(&m_cs);
	};

	int WaitThreads()
	{
		return m_nWaitCnt;
	};

	int IsWait()
	{
		return (m_nWaitCnt ? TRUE : FALSE);
	};

	void DetachThread()
	{
		m_nMaxThreads--;
	};

	int  MaxThreads()
	{
		return m_nMaxThreads;
	};

	BOOL WaitEnd(WaitEvent EventType, BOOL &bIsAbort);
	void NotifyEnd(WaitEvent EventType);

	BOOL WaitPause(BOOL &bIsAbort);
	void NotifyPause(BOOL bIsPause);

	BOOL Wait(DWORD dwTimeout = INFINITE);
	void Notify(void);
};
