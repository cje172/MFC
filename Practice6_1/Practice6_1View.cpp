
// Practice6_1View.cpp : CPractice6_1View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Practice6_1.h"
#endif

#include "Practice6_1Doc.h"
#include "Practice6_1View.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPractice5_1View

IMPLEMENT_DYNCREATE(CPractice6_1View, CView)

BEGIN_MESSAGE_MAP(CPractice6_1View, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPractice6_1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_LINE, &CPractice6_1View::OnLine)
	ON_COMMAND(ID_ELLIPSE, &CPractice6_1View::OnEllipse)
	ON_COMMAND(ID_POLYGON, &CPractice6_1View::OnPolygon)
	ON_COMMAND(ID_LINE_COLOR, &CPractice6_1View::OnLineColor)
	ON_COMMAND(ID_FACE_COLOR, &CPractice6_1View::OnFaceColor)
	ON_COMMAND(ID_BDIAGONAL, &CPractice6_1View::OnBdiagonal)
	ON_COMMAND(ID_CROSS, &CPractice6_1View::OnCross)
	ON_COMMAND(ID_VERTICAL, &CPractice6_1View::OnVertical)
	ON_UPDATE_COMMAND_UI(ID_LINE, &CPractice6_1View::OnUpdateLine)
	ON_UPDATE_COMMAND_UI(ID_ELLIPSE, &CPractice6_1View::OnUpdateEllipse)
	ON_UPDATE_COMMAND_UI(ID_POLYGON, &CPractice6_1View::OnUpdatePolygon)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_NCRBUTTONDOWN()
END_MESSAGE_MAP()

// CPractice6_1View ����/�Ҹ�

CPractice6_1View::CPractice6_1View()
	: m_nDrawMode(0)
	, m_nHatchStyle(0)
	, m_ptStart(0)
	, m_ptPrev(0)
	, m_bFirst(false)
	, m_bLButtonDown(false)
	, m_bContextMenu(false)
	, m_bHatch(false)
	, m_nCount(0)
{
	m_nDrawMode = LINE_MODE;				// �׸��� ��� �߿��� ������ �׸��� �ʱ�ȭ
	m_bContextMenu = true;					// ���ؽ�Ʈ �޴��� Ȱ������ �ʱ�ȭ
	m_bFirst = true;						// ó�� �׸��� ������ �ʱ�ȭ
	m_bLButtonDown = false;					// ���� ��ư�� ������ ���� ������ �ʱ�ȭ
	m_nCount = 0;							// �ٰ��� ���� ������ �迭�� ī��Ʈ �ʱ�ȭ
	for (int i = 0; i < 50; i++)		 	// �ٰ����� ���� ������ �迭 �ʱ�ȭ
		m_ptData[i] = 0;
	m_bHatch = false;						// ��ġ �귯���� ���ڰ� �������� �ʱ�ȭ
	m_nHatchStyle = HS_CROSS;
	m_colorPen = RGB(0, 0, 0);				// pen color�� ���������� �ʱ�ȭ
	m_colorBrush = RGB(255, 255, 255);		// brush color�� ������� �ʱ�ȭ
}

CPractice6_1View::~CPractice6_1View()
{
}

BOOL CPractice6_1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CPractice5_1View �׸���

void CPractice6_1View::OnDraw(CDC* pDC)
{
	CPractice6_1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	CPen pen, *oldpen;								
	pen.CreatePen(PS_SOLID, 1, m_colorPen);				// pen ��ü ����
	oldpen = pDC->SelectObject(&pen);					// pen ��ü ���		
	pDC->SetROP2(R2_COPYPEN);							// COPYPEN���� ����
	CBrush brush, * oldbrush;
	if (m_bHatch)
		brush.CreateHatchBrush(m_nHatchStyle, m_colorBrush);	// Hatch brush ��ü ����
	else
		brush.CreateSolidBrush(m_colorBrush);					// Solid brush ��ü ����
	oldbrush = pDC->SelectObject(&brush);						// brush ��ü ���

	switch (m_nDrawMode)
	{
	case LINE_MODE:			// ���� �׸���
		pDC->MoveTo(m_ptStart);
		pDC->LineTo(m_ptPrev);
		break;
	case ELLIPSE_MODE:		// �� �׸���
		pDC->Ellipse(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
		break;
	case POLYGON_MODE:		// �ٰ��� �׸���
		// �迭�� ������ ������� ������ ������ �ٰ��� �׸���
		pDC->Polygon(m_ptData, m_nCount);
		break;
	}
	pDC->SelectObject(oldpen);		// ���� pen���� ����
	pDC->SelectObject(oldbrush);	// ���� brush���� ����
	pen.DeleteObject();				// pen ��ü ����
	brush.DeleteObject();			// brush ��ü ����
}


// CPractice5_1View �μ�


void CPractice6_1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPractice6_1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CPractice6_1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CPractice6_1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CPractice6_1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPractice6_1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	if (m_bContextMenu == true)
	{
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
	}
	m_bContextMenu = true;
#endif
}


// CPractice6_1View ����

#ifdef _DEBUG
void CPractice6_1View::AssertValid() const
{
	CView::AssertValid();
}

void CPractice6_1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPractice6_1Doc* CPractice6_1View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPractice6_1Doc)));
	return (CPractice6_1Doc*)m_pDocument;
}
#endif //_DEBUG


// CPractice6_1View �޽��� ó����


void CPractice6_1View::OnLine()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// �����׸��� ��� ����
	m_nDrawMode = LINE_MODE;

	// ������������ ������ ����
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	// ���¹ٿ� �׸��� ��� ���
	pFrame->m_wndStatusBar.SetWindowText(_T("���� �׸���"));
}


void CPractice6_1View::OnEllipse()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// �� �׸��� ��� ���� 
	m_nDrawMode = ELLIPSE_MODE;

	// ������������ ������ ����
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	// ���¹ٿ� �׸��� ��� ���
	pFrame->m_wndStatusBar.SetWindowText(_T("�� �׸���"));
}


void CPractice6_1View::OnPolygon()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// �ٰ��� �׸��� ��� ����
	m_nDrawMode = POLYGON_MODE;

	// ������������ ������ ����
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	// ���¹ٿ� �׸��� ��� ���
	pFrame->m_wndStatusBar.SetWindowText(_T("�ٰ����׸���"));
}


void CPractice6_1View::OnLineColor()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CColorDialog dlgColor;				// ���� ��ȭ������ �ν��Ͻ� ����
	if (dlgColor.DoModal() == IDOK)		// ������ �����ϰ� Ȯ���� ������
	{
		m_colorPen = dlgColor.GetColor();		// ������ ���� ���� ��� colorPen�� ����
	}
	Invalidate(true);
}


void CPractice6_1View::OnFaceColor()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CColorDialog dlgColor;				// ���� ��ȭ������ �ν��Ͻ� ����
	if (dlgColor.DoModal() == IDOK)		// ������ �����ϰ� Ȯ���� ������
	{
		m_colorBrush = dlgColor.GetColor();		// ������ ���� ���� ��� colorBrush�� ����
	}
	Invalidate(true);
}


void CPractice6_1View::OnBdiagonal()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// ���� 45�� ���� ����
	m_nHatchStyle = HS_BDIAGONAL;
	m_bHatch = true;
	Invalidate(true);
}


void CPractice6_1View::OnCross()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// ���ڰ� ���� ����
	m_nHatchStyle = HS_CROSS;
	m_bHatch = true;
	Invalidate(true);
}


void CPractice6_1View::OnVertical()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// ���� ���� ����
	m_nHatchStyle = HS_VERTICAL;
	m_bHatch = true;
	Invalidate(true);
}


void CPractice6_1View::OnUpdateLine(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	// ���� �׸��� ����̸� �޴��� üũ ǥ�� 
	pCmdUI->SetCheck(m_nDrawMode == LINE_MODE ? 1 : 0);
}


void CPractice6_1View::OnUpdateEllipse(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	// �� �׸��� ����̸� �޴��� üũ ǥ�� 
	pCmdUI->SetCheck(m_nDrawMode == ELLIPSE_MODE ? 1 : 0);
}


void CPractice6_1View::OnUpdatePolygon(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	// �ٰ��� �׸��� ����̸� �޴��� üũ ǥ��
	pCmdUI->SetCheck(m_nDrawMode == POLYGON_MODE ? 1 : 0);
}


void CPractice6_1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CClientDC dc(this);  // Ŭ���̾�Ʈ ��ü ����
	CPen pen, * oldpen;
	pen.CreatePen(PS_SOLID, 1, m_colorPen);
	oldpen = dc.SelectObject(&pen);

	dc.SetROP2(R2_NOTXORPEN);

	CBrush brush, * oldbrush;
	if (m_bHatch)
		brush.CreateHatchBrush(m_nHatchStyle, m_colorBrush);
	else
		brush.CreateSolidBrush(m_colorBrush);

	oldbrush = dc.SelectObject(&brush);

	switch (m_nDrawMode)
	{
	case LINE_MODE:
		if (m_bLButtonDown)
		{
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptPrev);
			dc.MoveTo(m_ptStart);
			dc.LineTo(point);
			m_ptPrev = point;
		}
		break;

	case ELLIPSE_MODE:
		if (m_bLButtonDown)
		{
			dc.Ellipse(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
			dc.Ellipse(m_ptStart.x, m_ptStart.y, point.x, point.y);
			m_ptPrev = point;
		}
		break;
	case POLYGON_MODE:
		if (!m_bFirst)
		{
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptPrev);
			dc.MoveTo(m_ptStart);
			dc.LineTo(point);
			m_ptPrev = point;
		}
		break;
	}
	dc.SelectObject(oldpen);
	dc.SelectObject(oldbrush);
	pen.DeleteObject();
	brush.DeleteObject();

	// ���� �������� ������ ����
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CString strPoint;
	strPoint.Format(_T("���콺 ��ġ x : %d, y : %d"), point.x, point.y);
	// ���� �߰��� �ҿ� ���콺 ��ġ ���
	pFrame->m_wndStatusBar.SetPaneText(1, strPoint);

	CView::OnMouseMove(nFlags, point);
}


void CPractice6_1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// �� ������ �ʱ�ȭ
	if (m_bFirst)
	{
		m_ptStart = m_ptPrev = 0;
		m_bLButtonDown = false;
		m_nCount = 0;
		for (int i = 0; i < 50; i++)
			m_ptData[i] = 0;
		Invalidate(true);  // ȭ�鰻��
	}

	switch (m_nDrawMode)
	{
	case LINE_MODE:				// ���� �׸���
	case ELLIPSE_MODE:			// �� �׸���
		m_bLButtonDown = true;
		m_ptStart = m_ptPrev = point;
		m_bFirst = false;
		break;
	case POLYGON_MODE:			// �ٰ��� �׸���
		if (m_bFirst == true)
			m_bFirst = false;
		m_ptStart = m_ptPrev = point;
		m_ptData[m_nCount] = point;
		m_nCount++;
		break;
	}

	RECT rectClient;				// ����ü ���� ����
	SetCapture();					// ���콺 ĸó
	GetClientRect(&rectClient);		// Ŭ���̾�Ʈ ���� ����
	ClientToScreen(&rectClient);	// ��ũ�� ��ǥ�� ��ȯ
	::ClipCursor(&rectClient);		// ���콺 �̵������� Ŭ���̾�Ʈ �������� ����

	CView::OnLButtonDown(nFlags, point);
}


void CPractice6_1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bLButtonDown)				// ���� ���콺 ��ư�� ���� �����̸�
	{
		// �׸��� ��尡 ���� �׸���, �� �׸��� �̸�
		if (m_nDrawMode == LINE_MODE || m_nDrawMode == ELLIPSE_MODE)
		{
			m_bLButtonDown = false;
			m_bFirst = true;
			ReleaseCapture();		// ���콺 ĸó ����
			::ClipCursor(NULL);		// ���콺 Ŭ�� ����
			Invalidate(true);		// ȭ�� ����
		}
	}

	CView::OnLButtonUp(nFlags, point);
}


void CPractice6_1View::OnNcRButtonDown(UINT nHitTest, CPoint point)
{
	// �ٰ��� �׸���
	if (m_nDrawMode == POLYGON_MODE)
	{
		if (!m_bFirst)
		{
			m_bContextMenu = FALSE;
			// �迭�� ���� ���� �����ϰ� ī��Ʈ ����
			m_ptData[m_nCount] = point;
			m_nCount++;
			// üũ���� �ʱ�ȭ => �ٽ� �ٰ����� �׸��� ����
			m_bFirst = TRUE;
			ReleaseCapture();		// ���콺 ĸó ����
			::ClipCursor(NULL);		// ���콺 Ŭ�� ����
			Invalidate(TRUE);		// ȭ�鰻��
		}
	}

	CView::OnNcRButtonDown(nHitTest, point);
}
