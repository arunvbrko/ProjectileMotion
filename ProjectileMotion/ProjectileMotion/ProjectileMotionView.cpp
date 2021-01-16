// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// ProjectileMotionView.cpp : implementation of the CProjectileMotionView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ProjectileMotion.h"
#endif

#include "ProjectileMotionDoc.h"
#include "ProjectileMotionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProjectileMotionView

IMPLEMENT_DYNCREATE(CProjectileMotionView, CView)

BEGIN_MESSAGE_MAP(CProjectileMotionView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CProjectileMotionView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON_START, &CProjectileMotionView::OnButtonStart)
	ON_COMMAND(ID_BUTTON_PAUSE, &CProjectileMotionView::OnButtonPause)
	ON_COMMAND(ID_BUTTON_RESUME, &CProjectileMotionView::OnButtonResume)
END_MESSAGE_MAP()

// CProjectileMotionView construction/destruction

CProjectileMotionView::CProjectileMotionView() noexcept
{
	// TODO: add construction code here
	m_pCurrentThread = NULL;
	m_iCounter = 0;

}

CProjectileMotionView::~CProjectileMotionView()
{
}

BOOL CProjectileMotionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CProjectileMotionView drawing

void CProjectileMotionView::OnDraw(CDC* pDC)
{
	CProjectileMotionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	CString strCounter;
	strCounter.Format(L"y");
	pDC->TextOut(190, 90, strCounter);
	strCounter.Format(L"x -> ");
	pDC->TextOut(900, 310, strCounter);
	pDC->MoveTo(200, 100);
	pDC->LineTo(200, 303);
	pDC->MoveTo(1000, 303);
	pDC->LineTo(200, 303);
	CPen mypen;
	mypen.CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&mypen);

	if (m_iCounter < 900)
	{
		for (int i = 0; i < m_PointArray.GetSize() - 2; i++)
		{
			pDC->MoveTo(m_PointArray[i].x, m_PointArray[i].y);
			pDC->LineTo(m_PointArray[i + 1].x, m_PointArray[i + 1].y);
		}
	}
	pDC->SelectObject(&mypen);
	
	// TODO: add draw code for native data here
}


// CProjectileMotionView printing


void CProjectileMotionView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CProjectileMotionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CProjectileMotionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CProjectileMotionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CProjectileMotionView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CProjectileMotionView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CProjectileMotionView diagnostics

#ifdef _DEBUG
void CProjectileMotionView::AssertValid() const
{
	CView::AssertValid();
}

void CProjectileMotionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProjectileMotionDoc* CProjectileMotionView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProjectileMotionDoc)));
	return (CProjectileMotionDoc*)m_pDocument;
}
#endif //_DEBUG


// CProjectileMotionView message handlers


void CProjectileMotionView::OnButtonStart()
{
	// TODO: Add your command handler code here
	m_pCurrentThread = AfxBeginThread(CProjectileMotionView::StartThread, this);
	
}


void CProjectileMotionView::OnButtonPause()
{
	// TODO: Add your command handler code here
	m_pCurrentThread->SuspendThread();
}


void CProjectileMotionView::OnButtonResume()
{
	m_pCurrentThread->ResumeThread();
	// TODO: Add your command handler code here
}


UINT CProjectileMotionView::StartThread(LPVOID P)
{
	CProjectileMotionView* pview = (CProjectileMotionView*)P;
	int a = 13;
	CPoint MyPoint(0, 0);
	
	while (true)
	{
		MyPoint.y = 300+50* sin(pview->m_iCounter);
		MyPoint.x = 200 + pview->m_iCounter;
		
		pview->m_PointArray.Add(MyPoint);
		pview->m_iCounter = pview->m_iCounter + 100;

		pview->Invalidate();
		Sleep(1500);
	}
	// TODO: Add your implementation code here. 
	return 0;
}
