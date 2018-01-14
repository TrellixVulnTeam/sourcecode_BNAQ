#include "StdAfx.h"
#include "LocalImageList.h"
#include "ImageBasePropEditDlg.h"
#include "MainFrm.h"
#include "ImageBaseView.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "Function.h"

typedef list<ZIP_FILE*>		ZIP_FILE_ORDER_VEC;


CLocalImageList::CLocalImageList(void)
{
	m_pImgBaseDlg = NULL;
	m_pUiKernel = NULL;
	m_pImgBaseLise = NULL;
	m_pSelImgBase = NULL;
	m_pImgBaseView = NULL;
	m_pCurrentZipFile = NULL;
}

CLocalImageList::~CLocalImageList(void)
{
}

COLORREF CLocalImageList::OnGetCellBkColor(int nRow, int nColum)
{
	return(nRow % 2) == 0 ? RGB(255, 255, 255) : RGB(255, 255, 255);
}

void CLocalImageList::OnSelectItem()
{
	if (m_pImgBaseDlg == NULL)
		return;

	if (m_nSelectItem < 1)
	{
		// û��ѡ��
		m_pCurrentZipFile = NULL;
		if (m_pImgBaseView != NULL)
			m_pImgBaseView->SetCurrentShowImage(m_pImgBaseDlg, m_pUiKernel, m_pSelImgBase, NULL);
	}
	else
	{
		m_pCurrentZipFile = (ZIP_FILE*)this->GetItemData(m_nSelectItem);
		if (m_pCurrentZipFile == NULL)
			return;

		if (m_pSelImgBase != NULL)
		{
			// �����������жϣ�Ϊ������ͬһ�� IPropertyImage �����Ѿ����ú���֮��
			// ��������û���������Ե� IPropertyImage ���Ե�ֵѡ����Ϊ�յ�bug
			if (m_pSelImgBase->SetZipFile(m_pCurrentZipFile, true))
			{
				if (m_pSelImgBase->GetImageProp() != NULL && m_pSelImgBase->GetDrawingImage() != NULL)
				{
					IMAGE_BASE_PROP* pImgProp = m_pSelImgBase->GetImageProp();
					CDrawingImage* pDrawImg = m_pSelImgBase->GetDrawingImage();

					INIT_RECT(pImgProp->RectInImage);
					pImgProp->RectInImage.right = pDrawImg->GetDcSize().cx;
					pImgProp->RectInImage.bottom = pDrawImg->GetDcSize().cy;
				}
			}
		}

		if (m_pImgBaseView != NULL)
			m_pImgBaseView->SetCurrentShowImage(m_pImgBaseDlg, m_pUiKernel, m_pSelImgBase, m_pCurrentZipFile);
	}

	if (m_pImgBaseLise != NULL)
		m_pImgBaseLise->RefreshImageBaseShow();
}

void CLocalImageList::Init(IUiFeatureKernel* pUiKernel, CImageBasePropEditDlg *pImgBaseDlg, CImageBaseNameList* pImgBaseLise, CImageBaseView* pImgBaseView)
{
	if (pUiKernel == NULL || pImgBaseDlg == NULL || pImgBaseLise == NULL || pImgBaseView == NULL)
		return;

	m_pImgBaseView = pImgBaseView;
	m_pImgBaseDlg = pImgBaseDlg;
	m_pUiKernel = pUiKernel;
	m_pImgBaseLise = pImgBaseLise;

	if (m_pSelImgBase == NULL)
		RefreshList(NULL);
	else
		RefreshList(m_pSelImgBase->GetZipFile());
}

ZIP_FILE_MAP* CLocalImageList::GetZipFileMap()
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if (pMain == NULL)
		return NULL;

	SKIN_FILE_ITEM* pSkinFileItem = pMain->GetSkinFileItem();
	if (pSkinFileItem == NULL || pSkinFileItem->pZipFileMgr == NULL)
		return NULL;

	return pSkinFileItem->pZipFileMgr->GetUnZipFileMap();
}

void CLocalImageList::RefreshList(ZIP_FILE* pSelZipFile)
{
	this->DeleteAllItems();

	this->SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	this->ModifyStyle(0, LVS_SINGLESEL | LVS_SHOWSELALWAYS);
	this->InsertColumn(0, _T("#"), LVCFMT_LEFT, 50);
	this->InsertColumn(1, _T("����ͼƬ����"), LVCFMT_LEFT, 160);

	this->InsertItem(0, _T("#"));
	this->SetItemText(0, 1, _T("��������δ����ͼƬ"));
	this->SetItemData(0, NULL);

	if (GetZipFileMap() != NULL)
	{
		ZIP_FILE_ORDER_VEC ZipFileOrderVec;
		ZipFileOrderVec.clear();

		// �����򣬰�����������
		for (ZIP_FILE_MAP::iterator pZipItem = GetZipFileMap()->begin(); pZipItem != GetZipFileMap()->end(); pZipItem++)
		{
			ZIP_FILE *pZipFile = pZipItem->second;
			if (pZipFile == NULL)
				continue;

			if (ZipFileOrderVec.size() <= 0)
			{
				ZipFileOrderVec.push_back(pZipFile);
				continue;
			}

			char* pszObjName = (char*)(pZipFile->strFileName);
			if (pszObjName == NULL || strlen(pszObjName) <= 0)
			{
				ZipFileOrderVec.push_front(pZipFile);
				continue;
			}

			bool bInsert = false;
			for (ZIP_FILE_ORDER_VEC::iterator pZipFileItemTemp = ZipFileOrderVec.begin(); pZipFileItemTemp != ZipFileOrderVec.end(); pZipFileItemTemp++)
			{
				ZIP_FILE* pZipFileTemp = *pZipFileItemTemp;
				if (pZipFileTemp == NULL || pZipFileTemp == pZipFile)
					continue;

				char* pszComObjName = (char*)(pZipFileTemp->strFileName);
				if (pszComObjName == NULL || strlen(pszComObjName) <= 0)
					continue;

				if (lstrcmpiA(pszObjName, pszComObjName) <= 0)
				{
					bInsert = true;
					ZipFileOrderVec.insert(pZipFileItemTemp, pZipFile);
					break;
				}
			}

			if (!bInsert)
				ZipFileOrderVec.push_back(pZipFile);
		}

		int nNo = 1;
		for (ZIP_FILE_ORDER_VEC::iterator pZipFileItem = ZipFileOrderVec.begin(); pZipFileItem != ZipFileOrderVec.end(); pZipFileItem++, nNo++)
		{
			ZIP_FILE* pZipFile = *pZipFileItem;
			if (pZipFile == NULL)
				continue;

			CString strNo(_T(""));
			strNo.Format(_T("%d"), nNo);
			this->InsertItem(nNo, strNo);
			this->SetItemText(nNo, 1, pZipFile->strFileName);
			this->SetItemData(nNo, (DWORD_PTR)pZipFile);

			if (pSelZipFile == pZipFile)
			{
				this->SetItemState(nNo, LVIS_SELECTED, LVIS_SELECTED);
				if (m_pImgBaseView != NULL)
					m_pImgBaseView->SetCurrentShowImage(m_pImgBaseDlg, m_pUiKernel, m_pSelImgBase, pZipFile);
			}
		}
	}
}

bool CLocalImageList::OnLoadLocalImage(CString strFilePath, CString strFileName)
{
	if (m_pUiKernel == NULL || strFileName.GetLength() <= 0 || strFilePath.GetLength() <= 0 || GetZipFileMap() == NULL)
		return false;

	WIN32_FILE_ATTRIBUTE_DATA FileAttr;
	if (!::GetFileAttributesExW(strFilePath, GetFileExInfoStandard, &FileAttr))
		return false;

	FILE *pFile = NULL;
	_wfopen_s(&pFile, strFilePath, L"rb");

	if (pFile == NULL)
		return false;

	ZIP_FILE *pFileItem = m_pUiKernel->GetSkinManager()->MEM_CreateZipFile(GetSkinFileItem(), FileAttr.nFileSizeLow, ZFT_IMAGE, strFileName);
	if (pFileItem == NULL)
	{
		fclose(pFile);
		return false;
	}

	int nReadLen = 0;
	while (nReadLen < (int)FileAttr.nFileSizeLow)
	{
		BYTE *pRead = pFileItem->pFileData + nReadLen;
		int nNeedRead = FileAttr.nFileSizeLow - nReadLen;

		int nRead = fread_s(pRead, nNeedRead, 1, nNeedRead, pFile);
		nReadLen += nRead;
	}

	if (nReadLen != (int)FileAttr.nFileSizeLow)
	{
		m_pUiKernel->GetSkinManager()->MEM_DeleteZipFileByCom(GetSkinFileItem(), pFileItem);
		fclose(pFile);
		return false;
	}

	int nNo = this->GetItemCount();
	CString strNo(_T(""));
	strNo.Format(_T("%d"), nNo);
	this->InsertItem(nNo, strNo);
	this->SetItemText(nNo, 1, pFileItem->strFileName);
	this->SetItemData(nNo, (DWORD_PTR)pFileItem);
	return true;
}

void CLocalImageList::SetSelectImagePropBase(IPropertyImageBase* pImgBase)
{
	m_pSelImgBase = pImgBase;
	if (m_pSelImgBase == NULL)
		return;

	ZIP_FILE* pImgPropZipFile = m_pSelImgBase->GetZipFile();
	if (pImgPropZipFile == NULL)
	{
		this->SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
		m_nSelectItem = 0;
		OnSelectItem();
		return;
	}

	for (int i = 1; i < this->GetItemCount(); i++)
	{
		ZIP_FILE *pComZipFile = (ZIP_FILE *)this->GetItemData(i);
		if (pComZipFile == pImgPropZipFile)
		{
			this->SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
			m_nSelectItem = i;
			OnSelectItem();
			break;
		}
	}
}

bool CLocalImageList::OnDeleteLocalImage()
{
	bool bHaveDelete = false;
	int nCtns = this->GetItemCount();
	for (int i = 1; i < nCtns; i++)
	{
		BOOL bCheck = this->GetCheck(i);
		if (bCheck)
		{
			bHaveDelete = true;
			break;
		}
	}

	if (!bHaveDelete)
	{
		AfxMessageBox(_T("���ȹ�ѡ��Ҫɾ����ͼƬ��"), MB_OK | MB_ICONWARNING);
		return false;
	}

	if (AfxMessageBox(_T("ȷ��Ҫɾ�������ͼƬ��"), MB_OKCANCEL | MB_ICONINFORMATION) != IDOK)
		return true;

	if (m_pUiKernel == NULL || GetZipFileMap() == NULL)
		return false;

	bool bDelete = false;
	nCtns = this->GetItemCount();
	for (int i = 1; i < nCtns; )
	{
		BOOL bCheck = this->GetCheck(i);
		if (bCheck)
		{
			bDelete = true;

			// ѡ�У�ɾ��
			ZIP_FILE *pZipFile = (ZIP_FILE*)this->GetItemData(i);
			if (pZipFile == NULL)
				continue;

			if (!m_pUiKernel->GetSkinManager()->BD_DeleteZipImage(GetSkinFileItem(), pZipFile))
			{
				AfxMessageBox(_T("ɾ��ͼƬ��������"), MB_OK | MB_ICONERROR);
				return false;
			}

			m_pUiKernel->GetSkinManager()->MEM_DeleteZipFileByCom(GetSkinFileItem(), pZipFile);

			m_nSelectItem = -1;
			this->DeleteItem(i);
			nCtns = this->GetItemCount();
			if (nCtns <= 1)
				return true;

			i = 0;
		}
		else
		{
			i++;
		}
	}

	OnSelectItem();
	return true;
}
