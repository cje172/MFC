
// Practice5_1View.cpp : CPractice5_1View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
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

// CPractice5_1View 생성/소멸

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
	// TODO: 여기에 생성 코드를 추가합니다.
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
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPractice5_1View 그리기

void CPractice5_1View::OnDraw(CDC* pDC)
{
	CPractice5_1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CPen pen, * oldpen, Pointpen, Curvepen, Polygonpen;
	pen.CreatePen(PS_SOLID, 1, m_colorPen);					// Pen 객체 생성
	Pointpen.CreatePen(PS_SOLID, 7, m_colorPoint);
	Curvepen.CreatePen(PS_SOLID, 1, m_colorCurve);
	Polygonpen.CreatePen(PS_SOLID, 1, m_colorPolygon);
	oldpen = pDC->SelectObject(&pen);						// Pen 객체 등록
	pDC->SetROP2(R2_COPYPEN);

	CBrush brush, * oldbrush;
	CRect rectPoint;

	if (m_bHatch)
		brush.CreateHatchBrush(m_nHatchStyle, m_colorBrush);	// Hatch brush 객체 생성
	else
		brush.CreateSolidBrush(m_colorBrush);					// Solid brush 객체 생성
	oldbrush = pDC->SelectObject(&brush);						// brush 객체 등록

	switch (m_nDrawMode)
	{
	case LINE_MODE:				// 직선 그리기
		pDC->MoveTo(m_ptStart);
		pDC->LineTo(m_ptPrev);
		break;
	case ELLIPSE_MODE:			// 원 그리기
		pDC->Ellipse(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
		break;
	case POLYGON_MODE:			// 다각형 그리기
		pDC->Polygon(m_ptData, m_nCount);
		break;
	case BEZIER_MODE:			// 베지어 곡선 그리기
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


// CPractice5_1View 인쇄


void CPractice5_1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPractice5_1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CPractice5_1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPractice5_1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
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


// CPractice5_1View 진단

#ifdef _DEBUG
void CPractice5_1View::AssertValid() const
{
	CView::AssertValid();
}

void CPractice5_1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPractice5_1Doc* CPractice5_1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPractice5_1Doc)));
	return (CPractice5_1Doc*)m_pDocument;
}
#endif //_DEBUG


// CPractice5_1View 메시지 처리기


void CPractice5_1View::OnLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 직선 그리기 모드 변경
	m_nDrawMode = LINE_MODE;

	// 메인프레임의 포인터 얻음
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	// 상태바에 그리기 모드 출력
	pFrame->m_wndStatusBar.SetWindowTextW(_T("직선 그리기"));
}


void CPractice5_1View::OnEllipse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 원 그리기 모드 변경
	m_nDrawMode = ELLIPSE_MODE;

	// 메인프레임의 포인터 얻음
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	// 상태바에 그리기 모드 출력
	pFrame->m_wndStatusBar.SetWindowTextW(_T("원 그리기"));
}


void CPractice5_1View::OnPolygon()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 다각형 그리기 모드 변경
	m_nDrawMode = POLYGON_MODE;

	// 메인프레임의 포인터 얻음
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	// 상태바에 그리기 모드 출력
	pFrame->m_wndStatusBar.SetWindowTextW(_T("다각형 그리기"));
}


void CPractice5_1View::OnLineColor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorDialog dlgColor;					// 색상 대화상자의 인스턴스 생성
	if (dlgColor.DoModal() == IDOK)			// 색상을 선택하고 확인을 누르면
	{
		m_colorPen = dlgColor.GetColor();	// 선택한 색상 값을 얻어 colorPen에 설정
	}
	Invalidate(true);
}


void CPractice5_1View::OnFaceColor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorDialog dlgColor;					// 색상 대화상자의 인스턴스 생성
	if (dlgColor.DoModal() == IDOK)			// 색상을 선택하고 확인을 누르면
	{
		m_colorBrush = dlgColor.GetColor();	// 선택한 색상 값을 얻어 colorBrush에 설정
	}
	m_bHatch = false;
	Invalidate(true);
}


void CPractice5_1View::OnBdiagonal()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 브러시 스타일을 왼쪽 45도로 변경
	m_nHatchStyle = HS_BDIAGONAL;
	m_bHatch = true;
	Invalidate(true);
}


void CPractice5_1View::OnCross()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 브러시 스타일을 십자가로 변경
	m_nHatchStyle = HS_CROSS;
	m_bHatch = true;
	Invalidate(true);
}


void CPractice5_1View::OnVertical()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 브러시 스타일을 수직으로 변경
	m_nHatchStyle = HS_VERTICAL;
	m_bHatch = true;
	Invalidate(true);
}


void CPractice5_1View::OnUpdateLine(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	// 직선 그리기 모드이면 메뉴에 체크 표시
	pCmdUI->SetCheck(m_nDrawMode == LINE_MODE ? 1 : 0);
}


void CPractice5_1View::OnUpdateEllipse(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	// 원 그리기 모드이면 메뉴에 체크 표시
	pCmdUI->SetCheck(m_nDrawMode == ELLIPSE_MODE ? 1 : 0);
}


void CPractice5_1View::OnUpdatePolygon(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	// 다각형 그리기 모드이면 메뉴에 체크 표시
	pCmdUI->SetCheck(m_nDrawMode == POLYGON_MODE ? 1 : 0);
}


void CPractice5_1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);							// 클라이언트 객체 얻음
	CPen pen, * oldpen;
	pen.CreatePen(PS_SOLID, 1, m_colorPen);		// Pen 객체 생성
	oldpen = dc.SelectObject(&pen);				// Pen 객체 등록

	dc.SetROP2(R2_NOTXORPEN);					// R2_NOTXORPEN으로 설정

	CBrush brush, * oldbrush;
	if (m_bHatch)
		brush.CreateHatchBrush(m_nHatchStyle, m_colorBrush);	// Hatch Brush 객체 생성
	else
		brush.CreateSolidBrush(m_colorBrush);					// Solid Brush 객체 생성

	oldbrush = dc.SelectObject(&brush);							// brush 객체 등록

	switch (m_nDrawMode)
	{
	case LINE_MODE:			// 직선 그리기
		if (m_bLButtonDown)
		{
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptPrev);		// 이전 직선 지움
			dc.MoveTo(m_ptStart);
			dc.LineTo(point);			// 현재 직선 그림
			m_ptPrev = point;			// 이전 점에 현재 점을 저장
		}
		break;

	case ELLIPSE_MODE:		// 원 그리기
		if (m_bLButtonDown)
		{
			dc.Ellipse(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
			dc.Ellipse(m_ptStart.x, m_ptStart.y, point.x, point.y);
			m_ptPrev = point;		    // 이전 점에 현재 점을 저장
		}
		break;

	case POLYGON_MODE:		// 다각형 그리기
		if (!m_bFirst)
		{
			dc.SetROP2(R2_NOT);
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptPrev);
			dc.MoveTo(m_ptStart);
			dc.LineTo(point);
			m_ptPrev = point;			// 이전 점에 현재 점을 저장
		}
		break;

	case BEZIER_MODE:		// 베지어 곡선 그리기
		if (!m_bFirst)
		{
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptPrev);
			dc.MoveTo(m_ptStart);
			dc.LineTo(point);
			m_ptPrev = point;			// 이전 점에 현재 점을 저장
		}
		break;
	}
	dc.SelectObject(oldpen);		// 이전 pen으로 설정
	dc.SelectObject(oldbrush);		// 이전 brush로 설정
	pen.DeleteObject();				// pen 객체 삭제
	brush.DeleteObject();			// brush 객체 삭제

	//메인프레임의 포인터 얻음
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CString strPoint;
	strPoint.Format(_T("마우스 위치 x : %d, y : %d"), point.x, point.y);
	//새로 추가한 팬에 마우스 위치 출력
	pFrame->m_wndStatusBar.SetPaneText(1, strPoint);

	CView::OnMouseMove(nFlags, point);
}


void CPractice5_1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
		Invalidate(true);	// 화면 갱신
	}
	CRect rectPoint(point.x - 4, point.y - 4, point.x + 4, point.y + 4);

	switch (m_nDrawMode)
	{
	case LINE_MODE:					// 직선 그리기
	case ELLIPSE_MODE:				// 원 그리기
		m_bLButtonDown = true;
		m_ptStart = m_ptPrev = point;
		m_bFirst = false;
		break;
	case POLYGON_MODE:				// 다각형 그리기
		if (m_bFirst == true)
			m_bFirst = false;
		m_ptStart = m_ptPrev = point;
		m_ptData[m_nCount] = point;
		m_nCount++;
		break;
	case BEZIER_MODE:				// 베지어 곡선 그리기
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

	RECT rectClient;				// 구조체 변수 선언
	SetCapture();					// 마우스 캡처
	GetClientRect(&rectClient);		// 클라이언트 영역 받음
	ClientToScreen(&rectClient);	// 스크린 좌표계 변환
	::ClipCursor(&rectClient);		// 마우스 이동범위를 클라이언트 영역으로 제한

	CView::OnLButtonDown(nFlags, point);
}


void CPractice5_1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bLButtonDown)
	{
		// 그리기 모드가 직선 그리기, 원 그리기이면
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_nDrawMode == POLYGON_MODE)		// 다각형 그리기
	{
		if (!m_bFirst)						// 처음 그리는 것이 아니면
		{
			m_bContextMenu = false;			// 컨텍스트 메뉴 비활성
			// 배열에 현재 점을 저장하고 카운트 증가
			m_ptData[m_nCount] = point;
			m_nCount++;
			
			// 체크변수 초기화
			m_bFirst = true;
			ReleaseCapture();			// 마우스 캡처 해제
			::ClipCursor(NULL);			// 마우스 클립 해제
			Invalidate(true);			// 화면 갱신
		}
	}
	else if (m_nDrawMode == BEZIER_MODE)	// 베지어 곡선 그리기
	{
		if (m_nCtrlPointNum > 1)
		{
			if (!m_bFirst)					// 처음 그리는 것이 아니면
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

				m_bContextMenu = false;		// 컨텍스트 메뉴 비활성
				// 배열에 현재 점을 저장하고 카운트 증가
				m_ptData[m_nCount] = point;
				m_nCount++;
				// 체크변수 초기화
				m_bFirst = true;
				ReleaseCapture();			// 마우스 캡처 해제
				::ClipCursor(NULL);			// 마우스 클립 해제
				Invalidate(true);			// 화면 갱신

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

				AfxMessageBox(_T("점의 수 오류 <점의 수=베지어 곡선 수*3+1>"), MB_OK | MB_ICONWARNING);

				m_bContextMenu = false;
				// 배열에 현재 점을 저장하고 카운트 증가
				m_ptData[m_nCount] = point;
				m_nCount++;

				ReleaseCapture();
				::ClipCursor(NULL);
				Invalidate(true);
			}
		}
		else 
			AfxMessageBox(_T("점의 수 오류 <점의 수=베지어 곡선 수*3+1>"), MB_OK | MB_ICONWARNING);

	}

	CView::OnRButtonDown(nFlags, point);
}


void CPractice5_1View::OnBezier()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 베지어 곡선 그리기 모드 변경
	m_nDrawMode = BEZIER_MODE;
	m_nCtrlPointNum = m_nCount * 3 + 1;

	// 메인프레임의 포인터 얻음
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	// 상태바에 그리기 모드 출력
	pFrame->m_wndStatusBar.SetWindowTextW(_T("베지어 곡선 그리기"));
}


void CPractice5_1View::OnUpdateBezier(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	// 베지어 곡선 그리기 모드이면 메뉴에 체크 표시
	pCmdUI->SetCheck(m_nDrawMode == BEZIER_MODE ? 1 : 0);
}
