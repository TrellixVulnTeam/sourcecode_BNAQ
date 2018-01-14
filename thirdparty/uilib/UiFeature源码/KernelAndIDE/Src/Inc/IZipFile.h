
#pragma once
#include "CDrawingImage.h"
#include "IPropertyBase.h"
#include "IPropertyFontBase.h"

#include <string>
#include <map>
#include <vector>
#include <list>
using namespace std;

#include <atlstr.h>
using namespace ATL;

// ��������ַ�����
#define SKIN_FILE_PASSWORD_LEN			(255)

// zip�ļ��е��ļ�����
enum ZIP_FILE_TYPE
{
	ZFT_NORMAL		= 0,
	ZFT_IMAGE
};

// ѹ���ļ��б�
struct ZIP_FILE 
{
	WCHAR strFileName[MAX_PATH + 1];
	// �������ʹ�õĹ��õ��ڴ棬��ռ���ַ��ؼ���Ҳ����Ҫ�ͷţ�ϵͳ�������ͷ�
	LPCWSTR pstrSkinPath;
	BYTE byFileType;
	DWORD dwSrcFileLen;
	DWORD dwFileDataOffset;
	BYTE *pFileData;
	CDrawingImage DrawImg;

	ZIP_FILE()
	{
		memset(strFileName, 0, sizeof(strFileName));
		pstrSkinPath = NULL;
		byFileType = ZFT_NORMAL;
		dwSrcFileLen = dwFileDataOffset = 0;
		pFileData = NULL;
	};
};
// KEY:strFileName
typedef map<CStringW, ZIP_FILE*>		ZIP_FILE_MAP;
// ���ؼ��ص�Ƥ�����Ķ���
typedef list<CStringW>				SKIN_FILE_LIST;

// Ƥ�����汾��Ϣ
enum SKIN_VERSION
{
	// ����汾��
	SV_ERROR	= -1,
	// ���ϵİ汾��
	SV_0		= 0,
	// �ļ������Ƿ�unicode�İ汾
	SV_1		= 1,
	// �ļ�������unicode�İ汾��SV_1 �� SV_2 �汾�������������ȫһ���ģ����������㣺
	// 1. ѹ�������е��ļ����Ƶĸ�ʽ��һ����SV_2ʹ��Unicode
	// 2. ѹ�����е��ļ�ѹ����ʽ��һ����SV_2�Ķ�ȡ�ٶȸ���
	SV_2		= 2,
};

// һ��ѹ����Ƥ�����ļ�
class _declspec(novtable) IZipFile
{
public:

	// ȡ��Ƥ�����汾��
	virtual SKIN_VERSION GetSkinFileVersion(LPCWSTR pZipFilePath, int &nPasswordLen) = 0;
	// ��֤�û�Ƥ��������
	virtual bool ChekUserPassword_SV_1(const char *pUserPassword, LPCWSTR pZipFilePath) = 0;

	virtual void RemoveFile(ZIP_FILE *pRemove) = 0;
	// ����һ�������ļ�����ǰ��zip�ļ��б���
	virtual ZIP_FILE* AppendLocalFileToZipFile(LPCWSTR pLocalFilePath, LPCWSTR pKeyFileName) = 0;

//// ��ȡzip�ļ� //////////////////////////////////////////////////////////////////////
	// ��ȡzip�ļ�
	virtual bool ReadZipFile(LPCWSTR pZipFilePath) = 0;
	// ȡ�ý�ѹ���ļ�����ļ��б�
	virtual ZIP_FILE_MAP *GetUnZipFileMap() = 0;
	virtual ZIP_FILE *FindUnZipFile(LPCWSTR pFileName) = 0;

	// �ڴ��Ż���Ҫ��ֻ����Ҫ�õ�zip�е�ͼƬ��ʱ��ż���ͼƬ
	virtual bool ReadZipFileItem(ZIP_FILE* pZipItem) = 0;

//// ����zip�ļ� //////////////////////////////////////////////////////////////////////
	// ��ʼ��zip�ļ���pSrcFileDir����Ҫѹ����Դ�ļ�Ŀ¼
	virtual bool WriteZipInit(LPCWSTR pSrcFileDir, LPCWSTR pSaveZipFile, SKIN_VERSION skinVer, char* pszPassword) = 0;
	// д��һ���ļ���pFilePath�������������WriteZipInit������pSrcFileDir·�������·��
	virtual bool WriteZipAppendFile(LPCWSTR pFileName, ZIP_FILE_TYPE ZipType) = 0;
	// д��һ��buffer��pFileName�������������WriteZipInit������pSrcFileDir·�������·��
	virtual bool WriteZipAppendBuffer(LPCWSTR pFileName, BYTE *pBuffer, int nBufferLen, ZIP_FILE_TYPE ZipType) = 0;
	// ��zip�ļ�д��һ������
	virtual bool WriteZipAppendStruct(ZIP_FILE *pNormalFile) = 0;
	virtual bool WriteZipEnd(bool bEntToClear) = 0;
};

// һ��Ƥ��������Ϣ
struct SKIN_FILE_ITEM
{
	// Ƥ��·��
	CStringW strSkinFilePath;
	// Ƥ����ѹ��������
	IZipFile *pZipFileMgr;
	// ȡ��Ƥ������Ĭ�ϵ�������Ϣ
	IPropertyFontBase* pDefaultFontBase;
	// Resource.xml ������������ԵĶ���
	IPropertyBaseMapMap AllPropMap;
	// Controls.xml ���пؼ���������ԵĶ��У�KEY���ؼ��������ƣ��磺Button
	// �洢ÿһ���ؼ��ľ�������ԣ����пؼ����Զ������һ�� IPropertyGroup ��
	IPropertyBaseMapMap AllCtrlPropMap;
	// Windows.xml ���д��ڵ����Թ�����map
	// �洢ÿһ�����ڵľ�������ԣ����д������Զ������һ�� IPropertyGroup ��
	IPropertyBaseMap AllWindowPropMap;
	// ���ֶ��У�KEY��ObjectID���洢 IPropertyWindow IPropertyControl
	IPropertyBaseMap LayoutWindowMap;

	SKIN_FILE_ITEM()
	{
		strSkinFilePath = L"";
		pZipFileMgr = NULL;
		pDefaultFontBase = NULL;
		AllPropMap.clear();
		AllCtrlPropMap.clear();
		AllWindowPropMap.clear();
		LayoutWindowMap.clear();
	};
};
// Ƥ����map��KEY��Ƥ��������ȫ·��
typedef map<CStringW, SKIN_FILE_ITEM*>		SKIN_FILE_MAP;
