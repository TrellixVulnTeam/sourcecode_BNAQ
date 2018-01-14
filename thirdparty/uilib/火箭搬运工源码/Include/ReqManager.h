
#pragma once

#include <Windows.h>
#include "define.h"
#include "TList.h"

// ��������
enum Command
{
	// ���Կ�ʼд���ļ�
	BEGIN_WRITE_FILE,
	// д�ļ�
	WRITE_FILE,
	// �����ļ�����
	REQ_EOF
};

struct FileStat
{
	LARGE_INTEGER lnFileSize;
	FILETIME	ftCreationTime;
	FILETIME	ftLastAccessTime;
	FILETIME	ftLastWriteTime;
	DWORD		dwFileAttributes;
	HANDLE		hFile;
	DWORD		dwLastError;
	int			nFileStatMinSize;

	WCHAR		cFileName[MAX_PATH];
};

struct ReqHeader : public ListObj
{
	// ��������
	Command		HeaderCommand;
	BYTE		*pHeaderBuf;
	int			nHeaderBufSize;
	int			nHeaderReqSize;
	FileStat	FStat;
};

struct ReqBuf
{
	// �洢��д�����õĻ���VBuf
	BYTE		*pBuf;
	// �������������Ļ���ĳ���
	int			nBufSize;
	ReqHeader	*pReqHeader;
	int			nReqHeaderSize;
};


class TReqList : public CTList
{
public:
	TReqList(void) {};

	ReqHeader *TopObj(void)
	{
		return (ReqHeader *)CTList::TopObj();
	};

	ReqHeader *NextObj(ReqHeader *pReqObj)
	{
		return (ReqHeader *)CTList::NextObj(pReqObj);
	};
};
