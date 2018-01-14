
#include "stdafx.h"
#include "IZipFileImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IUiFeatureKernel.h"

static BYTE s_byBeginSign[3] = { 0xE1, 0xF2, 0xD3 };
static BYTE s_byEndSign[3] = { 0xD1, 0xF2, 0xE3 };

IZipFileImpl::IZipFileImpl()
{
	m_ZipFileMap.clear();
	m_SkinFileList.clear();
}

IZipFileImpl::~IZipFileImpl()
{
	Clear();
	m_SkinFileList.clear();
}

void IZipFileImpl::Clear()
{
	ReleasePassword(m_Password);
	for (ZIP_FILE_MAP::iterator pZipItem = m_ZipFileMap.begin(); pZipItem != m_ZipFileMap.end(); pZipItem++)
	{
		ZIP_FILE* pZip = pZipItem->second;
		if (pZip != NULL)
		{
			SAFE_DELETE_LIST(pZip->pFileData);
			SAFE_DELETE(pZip);
		}
	}
	m_ZipFileMap.clear();
}

void IZipFileImpl::RemoveFile(ZIP_FILE *pRemove)
{
	if (m_ZipFileMap.size() <= 0 || pRemove == NULL)
		return;

	for (ZIP_FILE_MAP::iterator pZipItem = m_ZipFileMap.begin(); pZipItem != m_ZipFileMap.end(); pZipItem++)
	{
		ZIP_FILE* pZip = pZipItem->second;
		if (pZip == pRemove)
		{
			SAFE_DELETE_LIST(pZip->pFileData);
			SAFE_DELETE(pZip);
			m_ZipFileMap.erase(pZipItem);
			break;
		}
	}

	if (m_ZipFileMap.size() <= 0)
		m_ZipFileMap.clear();
}

// ��ʼ��zip�ļ���pSrcFileDir����Ҫѹ����Դ�ļ�Ŀ¼
bool IZipFileImpl::WriteZipInit(LPCWSTR pSrcFileDir, LPCWSTR pSaveZipFile, SKIN_VERSION skinVer, char* pszPassword)
{
	Clear();
	if (pSrcFileDir == NULL || pSaveZipFile == NULL || wcslen(pSrcFileDir) <= 0 || wcslen(pSaveZipFile) <= 0)
		return false;

	m_strSrcFileDir = pSrcFileDir;
	m_strSaveZipFile = pSaveZipFile;

	WCHAR pEnd = m_strSrcFileDir[m_strSrcFileDir.GetLength() - 1];
	if (pEnd != '\\')
		m_strSrcFileDir += L"\\";

//////////////////////////////////////////////////////////////////////////
	// ����Ƥ��������
	ReleasePassword(m_Password);
	m_Password.skinVer = skinVer;
	m_Password.strSrcPassword = "";
	if (pszPassword != NULL && strlen(pszPassword) > 0)
		m_Password.strSrcPassword = pszPassword;

	if (m_Password.skinVer >= SV_1 && m_Password.skinVer <= SV_2 && m_Password.strSrcPassword.size() > 0)
		return CreatePassword_SV_1(m_Password);

	return true;
}

bool IZipFileImpl::FindFileName(LPCWSTR pFileName)
{
	if (pFileName == NULL)
		return false;

	for (ZIP_FILE_MAP::iterator pZipItem = m_ZipFileMap.begin(); pZipItem != m_ZipFileMap.end(); pZipItem++)
	{
		ZIP_FILE* pZipFile = pZipItem->second;
		if (pZipFile == NULL)
			continue;

		if (lstrcmpiW(pZipFile->strFileName, pFileName) == 0)
			return true;
	}

	return false;
}

// ��zip�ļ�д��һ������
bool IZipFileImpl::WriteZipAppendStruct(ZIP_FILE *pNormalFile)
{
	if (pNormalFile == NULL)
		return false;

	return WriteZipAppendBuffer(pNormalFile->strFileName, pNormalFile->pFileData, pNormalFile->dwSrcFileLen, (ZIP_FILE_TYPE)pNormalFile->byFileType);
}

// д��һ��buffer
bool IZipFileImpl::WriteZipAppendBuffer(LPCWSTR pFileName, BYTE *pBuffer, int nBufferLen, ZIP_FILE_TYPE ZipType)
{
	if (pFileName == NULL || wcslen(pFileName) <= 0 || pBuffer == NULL)
		return false;

	if (nBufferLen <= 0)
		return true;

	if (FindFileName(pFileName))
		return false;

	ZIP_FILE *pFileItem = new ZIP_FILE;
	if (pFileItem == NULL)
		return false;

	memset(pFileItem->strFileName, 0, sizeof(pFileItem->strFileName));
	wcscpy_s(pFileItem->strFileName, MAX_PATH, pFileName);
	pFileItem->dwSrcFileLen = nBufferLen;
	pFileItem->byFileType = (BYTE)ZipType;
	pFileItem->pFileData = NULL;
	pFileItem->pFileData = new BYTE[nBufferLen];
	if (pFileItem->pFileData == NULL)
	{
		SAFE_DELETE(pFileItem);
		return false;
	}

	memcpy(pFileItem->pFileData, pBuffer, nBufferLen);

	m_ZipFileMap.insert(pair<CStringW, ZIP_FILE*>(pFileItem->strFileName, pFileItem));
	return true;
}

// д��һ���ļ���pFilePath�������������WriteZipInit������pSrcFileDir·�������·��
bool IZipFileImpl::WriteZipAppendFile(LPCWSTR pFileName, ZIP_FILE_TYPE ZipType)
{
	if (pFileName == NULL || wcslen(pFileName) <= 0 || m_strSrcFileDir.GetLength() <= 0 || m_strSaveZipFile.GetLength() <= 0)
		return false;

	if (FindFileName(pFileName))
		return false;

	CStringW strPath = m_strSrcFileDir;
	strPath += pFileName;

	WIN32_FILE_ATTRIBUTE_DATA FileAttr;
	if (!::GetFileAttributesExW(strPath, GetFileExInfoStandard, &FileAttr))
		return false;

	FILE *pFile = NULL;
	_wfopen_s(&pFile, strPath, L"rb");
	if (pFile == NULL)
		return false;

	BYTE *pReadBuf = new BYTE[FileAttr.nFileSizeLow];
	if (pReadBuf == NULL)
	{
		fclose(pFile);
		return false;
	}

	int nReadCtns = 0;
	while (nReadCtns < (int)FileAttr.nFileSizeLow)
	{
		BYTE *pRead = pReadBuf + nReadCtns;
		int nNeedRead = FileAttr.nFileSizeLow - nReadCtns;

		int nRead = fread_s(pRead, nNeedRead, 1, nNeedRead, pFile);
		nReadCtns += nRead;
	}

	if (nReadCtns != (int)FileAttr.nFileSizeLow)
	{
		SAFE_DELETE_LIST(pReadBuf);
		fclose(pFile);
		return false;
	}

	ZIP_FILE *pFileItem = new ZIP_FILE;
	if (pFileItem == NULL)
	{
		SAFE_DELETE_LIST(pReadBuf);
		fclose(pFile);
		return false;
	}

	pFileItem->byFileType = (BYTE)ZipType;
	memset(pFileItem->strFileName, 0, sizeof(pFileItem->strFileName));
	wcscpy_s(pFileItem->strFileName, MAX_PATH, pFileName);
	pFileItem->dwSrcFileLen = FileAttr.nFileSizeLow;
	pFileItem->pFileData = pReadBuf;

	m_ZipFileMap.insert(pair<CStringW, ZIP_FILE*>(pFileItem->strFileName, pFileItem));

	fclose(pFile);
	return true;
}

bool IZipFileImpl::WriteZipEnd(bool bEntToClear)
{
	if (m_ZipFileMap.size() <= 0)
		return false;

	FILE *pFile = NULL;
	_wfopen_s(&pFile, m_strSaveZipFile, L"wb");
	if (pFile == NULL)
		return false;
	
	// ---д���ļ�ͷ
	int nWriteLen = fwrite(s_byBeginSign, 1, 3, pFile);
	if (nWriteLen != 3)
	{
		fclose(pFile);
		return false;
	}

	// ---д��Ƥ�����汾��
	BYTE byData = SV_2;
	nWriteLen = fwrite(&byData, 1, 1, pFile);
	if (nWriteLen != 1)
	{
		fclose(pFile);
		return false;
	}

	// ---д�����볤��
	byData = (BYTE)m_Password.nDstLen;
	nWriteLen = fwrite(&byData, 1, 1, pFile);
	if (nWriteLen != 1)
	{
		fclose(pFile);
		return false;
	}

	// ---д������
	if (m_Password.nDstLen > 0)
	{
		nWriteLen = fwrite(m_Password.pbyDstPassword, 1, m_Password.nDstLen, pFile);
		if (nWriteLen != m_Password.nDstLen)
		{
			fclose(pFile);
			return false;
		}
	}

	// д�����ļ�����
	DWORD dwFileCtns = m_ZipFileMap.size();
	nWriteLen = fwrite(&dwFileCtns, 1, sizeof(DWORD), pFile);
	if (nWriteLen != sizeof(DWORD))
	{
		fclose(pFile);
		return false;
	}

	// д�뵥���ļ�
	for (ZIP_FILE_MAP::iterator pZipItem = m_ZipFileMap.begin(); pZipItem != m_ZipFileMap.end(); pZipItem++)
	{
		ZIP_FILE* pZip = pZipItem->second;
		if (pZip == NULL || pZip->pFileData == NULL || pZip->dwSrcFileLen <= 0 || wcslen(pZip->strFileName) <= 0)
			continue;

		// �ļ�����
		nWriteLen = fwrite(&(pZip->byFileType), 1, sizeof(BYTE), pFile);
		if (nWriteLen != sizeof(BYTE))
		{
			fclose(pFile);
			return false;
		}

		// �ļ����Ƴ���
		SHORT sNameLen = wcslen(pZip->strFileName) * sizeof(WCHAR);
		nWriteLen = fwrite(&sNameLen, 1, sizeof(SHORT), pFile);
		if (nWriteLen != sizeof(SHORT))
		{
			fclose(pFile);
			return false;
		}

		// �ļ���
		nWriteLen = fwrite(pZip->strFileName, 1, sNameLen, pFile);
		if (nWriteLen != sNameLen)
		{
			fclose(pFile);
			return false;
		}

		// ԭ�ļ����ݳ���
		nWriteLen = fwrite(&(pZip->dwSrcFileLen), 1, sizeof(DWORD), pFile);
		if (nWriteLen != sizeof(DWORD))
		{
			fclose(pFile);
			return false;
		}

		// �ļ�����
		nWriteLen = 0;
		while (nWriteLen < (int)(pZip->dwSrcFileLen))
		{
			BYTE *pWrite = pZip->pFileData + nWriteLen;
			int nNeedWrite = pZip->dwSrcFileLen - nWriteLen;
			int nWrite = fwrite(pWrite, 1, nNeedWrite, pFile);
			nWriteLen += nWrite;
		}

		if (nWriteLen != (int)pZip->dwSrcFileLen)
		{
			fclose(pFile);
			return false;
		}
	}

	// ---д���ļ�β
	nWriteLen = fwrite(s_byEndSign, 1, 3, pFile);
	if (nWriteLen != 3)
	{
		fclose(pFile);
		return false;
	}

	fclose(pFile);
	if (bEntToClear)
		Clear();
	return true;
}

//////////////////////////////////////////////////////////////////////////
// ��ȡzip�ļ�
bool IZipFileImpl::ReadZipFile(LPCWSTR pZipFilePath)
{
	Clear();
	if (pZipFilePath == NULL || wcslen(pZipFilePath) <= 0)
		return false;

	FILE *pFile = NULL;
	_wfopen_s(&pFile, pZipFilePath, L"rb");
	if (pFile == NULL)
		return false;

	int nFileOffset = 0;
	int nReadLen = 0;

	// �����ļ�ͷ
	if (fseek(pFile, 4, SEEK_SET) != 0)
	{
		fclose(pFile);
		return false;
	}
	nFileOffset += 4;

	// ��������
	BYTE byPasswordLen = 0;
	nReadLen = fread_s(&byPasswordLen, 1, 1, 1, pFile);
	if (nReadLen != 1)
	{
		fclose(pFile);
		return false;
	}
	nFileOffset += nReadLen;

	if (byPasswordLen > USER_PASSWORD_KEY_LEN)
	{
		fclose(pFile);
		return false;
	}

	if (byPasswordLen > 0)
	{
		// ��������
		char szOutKey[USER_PASSWORD_KEY_LEN + 1] = {0};
		memset(szOutKey, 0, USER_PASSWORD_KEY_LEN + 1);

		nReadLen = fread_s(&szOutKey, byPasswordLen, 1, byPasswordLen, pFile);
		if (nReadLen != byPasswordLen)
		{
			fclose(pFile);
			return false;
		}
		nFileOffset += nReadLen;
	}

	DWORD nFileCtns = 0;
	// ��ȡ�ļ��ܸ���
	nReadLen = fread_s(&nFileCtns, sizeof(DWORD), 1, sizeof(DWORD), pFile);
	if (nReadLen != sizeof(DWORD))
	{
		fclose(pFile);
		return false;
	}
	nFileOffset += nReadLen;

	m_SkinFileList.push_front(pZipFilePath);
	SKIN_FILE_LIST::iterator pPathItem = m_SkinFileList.begin();
	if (pPathItem == m_SkinFileList.end())
	{
		fclose(pFile);
		return false;
	}
	CStringW &strPath = *pPathItem;

	for (int i = 0; i < (int)nFileCtns; i++)
	{
		// ��ȡ�ļ�����
		BYTE byFileType = 0;
		nReadLen = fread_s(&byFileType, sizeof(BYTE), 1, sizeof(BYTE), pFile);
		if (nReadLen != sizeof(BYTE))
		{
			fclose(pFile);
			return false;
		}
		nFileOffset += nReadLen;

		// ��ȡ�ļ����Ƴ���
		SHORT sNameLen = 0;
		nReadLen = fread_s(&sNameLen, sizeof(SHORT), 1, sizeof(SHORT), pFile);
		if (nReadLen != sizeof(SHORT))
		{
			fclose(pFile);
			return false;
		}
		nFileOffset += nReadLen;

		// ��ȡ�ļ�����
		WCHAR szName[MAX_PATH + 1];
		memset(szName, 0, sizeof(szName));
		nReadLen = fread_s(szName, MAX_PATH * sizeof(WCHAR), 1, sNameLen, pFile);
		if (nReadLen != sNameLen)
		{
			fclose(pFile);
			return false;
		}
		nFileOffset += nReadLen;

		// ��ȡԴ�ļ�����
		DWORD dwSrcFileLen = 0;
		int nReadLen = fread_s(&dwSrcFileLen, sizeof(DWORD), 1, sizeof(DWORD), pFile);
		if (nReadLen != sizeof(DWORD))
		{
			fclose(pFile);
			return false;
		}
		nFileOffset += nReadLen;

		// ��ѹ��
		ZIP_FILE* pZipItem = new ZIP_FILE;
		if (pZipItem == NULL)
		{
			fclose(pFile);
			return false;
		}

		pZipItem->byFileType = byFileType;
		memset(pZipItem->strFileName, 0, sizeof(pZipItem->strFileName));
		wcscpy_s(pZipItem->strFileName, MAX_PATH, szName);
		pZipItem->dwSrcFileLen = dwSrcFileLen;
		pZipItem->pFileData = NULL;
		pZipItem->dwFileDataOffset = nFileOffset;
		pZipItem->pstrSkinPath = strPath;

		WCHAR szXml[4];
		memset(szXml, 0, sizeof(szXml));
		wcscpy_s(szXml, 4, (pZipItem->strFileName + wcslen(pZipItem->strFileName) - 3));

		// �ڴ��Ż���Ҫ��ֻ����Ҫ�õ�zip�е�ͼƬ��ʱ��ż���ͼƬ��ֻ��xml�ļ�ֱ�ӽ���
		// �༭ģʽ�²������ڴ��Ż���ֱ��ʹ��
		if (lstrcmpiW(szXml, L"xml") == 0 || GetUiKernelInterface()->IsDesignMode())
		{
			// xml �ļ�ֱ�ӽ���
			// ��ȡѹ������
			BYTE *pZipData = new BYTE[dwSrcFileLen];
			if (pZipData == NULL)
			{
				SAFE_DELETE(pZipItem);
				fclose(pFile);
				return false;
			}
			nReadLen = 0;
			while (nReadLen < (int)dwSrcFileLen)
			{
				BYTE *pRead = pZipData + nReadLen;
				int nNeedRead = dwSrcFileLen - nReadLen;

				int nRead = fread_s(pRead, nNeedRead, 1, nNeedRead, pFile);
				nReadLen += nRead;
			}
			if (nReadLen != (int)dwSrcFileLen)
			{
				SAFE_DELETE(pZipItem);
				SAFE_DELETE_LIST(pZipData);
				fclose(pFile);
				return false;
			}
			nFileOffset += nReadLen;

			pZipItem->pFileData = pZipData;
		}
		else
		{
			// ��xml�ļ��ӳټ��أ�ֻ������Ҫ��ʱ��ŴӴ��̶�ȡ
			nFileOffset += (int)dwSrcFileLen;
			if (fseek(pFile, nFileOffset, SEEK_SET) != 0)
			{
				SAFE_DELETE(pZipItem);
				fclose(pFile);
				return false;
			}
		}

		m_ZipFileMap.insert(pair<CStringW, ZIP_FILE*>(pZipItem->strFileName, pZipItem));
	}

	fclose(pFile);
	return true;
}

// ȡ�ý�ѹ���ļ�����ļ��б�
ZIP_FILE_MAP* IZipFileImpl::GetUnZipFileMap()
{
	return &m_ZipFileMap;
}

ZIP_FILE* IZipFileImpl::FindUnZipFile(LPCWSTR pFileName)
{
	if (pFileName == NULL || wcslen(pFileName) <= 0)
		return NULL;

	ZIP_FILE_MAP::iterator pZipItem = m_ZipFileMap.find(pFileName);
	if (pZipItem == m_ZipFileMap.end())
		return NULL;

	return (pZipItem->second);
}

void IZipFileImpl::TestWriteUnZipFile(LPCWSTR pszOutDir)
{
	if (pszOutDir == NULL || wcslen(pszOutDir) <= 0)
		return;

	CStringW strOutDir = pszOutDir;
	if ((pszOutDir[wcslen(pszOutDir) - 1]) != '\\')
		strOutDir += L"\\";

	for (ZIP_FILE_MAP::iterator pZipItem = m_ZipFileMap.begin(); pZipItem != m_ZipFileMap.end(); pZipItem++)
	{
		ZIP_FILE* pZip = pZipItem->second;
		if (pZip == NULL || pZip->pFileData == NULL || pZip->dwSrcFileLen <= 0 || wcslen(pZip->strFileName) <= 0)
			continue;

		CStringW strPath = strOutDir + pZip->strFileName;

		FILE *pFile = NULL;
		_wfopen_s(&pFile, strPath, L"wb");
		if (pFile == NULL)
			continue;

		// �ļ�����
		int nWriteLen = 0;
		while (nWriteLen < (int)(pZip->dwSrcFileLen))
		{
			BYTE *pWrite = pZip->pFileData + nWriteLen;
			int nNeedWrite = pZip->dwSrcFileLen - nWriteLen;
			int nWrite = fwrite(pWrite, 1, nNeedWrite, pFile);
			nWriteLen += nWrite;
		}

		fclose(pFile);
	}
}

// �ڴ��Ż���Ҫ��ֻ����Ҫ�õ�zip�е�ͼƬ��ʱ��ż���ͼƬ
bool IZipFileImpl::ReadZipFileItem(ZIP_FILE* pZipItem)
{
	if (pZipItem == NULL || pZipItem->pFileData != NULL || pZipItem->pstrSkinPath == NULL || wcslen(pZipItem->pstrSkinPath) <= 0)
		return false;

	FILE *pFile = NULL;
	_wfopen_s(&pFile, pZipItem->pstrSkinPath, L"rb");
	if (pFile == NULL)
		return false;

	if (fseek(pFile, pZipItem->dwFileDataOffset, SEEK_SET) != 0)
	{
		fclose(pFile);
		return false;
	}

	DWORD dwSrcFileLen = pZipItem->dwSrcFileLen;

	// ��ȡѹ������
	BYTE *pZipData = new BYTE[dwSrcFileLen];
	if (pZipData == NULL)
	{
		fclose(pFile);
		return false;
	}
	int nReadLen = 0;
	while (nReadLen < (int)dwSrcFileLen)
	{
		BYTE *pRead = pZipData + nReadLen;
		int nNeedRead = dwSrcFileLen - nReadLen;

		int nRead = fread_s(pRead, nNeedRead, 1, nNeedRead, pFile);
		nReadLen += nRead;
	}
	if (nReadLen != (int)dwSrcFileLen)
	{
		SAFE_DELETE_LIST(pZipData);
		fclose(pFile);
		return false;
	}

	pZipItem->pFileData = pZipData;

	fclose(pFile);
	return true;
}

// ȡ��Ƥ�����汾��
SKIN_VERSION IZipFileImpl::GetSkinFileVersion(LPCWSTR pZipFilePath, int &nPasswordLen)
{
	nPasswordLen = 0;
	if (pZipFilePath == NULL || wcslen(pZipFilePath) <= 0)
		return SV_ERROR;

	FILE *pFile = NULL;
	_wfopen_s(&pFile, pZipFilePath, L"rb");
	if (pFile == NULL)
		return SV_ERROR;

	BYTE byVersionSign[3];
	memset(&byVersionSign, 0, 3);

	int nReadLen = fread_s(byVersionSign, 3, 1, 3, pFile);
	if (nReadLen != 3)
	{
		fclose(pFile);
		return SV_ERROR;
	}

	// ��֤�ļ�ͷ
	if (memcmp(byVersionSign, s_byBeginSign, 3) != 0)
	{
		fclose(pFile);
		return SV_0;
	}

	if (fseek(pFile, -3, SEEK_END) != 0)
	{
		fclose(pFile);
		return SV_ERROR;
	}

	nReadLen = fread_s(byVersionSign, 3, 1, 3, pFile);
	if (nReadLen != 3)
	{
		fclose(pFile);
		return SV_ERROR;
	}

	// ��֤�ļ�β
	if (memcmp(byVersionSign, s_byEndSign, 3) != 0)
	{
		fclose(pFile);
		return SV_0;
	}

	if (fseek(pFile, 3, SEEK_SET) != 0)
	{
		fclose(pFile);
		return SV_ERROR;
	}

	BYTE byVersion = 0;
	nReadLen = fread_s(&byVersion, 1, 1, 1, pFile);
	if (nReadLen != 1)
	{
		fclose(pFile);
		return SV_ERROR;
	}

	BYTE byPasswordLen = 0;
	nReadLen = fread_s(&byPasswordLen, 1, 1, 1, pFile);
	if (nReadLen != 1)
	{
		fclose(pFile);
		return SV_ERROR;
	}

	nPasswordLen = byPasswordLen;

	fclose(pFile);
	return (SKIN_VERSION)byVersion;
}

void IZipFileImpl::ReleasePassword(VER_PASSWORD &Password)
{
	SAFE_DELETE(Password.pbyDstPassword);
}

bool IZipFileImpl::CreatePassword_SV_1(VER_PASSWORD &Password)
{
	if (Password.skinVer < SV_1 || Password.skinVer > SV_2 || Password.strSrcPassword.size() <= 0)
		return false;

	CUiFeatureAes SV_1_Aes;
	return SV_1_Aes.CreateAesPassword((char*)Password.strSrcPassword.c_str(), &Password.pbyDstPassword, Password.nDstLen);
}

bool IZipFileImpl::GerPassword_SV_1(VER_PASSWORD &Password)
{
	if (Password.skinVer < SV_1 || Password.skinVer > SV_2 || Password.nDstLen <= 0 || Password.pbyDstPassword == NULL)
		return false;

	CUiFeatureAes SV_1_Aes;
	return SV_1_Aes.GetUserPassword(Password.pbyDstPassword, Password.nDstLen, Password.strSrcPassword);
}

bool IZipFileImpl::ComparePassword_SV_1(VER_PASSWORD &Password)
{
	if (Password.skinVer < SV_1 || Password.skinVer > SV_2 || Password.nDstLen <= 0 || Password.pbyDstPassword == NULL || Password.strSrcPassword.size() <= 0)
		return false;

	CUiFeatureAes SV_1_Aes;
	return SV_1_Aes.Compare(Password.pbyDstPassword, Password.nDstLen, (char*)Password.strSrcPassword.c_str());
}

// ��֤�û�Ƥ��������
bool IZipFileImpl::ChekUserPassword_SV_1(const char *pUserPassword, LPCWSTR pZipFilePath)
{
	if (pZipFilePath == NULL || wcslen(pZipFilePath) <= 0)
		return false;

	FILE *pFile = NULL;
	_wfopen_s(&pFile, pZipFilePath, L"rb");
	if (pFile == NULL)
		return false;

	if (fseek(pFile, 4, SEEK_SET) != 0)
	{
		fclose(pFile);
		return false;
	}

	BYTE byKeyLen = 0;
	int nReadLen = fread_s(&byKeyLen, 1, 1, 1, pFile);
	if (nReadLen != 1)
	{
		fclose(pFile);
		return false;
	}

	if (byKeyLen == 0)
	{
		// ������
		fclose(pFile);
		return true;
	}

	if (pUserPassword == NULL || strlen(pUserPassword) <= 0)
	{
		fclose(pFile);
		return false;
	}

	BYTE byKeyData[USER_PASSWORD_KEY_LEN + 1];
	memset(&byKeyData, 0, USER_PASSWORD_KEY_LEN + 1);
	nReadLen = fread_s(byKeyData, byKeyLen, 1, byKeyLen, pFile);
	if (nReadLen != byKeyLen)
	{
		fclose(pFile);
		return false;
	}
	fclose(pFile);

	CUiFeatureAes SV_1_Aes;
	return SV_1_Aes.Compare(byKeyData, (int)byKeyLen, (char*)pUserPassword);
}

// ����һ�������ļ�����ǰ��zip�ļ��б���
ZIP_FILE* IZipFileImpl::AppendLocalFileToZipFile(LPCWSTR pLocalFilePath, LPCWSTR pKeyFileName)
{
	if (pLocalFilePath == NULL || wcslen(pLocalFilePath) <= 0 || pKeyFileName == NULL || wcslen(pKeyFileName) <= 0)
		return NULL;

	WIN32_FILE_ATTRIBUTE_DATA FileAttr;
	if (!::GetFileAttributesExW(pLocalFilePath, GetFileExInfoStandard, &FileAttr))
		return NULL;

	FILE *pFile = NULL;
	_wfopen_s(&pFile, pLocalFilePath, L"rb");
	if (pFile == NULL)
		return NULL;

	ZIP_FILE* pAppendZipFile = new(nothrow) ZIP_FILE;
	if (pAppendZipFile == NULL)
	{
		fclose(pFile);
		return NULL;
	}

	pAppendZipFile->byFileType = ZFT_IMAGE;

	memset(pAppendZipFile->strFileName, 0, sizeof(pAppendZipFile->strFileName));
	wcscpy_s(pAppendZipFile->strFileName, MAX_PATH, pKeyFileName);

	pAppendZipFile->dwSrcFileLen = FileAttr.nFileSizeLow;
	pAppendZipFile->pFileData = new(nothrow) BYTE[FileAttr.nFileSizeLow];
	if (pAppendZipFile->pFileData == NULL)
	{
		fclose(pFile);
		SAFE_DELETE(pAppendZipFile);
		return NULL;
	}

	int nReadLen = 0;
	while (nReadLen < (int)FileAttr.nFileSizeLow)
	{
		BYTE *pRead = pAppendZipFile->pFileData + nReadLen;
		int nNeedRead = FileAttr.nFileSizeLow - nReadLen;

		int nRead = fread_s(pRead, nNeedRead, 1, nNeedRead, pFile);
		nReadLen += nRead;
	}

	if (nReadLen != (int)FileAttr.nFileSizeLow)
	{
		fclose(pFile);
		SAFE_DELETE(pAppendZipFile->pFileData);
		SAFE_DELETE(pAppendZipFile);
		return NULL;
	}

	fclose(pFile);
	m_ZipFileMap.insert(pair<CStringW, ZIP_FILE*>(pAppendZipFile->strFileName, pAppendZipFile));
	return pAppendZipFile;
}
