
#include "stdafx.h"
#include "ChildView.h"
#include "service\ISqliteService.h"
#include "core\SingletonManagerCenter.h"

void CChildView::HandleNewCompany()
{
    ISqliteService* pSS = SingletonManagerCenter->GetInstance()->GetSingletonByID(STID_SQLITESV);
	if(pSS)
	{
		if(pSS->IsComanyExist(m_dbOperation.sComanyName))
		{
			MessageBox(_T("��Ҫ��ӵĹ�˾�Ѵ���"));
		}
		else
		{
            if(!pSS->NewComany(m_dbOperation.sComanyName))
			{
                MessageBox(_T("��ӹ�˾ʧ��"));
			}
			else
			{
				RefreshTree();
			}
		}
	}
}

void CChildView::RefreshTree()
{

}

void CChildView::HandleDeleteCompany()
{
	ISqliteService* pSS = SingletonManagerCenter->GetInstance()->GetSingletonByID(STID_SQLITESV);
	if(pSS)
	{
		if(pSS->IsComanyExist(m_dbOperation.sComanyName))
		{
			MessageBox(_T("��Ҫ��ӵĹ�˾�Ѵ���"));
		}
		else
		{
			if(!pSS->NewComany(m_dbOperation.sComanyName))
			{
				MessageBox(_T("��ӹ�˾ʧ��"));
			}
			else
			{
				NewCompany();
			}
		}
	}
}



void CChildView::HandleNewDepartment()
{

}

void CChildView::HandleDeleteDepartment()
{

}

void CChildView::HandleNewEmploy()
{

}

void CChildView::HandleDeleteEmploy()
{

}