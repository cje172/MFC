
// Practice5_1View.cpp : CPractice5_1View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Practice5_1.h"
#endif

#include "Practice5_1Doc.h"
#include "Practice5_1View.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPractice5_1View

IMPLEMENT_DYNCREATE(CPractice5_1View, CView)

BEGIN_MESSAGE_MAP(CPractice5_1View, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPractice5_1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_LINE, &CPractice5_1View::OnLine)
	ON_COMMAND(ID_ELLIPSE, &CPractice5_1View::OnEllipse)
	ON_COMMAND(ID_POLYGON, &CPractice5_1View::OnPolygon)
	ON_COMMAND(ID_LINE_COLOR, &CPractice5_1View::OnLineColor)
	ON_COMMAND(ID_FACE_COLOR, &CPractice5_1View::OnFaceColor)
	ON_COMMAND(ID_BDIAGONAL, &CPractice5_1View::OnBdiagonal)
	ON_COMMAND(ID_CROSS, &CPractice5_1View::OnCross)
	ON_COMMAND(ID_VERTICAL, &CPractice5_1View::OnVertical)
	ON_UPDATE_COMMAND_UI(ID_LINE, &CPractice5_1View::OnUpdateLine)
	ON_UPDATE_COMMAND_UI(ID_ELLIPSE, &CPractice5_1View::OnUpdateEllipse)
	ON_UPDATE_COMMAND_UI(ID_POLYGON, &CPractice5_1View::OnUpdatePolygon)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_BEZIER, &CPractice5_1View::OnBezier)
	ON_UPDATE_COMMAND_UI(ID_BEZIER, &CPractice5_1View::OnUpdateBezier)
END_MESSAGE_MAP()

// CPractice5_1View ����/�Ҹ�

CPractice5_1View::CPractice5_1View()
	: m_nDrawMode(0)
	, m_nHatchStyle(0)
	, m_ptStart(0)
	, m_ptPrev(0)
	, m_bFirst(false)
	, m_bLButtonDown(false)
	, m_bContextMenu(false)
	, m_bHatch(false)
	, m_nCount(0)
	, m_nCtrlPointNum(0)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_nDrawMode = LINE_MODE;
	m_bContextMenu = true;
	m_bFirst = true;
	m_bLButtonDown = false;
	m_nCount = 0;
	for (int i = 0; i < 50; i++)
		m_ptData[i] = 0;
	m_bHatch = false;
	m_nHatchStyle = HS_CROSS;
	for (int i = 0; i < 50; i++)
		m_ptControl[i] = 0;

	m_colorPen = RGB(0, 0, 0);
	m_colorBrush = RGB(255, 255, 255);
	m_colorCurve = RGB(255, 0, 0);
	m_colorPolygon = RGB(0, 0, 0);
	m_colorPoint = RGB(200, 200, 200);

	m_nCtrlPointNum = 0;
}

CPractice5_1View::~CPractice5_1View()
{
}

BOOL CPractice5_1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CPractice5_1View �׸���

void CPractice5_1View::OnDraw(CDC* pDC)
{
	CPractice5_1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	CPen pen, * oldpen, Pointpen, Curvepen, Polygonpen;
	pen.CreatePen(PS_SOLID, 1, m_colorPen);					// Pen ��ü ����
	Pointpen.CreatePen(PS_SOLID, 7, m_colorPoint);
	Curvepen.CreatePen(PS_SOLID, 1, m_colorCurve);
	Polygonpen.CreatePen(PS_SOLID, 1, m_colorPolygon);
	oldpen = pDC->SelectObject(&pen);						// Pen ��ü ���
	pDC->SetROP2(R2_COPYPEN);

	CBrush brush, * oldbrush;
	CRect rectPoint;

	if (m_bHatch)
		brush.CreateHatchBrush(m_nHatchStyle, m_colorBrush);	// Hatch brush ��ü ����
	else
		brush.CreateSolidBrush(m_colorBrush);					// Solid brush ��ü ����
	oldbrush = pDC->SelectObject(&brush);						// brush ��ü ���

	switch (m_nDrawMode)
	{
	case LINE_MODE:				// ���� �׸���
		pDC->MoveTo(m_ptStart);
		pDC->LineTo(m_ptPrev);
		break;
	case ELLIPSE_MODE:			// �� �׸���
		pDC->Ellipse(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
		break;
	case POLYGON_MODE:			// �ٰ��� �׸���
		pDC->Polygon(m_ptData, m_nCount);
		break;
	case BEZIER_MODE:			// ������ � �׸���
		for (int i = 0; i < m_nCtrlPointNum; i++)
		{
			rectPoint = CRect(m_ptControl[i].x - 4, m_ptControl[i].y - 4, m_ptControl[i].x + 4, m_ptControl[i].y + 4);
			pDC->SelectObject(&Pointpen);
			pDC->Ellipse(&rectPoint);

		}
		pDC->SelectObject(&Polygonpen);
		pDC->Polyline(m_ptData, m_nCount);
		pDC->SelectObject(&Curvepen);
		pDC->PolyBezier(m_ptData, m_nCount);
		break;
	}
	pDC->SelectObject(oldpen);
	pDC->SelectObject(oldbrush);
	DeleteObject(pen);
	DeleteObject(Pointpen);
	DeleteObject(Polygonpen);
	DeleteObject(Curvepen);
	brush.DeleteObject();
}


// CPractice5_1View �μ�


void CPractice5_1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPractice5_1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CPractice5_1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CPractice5_1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CPractice5_1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPractice5_1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	if (m_bContextMenu == true)
	{
		//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
	}
	m_bContextMenu = true;
#endif
}


// CPractice5_1View ����

#ifdef _DEBUG
void CPractice5_1View::AssertValid() const
{
	CView::AssertValid();
}

void CPractice5_1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPractice5_1Doc* CPractice5_1View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPractice5_1Doc)));
	return (CPractice5_1Doc*)m_pDocument;
}
#endif //_DEBUG


// CPractice5_1View �޽��� ó����


void CPractice5_1View::OnLine()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// ���� �׸��� ��� ����
	m_nDrawMode = LINE_MODE;

	// ������������ ������ ����
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	// ���¹ٿ� �׸��� ��� ���
	pFrame->m_wndStatusBar.SetWindowTextW(_T("���� �׸���"));
}


void CPractice5_1View::OnEllipse()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// �� �׸��� ��� ����
	m_nDrawMode = ELLIPSE_MODE;

	// ������������ ������ ����
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	// ���¹ٿ� �׸��� ��� ���
	pFrame->m_wndStatusBar.SetWindowTextW(_T("�� �׸���"));
}


void CPractice5_1View::OnPolygon()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// �ٰ��� �׸��� ��� ����
	m_nDrawMode = POLYGON_MODE;

	// ������������ ������ ����
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	// ���¹ٿ� �׸��� ��� ���
	pFrame->m_wndStatusBar.SetWindowTextW(_T("�ٰ��� �׸���"));
}


void CPractice5_1View::OnLineColor()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CColorDialog dlgColor;					// ���� ��ȭ������ �ν��Ͻ� ����
	if (dlgColor.DoModal() == IDOK)			// ������ �����ϰ� Ȯ���� ������
	{
		m_colorPen = dlgColor.GetColor();	// ������ ���� ���� ��� colorPen�� ����
	}
	Invalidate(true);
}


void CPractice5_1View::OnFaceColor()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CColorDialog dlgColor;					// ���� ��ȭ������ �ν��Ͻ� ����
	if (dlgColor.DoModal() == IDOK)			// ������ �����ϰ� Ȯ���� ������
	{
		m_colorBrush = dlgColor.GetColor();	// ������ ���� ���� ��� colorBrush�� ����
	}
	m_bHatch = false;
	Invalidate(true);
}


void CPractice5_1View::OnBdiagonal()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// �귯�� ��Ÿ���� ���� 45���� ����
	m_nHatchStyle = HS_BDIAGONAL;
	m_bHatch = true;
	Invalidate(true);
}


void CPractice5_1View::OnCross()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// �귯�� ��Ÿ���� ���ڰ��� ����
	m_nHatchStyle = HS_CROSS;
	m_bHatch = true;
	Invalidate(true);
}


void CPractice5_1View::OnVertical()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// �귯�� ��Ÿ���� �������� ����
	m_nHatchStyle = HS_VERTICAL;
	m_bHatch = true;
	Invalidate(true);
}


void CPractice5_1View::OnUpdateLine(CCmdUI* pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	// ���� �׸��� ����̸� �޴��� üũ ǥ��
	pCmdUI->SetCheck(m_nDrawMode == LINE_MODE ? 1 : 0);
}


void CPractice5_1View::OnUpdateEllipse(CCmdUI* pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	// �� �׸��� ����̸� �޴��� üũ ǥ��
	pCmdUI->SetCheck(m_nDrawMode == ELLIPSE_MODE ? 1 : 0);
}


void CPractice5_1View::OnUpdatePolygon(CCmdUI* pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	// �ٰ��� �׸��� ����̸� �޴��� üũ ǥ��
	pCmdUI->SetCheck(m_nDrawMode == POLYGON_MODE ? 1 : 0);
}


void CPractice5_1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CClientDC dc(this);							// Ŭ���̾�Ʈ ��ü ����
	CPen pen, * oldpen;
	pen.CreatePen(PS_SOLID, 1, m_colorPen);		// Pen ��ü ����
	oldpen = dc.SelectObject(&pen);				// Pen ��ü ���

	dc.SetROP2(R2_NOTXORPEN);					// R2_NOTXORPEN���� ����

	CBrush brush, * oldbrush;
	if (m_bHatch)
		brush.CreateHatchBrush(m_nHatchStyle, m_colorBrush);	// Hatch Brush ��ü ����
	else
		brush.CreateSolidBrush(m_colorBrush);					// Solid Brush ��ü ����

	oldbrush = dc.SelectObject(&brush);							// brush ��ü ���

	switch (m_nDrawMode)
	{
	case LINE_MODE:			// ���� �׸���
		if (m_bLButtonDown)
		{
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptPrev);		// ���� ���� ����
			dc.MoveTo(m_ptStart);
			dc.LineTo(point);			// ���� ���� �׸�
			m_ptPrev = point;			// ���� ���� ���� ���� ����
		}
		break;

	case ELLIPSE_MODE:		// �� �׸���
		if (m_bLButtonDown)
		{
			dc.Ellipse(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
			dc.Ellipse(m_ptStart.x, m_ptStart.y, point.x, point.y);
			m_ptPrev = point;		    // ���� ���� ���� ���� ����
		}
		break;

	case POLYGON_MODE:		// �ٰ��� �׸���
		if (!m_bFirst)
		{
			dc.SetROP2(R2_NOT);
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptPrev);
			dc.MoveTo(m_ptStart);
			dc.LineTo(point);
			m_ptPrev = point;			// ���� ���� ���� ���� ����
		}
		break;

	case BEZIER_MODE:		// ������ � �׸���
		if (!m_bFirst)
		{
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptPrev);
			dc.MoveTo(m_ptStart);
			dc.LineTo(point);
			m_ptPrev = point;			// ���� ���� ���� ���� ����
		}
		break;
	}
	dc.SelectObject(oldpen);		// ���� pen���� ����
	dc.SelectObject(oldbrush);		// ���� brush�� ����
	pen.DeleteObject();				// pen ��ü ����
	brush.DeleteObject();			// brush ��ü ����

	//������������ ������ ����
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CString strPoint;
	strPoint.Format(_T("���콺 ��ġ x : %d, y : %d"), point.x, point.y);
	//���� �߰��� �ҿ� ���콺 ��ġ ���
	pFrame->m_wndStatusBar.SetPaneText(1, strPoint);

	CView::OnMouseMove(nFlags, point);
}


void CPractice5_1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_bFirst)
	{
		m_ptStart = m_ptPrev = 0;
		m_bLButtonDown = false;
		m_bFirst = true;
		m_nCount = 0;
		m_nCtrlPointNum = 0;
		for (int i = 0; i < 50; i++) {
			m_ptData[i] = 0;
			m_ptControl[i] = 0;
		}
		Invalidate(true);	// ȭ�� ����
	}
	CRect rectPoint(point.x - 4, point.y - 4, point.x + 4, point.y + 4);

	switch (m_nDrawMode)
	{
	case LINE_MODE:					// ���� �׸���
	case ELLIPSE_MODE:				// �� �׸���
		m_bLButtonDown = true;
		m_ptStart = m_ptPrev = point;
		m_bFirst = false;
		break;
	case POLYGON_MODE:				// �ٰ��� �׸���
		if (m_bFirst == true)
			m_bFirst = false;
		m_ptStart = m_ptPrev = point;
		m_ptData[m_nCount] = point;
		m_nCount++;
		break;
	case BEZIER_MODE:				// ������ � �׸���
		CClientDC dc(this);
		CPen newpen, * oldpen;
		newpen.CreatePen(PS_SOLID, 7, m_colorPoint);
		oldpen = dc.SelectObject(&newpen);

		dc.Ellipse(&rectPoint);
		dc.SelectObject(oldpen);
		DeleteObject(newpen);

		if (m_bFirst == true)
			m_bFirst = false;
		m_ptStart = m_ptPrev = point;
		m_ptData[m_nCount] = point;
		m_nCount++;
		m_ptControl[m_nCtrlPointNum++] = point;
		break;
	}

	RECT rectClient;				// ����ü ���� ����
	SetCapture();					// ���콺 ĸó
	GetClientRect(&rectClient);		// Ŭ���̾�Ʈ ���� ����
	ClientToScreen(&rectClient);	// ��ũ�� ��ǥ�� ��ȯ
	::ClipCursor(&rectClient);		// ���콺 �̵������� Ŭ���̾�Ʈ �������� ����

	CView::OnLButtonDown(nFlags, point);
}


void CPractice5_1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_bLButtonDown)
	{
		// �׸��� ��尡 ���� �׸���, �� �׸����̸�
		if (m_nDrawMode == LINE_MODE | m_nDrawMode == ELLIPSE_MODE)
		{
			m_bLButtonDown = false;
			m_bFirst = true;
			ReleaseCapture();
			::ClipCursor(NULL);
			Invalidate(true);
		}
	}

	CView::OnLButtonUp(nFlags, point);
}


void CPractice5_1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if (m_nDrawMode == POLYGON_MODE)		// �ٰ��� �׸���
	{
		if (!m_bFirst)						// ó�� �׸��� ���� �ƴϸ�
		{
			m_bContextMenu = false;			// ���ؽ�Ʈ �޴� ��Ȱ��
			// �迭�� ���� ���� �����ϰ� ī��Ʈ ����
			m_ptData[m_nCount] = point;
			m_nCount++;
			
			// üũ���� �ʱ�ȭ
			m_bFirst = true;
			ReleaseCapture();			// ���콺 ĸó ����
			::ClipCursor(NULL);			// ���콺 Ŭ�� ����
			Invalidate(true);			// ȭ�� ����
		}
	}
	else if (m_nDrawMode == BEZIER_MODE)	// ������ � �׸���
	{
		if (m_nCtrlPointNum > 1)
		{
			if (!m_bFirst)					// ó�� �׸��� ���� �ƴϸ�
			{
				m_ptControl[m_nCtrlPointNum++] = point;
				CRect rectPoint(point.x - 4, point.y - 4, point.x + 4, point.y + 4);
				CClientDC dc(this);
				CPen newpen, * oldpen;
				newpen.CreatePen(PS_SOLID, 7, m_colorPoint);
				oldpen = dc.SelectObject(&newpen);
				dc.Ellipse(&rectPoint);
				dc.SelectObject(oldpen);
				DeleteObject(newpen);

				m_bContextMenu = false;		// ���ؽ�Ʈ �޴� ��Ȱ��
				// �迭�� ���� ���� �����ϰ� ī��Ʈ ����
				m_ptData[m_nCount] = point;
				m_nCount++;
				// üũ���� �ʱ�ȭ
				m_bFirst = true;
				ReleaseCapture();			// ���콺 ĸó ����
				::ClipCursor(NULL);			// ���콺 Ŭ�� ����
				Invalidate(true);			// ȭ�� ����

			}
			else
			{
				m_ptControl[m_nCtrlPointNum++] = point;
				CRect rectPoint(point.x - 4, point.y - 4, point.x + 4, point.y + 4);
				CClientDC dc(this);
				CPen newpen, * oldpen;
				newpen.CreatePen(PS_SOLID, 7, m_colorPoint);
				oldpen = dc.SelectObject(&newpen);
				dc.Ellipse(&rectPoint);
				dc.SelectObject(oldpen);
				DeleteObject(newpen);

				AfxMessageBox(_T("���� �� ���� <���� ��=������ � ��*3+1>"), MB_OK | MB_ICONWARNING);

				m_bContextMenu = false;
				// �迭�� ���� ���� �����ϰ� ī��Ʈ ����
				m_ptData[m_nCount] = point;
				m_nCount++;

				ReleaseCapture();
				::ClipCursor(NULL);
				Invalidate(true);
			}
		}
		else 
			AfxMessageBox(_T("���� �� ���� <���� ��=������ � ��*3+1>"), MB_OK | MB_ICONWARNING);

	}

	CView::OnRButtonDown(nFlags, point);
}


void CPractice5_1View::OnBezier()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// ������ � �׸��� ��� ����
	m_nDrawMode = BEZIER_MODE;
	m_nCtrlPointNum = m_nCount * 3 + 1;

	// ������������ ������ ����
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	// ���¹ٿ� �׸��� ��� ���
	pFrame->m_wndStatusBar.SetWindowTextW(_T("������ � �׸���"));
}


void CPractice5_1View::OnUpdateBezier(CCmdUI* pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	// ������ � �׸��� ����̸� �޴��� üũ ǥ��
	pCmdUI->SetCheck(m_nDrawMode == BEZIER_MODE ? 1 : 0);
}
