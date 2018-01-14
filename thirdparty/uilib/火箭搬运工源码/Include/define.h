
#pragma once

#pragma warning(disable:4311)
#pragma warning(disable:4312)

#include <windows.h>

// read write �����С 32MB
#define READ_WRITE_BUF_LEN					(32 * 1024 *1024)

// Ĭ��������С
#define DEFAULT_SECTOR_SIZE					(2048)

// �޳�������·��ǰ׺
#define PATH_LOCAL_PREFIX					(L"\\\\?\\")
#define PATH_LOCAL_PREFIX_LEN				(4)
#define PATH_UNC_PREFIX						(L"\\\\?\\UNC")
#define PATH_UNC_PREFIX_LEN					(7)

// WCHAR �Ŀ��
#define WCHAR_SIZE							(sizeof(WCHAR))

// ȡ�ð�ȫȨ��
#ifndef SE_CREATE_SYMBOLIC_LINK_NAME
#define SE_CREATE_SYMBOLIC_LINK_NAME		TEXT("SeCreateSymbolicLinkPrivilege")
#endif

// �� all_size �� blcok_size ����
#define ALIGN_SIZE(all_size, block_size)	((((all_size) + (block_size) -1) / (block_size)) * (block_size))

// FILE_FLAG_NO_BUFFERING ��ֹ�Դ��̽��л��崦���ļ�ֻ��д����̾��������
// NTFS ���ļ����� < 65535(64KB) �ֽ�ʱ��ʹ�� FILE_FLAG_NO_BUFFERING ��д���ļ���
#define NB_MIN_SIZE_NTFS					(64 * 1024)
// FAT ���ļ����� < 131072(128KB) �ֽ�ʱ��ʹ�� FILE_FLAG_NO_BUFFERING ��д���ļ���
#define NB_MIN_SIZE_FAT						(128 * 1024)

// ÿ�ζ�ȡ����д�����󳤶� 8388608(8MB)
#define MAX_TRANS_SIZE						(8 * 1024 * 1024)

// TBD ���ļ��ǵı�־ (VERIFY_MD5 | AUTOSLOW_IOLIMIT | SAMEDIR_RENAME)
#define OPEN_FILE_FLAGS						(0x02000110)

// �ȴ����в�������
#define CV_WAIT_TICK						(200)

// ��С������С
#define MIN_SECTOR_SIZE						(512)

// ����ȡ/д�볤�ȼ��ٵĳߴ�
#define REDUCE_SIZE							(1024 * 1024)

// NTFS֧�ֵ�����ļ�·������ 32768(32KB)
#define NTFS_MAX_PATH						(32768 + MAX_PATH)
#define MAX_PATH_EX							(MAX_PATH * 8)

#ifndef IS_SAVE_HANDLE
// �Ƿ�Ϊ��ȫ���
#define IS_SAVE_HANDLE(hHandle)				(((hHandle) != NULL) && ((hHandle) != INVALID_HANDLE_VALUE))
#endif

// ��ȫɾ����
#ifndef SAFE_DELETE_MEM_LIST
#define SAFE_DELETE_MEM_LIST(pMemBuf)		{ if ((pMemBuf) != NULL) { delete [] (pMemBuf); } (pMemBuf) = NULL; }
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(pMemBuf)				{ if ((pMemBuf) != NULL) { delete (pMemBuf); } (pMemBuf) = NULL; }
#endif

#ifndef SAFE_CLOSE_HANDLE
#define SAFE_CLOSE_HANDLE(hHandle)			{ if (IS_SAVE_HANDLE(hHandle)) { ::CloseHandle(hHandle); } (hHandle) = NULL; }
#endif

// �Ƿ�Ϊ�ļ���
#define IsDir(dwFileAttr)					(dwFileAttr & FILE_ATTRIBUTE_DIRECTORY)
#define IsReparse(dwFileAttr)				(dwFileAttr & FILE_ATTRIBUTE_REPARSE_POINT)
#define IsNoReparseDir(dwFileAttr)			(IsDir(dwFileAttr) && !IsReparse(dwFileAttr))


// ��������
enum DiskType
{
	// δ֪
	DT_NONE,
	// NTFS
	DT_NTFS,
	// FAT
	DT_FAT,
	// �������
	DT_NETWORK
};

enum Flags
{
	CREATE_OPENERR_FILE	=	0x00000001,
	USE_OSCACHE_READ	=	0x00000002,
	USE_OSCACHE_WRITE	=	0x00000004,
	PRE_SEARCH			=	0x00000008,
	SAMEDIR_RENAME		=	0x00000010,
	SKIP_EMPTYDIR		=	0x00000020,
	FIX_SAMEDISK		=	0x00000040,
	FIX_DIFFDISK		=	0x00000080,
	AUTOSLOW_IOLIMIT	=	0x00000100,
	WITH_ACL			=	0x00000200,
	WITH_ALTSTREAM		=	0x00000400,
	OVERWRITE_DELETE	=	0x00000800,
	OVERWRITE_DELETE_NSA=	0x00001000,
	FILE_REPARSE		=	0x00002000,
	DIR_REPARSE			=	0x00004000,
	COMPARE_CREATETIME	=	0x00008000,
	SERIAL_MOVE			=	0x00010000,
	SERIAL_VERIFY_MOVE	=	0x00020000,
	USE_OSCACHE_READVERIFY=	0x00040000,
	RESTORE_HARDLINK	=	0x00080000,
	DEL_BEFORE_CREATE	=	0x00200000,
	DELDIR_WITH_FILTER	=	0x00400000,
	LISTING				=	0x01000000,
	VERIFY_MD5			=	0x02000000,
	OVERWRITE_PARANOIA	=	0x04000000,
	VERIFY_FILE			=	0x08000000,
	LISTING_ONLY		=	0x10000000,
	REPORT_ACL_ERROR	=	0x20000000,
	REPORT_STREAM_ERROR	=	0x40000000
};
