// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://go.microsoft.com/fwlink/?LinkId=238214��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// BMView.cpp : CBMView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "BM.h"
#endif

#include "BMDoc.h"
#include "BMView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBMView

IMPLEMENT_DYNCREATE(CBMView, CView)

BEGIN_MESSAGE_MAP(CBMView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CBMView ����/����

CBMView::CBMView()
{
	// TODO: �ڴ˴���ӹ������

}

CBMView::~CBMView()
{
}

BOOL CBMView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CBMView ����

void CBMView::OnDraw(CDC* /*pDC*/)
{
	CBMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

void CBMView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CBMView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CBMView ���

#ifdef _DEBUG
void CBMView::AssertValid() const
{
	CView::AssertValid();
}

void CBMView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBMDoc* CBMView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBMDoc)));
	return (CBMDoc*)m_pDocument;
}
#endif //_DEBUG


// CBMView ��Ϣ�������
