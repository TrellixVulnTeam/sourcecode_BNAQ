
#pragma once
#include <Windows.h>
#include "..\..\..\3rd\AES\AES.h"

class CUiFeatureAes
{
public:
	CUiFeatureAes();
	~CUiFeatureAes();

	// �����û�������ַ���������AES��Կ
	bool CreateAesPassword(char* pszScr, BYTE** ppbyOutKey, int &nOutKeyLen);
	// ����AES��Կ�õ��û�����
	bool GetUserPassword(BYTE* pbyAesData, int nAesDataLen, string &strUserPassword);
	// ƥ���û�����������AES�����Ƿ����
	bool Compare(BYTE* pbyAesData, int nAesDataLen, char* pUserPassword);

};
