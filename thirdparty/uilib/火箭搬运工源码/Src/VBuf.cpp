
#include "stdafx.h"
#include "VBuf.h"

CVBuf::CVBuf(int nSize)
{
	Init();
	AllocBuf(nSize);
}

CVBuf::~CVBuf()
{
	FreeBuf();
}

void CVBuf::Init(void)
{
	m_pVBuf = NULL;
	m_nSize = 0;
}

BOOL CVBuf::AllocBuf(int nSize)
{
	BOOL bAlloc = false;
	if (nSize > 0 && m_pVBuf == NULL)
	{
		// ���������ַ�ռ��Ա��Ժ��ύ��
		m_pVBuf = (BYTE *)::VirtualAlloc(NULL, nSize + PAGE_SIZE, MEM_RESERVE, PAGE_READWRITE);
		if (m_pVBuf == NULL)
		{
			Init();
		}
		else
		{
			// ���ڴ����ָ���Ĵ���ҳ�ļ�(�����ڴ��ļ�)�з���һ����洢���� ������ʼ���������Ϊ0
			if (::VirtualAlloc(m_pVBuf, nSize, MEM_COMMIT, PAGE_READWRITE))
			{
				m_nSize = nSize;
				bAlloc = TRUE;
			}
			else
			{
				// ȡ��VirtualAlloc�ύ��ҳ
				::VirtualFree(m_pVBuf, nSize + PAGE_SIZE, MEM_DECOMMIT);
				Init();
			}
		}
	}

	return bAlloc;
}

BOOL CVBuf::LockBuf(void)
{
	// ָ�����ڴ�ҳ��ʼ�ձ����������ڴ��ϣ�����������������ҳ�ļ��У��Գ��õ��ڴ�ҳִ��������������Խ�ʡʱ��
	return ::VirtualLock(m_pVBuf, m_nSize);
}

void CVBuf::FreeBuf(void)
{
	if (m_pVBuf != NULL)
	{
		// �ͷ�ָ��ҳ
		::VirtualFree(m_pVBuf, 0, MEM_RELEASE);
	}

	Init();
}
