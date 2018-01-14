
#pragma once
#include "..\..\Inc\IZipFile.h"
#include "UiFeatureAes.h"
#include <atlstr.h>
using namespace ATL;


//////////////////////////////////////////////////////////////////////////
// �ļ�ͷ��ʾ3�ֽڣ�0xE1F2D3
// ��չ�ļ�ͷ
// ||��1�ֽڡ�Ƥ�����ṹ�汾�š�1�ֽڡ����볤�ȣ�������󳤶�255����N�ֽڡ�����||
// Ƥ���ļ��ļ��ṹ
// ||��4�ֽڡ��ļ�����----����1�ֽڡ��ļ�����----��2�ֽڡ������ļ����Ƴ���----�ļ�����----��4�ֽڡ�ԭ�ļ����ݳ���----��4�ֽڡ�ѹ�����ļ����ݳ���----ѹ���ļ����ݣ�||
// �ļ�β��ʾ3�ֽڣ�0xD1F2E3
//////////////////////////////////////////////////////////////////////////

// ����Ҫѹ�����ļ���׺��
typedef vector<CStringW>				NO_COMPRESS_FILE_VEC;

// ������Ϣ
struct VER_PASSWORD
{
	SKIN_VERSION skinVer;
	string strSrcPassword;
	int nDstLen;
	BYTE* pbyDstPassword;

	VER_PASSWORD()
	{
		skinVer = SV_0;
		strSrcPassword.clear();
		nDstLen = 0;
		pbyDstPassword = NULL;
	}
};


class IZipFileImpl : public IZipFile
{
public:
	IZipFileImpl();
	virtual ~IZipFileImpl();

	// ȡ��Ƥ�����汾��
	virtual SKIN_VERSION GetSkinFileVersion(LPCWSTR pZipFilePath, int &nPasswordLen);
	// ��֤�û�Ƥ��������
	virtual bool ChekUserPassword_SV_1(const char *pUserPassword, LPCWSTR pZipFilePath);

	virtual void RemoveFile(ZIP_FILE *pRemove);
	// ����һ�������ļ�����ǰ��zip�ļ��б���
	virtual ZIP_FILE* AppendLocalFileToZipFile(LPCWSTR pLocalFilePath, LPCWSTR pKeyFileName);

//// ��ȡzip�ļ� //////////////////////////////////////////////////////////////////////
	// ��ȡzip�ļ�
	virtual bool ReadZipFile(LPCWSTR pZipFilePath);
	// ȡ�ý�ѹ���ļ�����ļ��б�
	virtual ZIP_FILE_MAP *GetUnZipFileMap();
	virtual ZIP_FILE *FindUnZipFile(LPCWSTR pFileName);

	// �ڴ��Ż���Ҫ��ֻ����Ҫ�õ�zip�е�ͼƬ��ʱ��ż���ͼƬ
	virtual bool ReadZipFileItem(ZIP_FILE* pZipItem);

//// ����zip�ļ� //////////////////////////////////////////////////////////////////////
	// ��ʼ��zip�ļ���pSrcFileDir����Ҫѹ����Դ�ļ�Ŀ¼
	virtual bool WriteZipInit(LPCWSTR pSrcFileDir, LPCWSTR pSaveZipFile, SKIN_VERSION skinVer, char* pszPassword);
	// д��һ���ļ���pFilePath�������������WriteZipInit������pSrcFileDir·�������·��
	virtual bool WriteZipAppendFile(LPCWSTR pFileName, ZIP_FILE_TYPE ZipType);
	// д��һ��buffer��pFileName�������������WriteZipInit������pSrcFileDir·�������·��
	virtual bool WriteZipAppendBuffer(LPCWSTR pFileName, BYTE *pBuffer, int nBufferLen, ZIP_FILE_TYPE ZipType);
	// ��zip�ļ�д��һ������
	virtual bool WriteZipAppendStruct(ZIP_FILE *pNormalFile);
	virtual bool WriteZipEnd(bool bEntToClear);

//////////////////////////////////////////////////////////////////////////
	// ���Ժ���������ѹ����ļ�д�뱾��һ��ָ��Ŀ¼
	virtual void TestWriteUnZipFile(LPCWSTR pszOutDir);

	void Clear();
	bool FindFileName(LPCWSTR pFileName);

private:
	bool CreatePassword_SV_1(VER_PASSWORD &Password);
	bool GerPassword_SV_1(VER_PASSWORD &Password);
	bool ComparePassword_SV_1(VER_PASSWORD &Password);
	void ReleasePassword(VER_PASSWORD &Password);

private:
	ZIP_FILE_MAP m_ZipFileMap;
	// Ƥ��·��
	SKIN_FILE_LIST m_SkinFileList;

//////////////////////////////////////////////////////////////////////////
	// д��zip��
	CStringW m_strSrcFileDir;
	CStringW m_strSaveZipFile;

	VER_PASSWORD m_Password;
};
