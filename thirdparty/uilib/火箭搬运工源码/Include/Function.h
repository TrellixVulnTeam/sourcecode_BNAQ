
#pragma once

#include <Windows.h>
#include "define.h"

// ȡ���ַ���ָ��λ�õ��ڴ�ָ��
inline void *MakeAddr(const void *addr, int len)
{
	return (BYTE *)addr + len * sizeof(WCHAR);
}

// �����ַ���ָ��ƫ�������ڴ��ֵ
inline void SetChar(void *addr, int offset, int val)
{
	*(WCHAR *)MakeAddr(addr, offset) = val;
}

// ȡ���ַ���ָ��ƫ�������ڴ��ֵ
inline DWORD GetChar(const void *addr, int offset)
{
	return *(WCHAR *)MakeAddr(addr, offset);
}

BOOL SetPrivilege(LPSTR pszPrivilege, BOOL bEnable);
int MakePath(WCHAR *dest, const WCHAR *dir, const WCHAR *file);
BOOL PathIsDir(WCHAR *pFile, BOOL &bIsDir);
BOOL FileSize(WCHAR *pFile, _int64 &nFileSize);
BOOL GetRootDir(WCHAR *pPath, WCHAR *pRetRoot);
BOOL GetFileFindData(WCHAR *pFile, WIN32_FIND_DATAW& FindDat);
UINT GetTickDiff(UINT nOldTickCount, UINT nNewTickCount);
BOOL GetDirSize(WCHAR *pPath, _int64 &nSize, int &nFileCnts, BOOL &bIsAbort);
