
// Practice6_1View.cpp : CPractice6_1View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
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

// CPractice6_1View 생성/소멸

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
	m_nDrawMode = LINE_MODE;				// 그리기 모드 중에서 펜으로 그리기 초기화
	m_bContextMenu = true;					// 컨텍스트 메뉴를 활성으로 초기화
	m_bFirst = true;						// 처음 그리는 것으로 초기화
	m_bLButtonDown = false;					// 왼쪽 버튼이 눌리지 않은 것으로 초기화
	m_nCount = 0;							// 다각형 점을 저장할 배열의 카운트 초기화
	for (int i = 0; i < 50; i++)		 	// 다각형의 점을 저장할 배열 초기화
		m_ptData[i] = 0;
	m_bHatch = false;						// 해치 브러쉬를 십자가 빗금으로 초기화
	m_nHatchStyle = HS_CROSS;
	m_colorPen = RGB(0, 0, 0);				// pen color를 검은색으로 초기화
	m_colorBrush = RGB(255, 255, 255);		// brush color를 흰색으로 초기화
}

CPractice6_1View::~CPractice6_1View()
{
}

BOOL CPractice6_1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPractice5_1View 그리기

void CPractice6_1View::OnDraw(CDC* pDC)
{
	CPractice6_1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CPen pen, *oldpen;								
	pen.CreatePen(PS_SOLID, 1, m_colorPen);				// pen 객체 생성
	oldpen = pDC->SelectObject(&pen);					// pen 객체 등록		
	pDC->SetROP2(R2_COPYPEN);							// COPYPEN으로 설정
	CBrush brush, * oldbrush;
	if (m_bHatch)
		brush.CreateHatchBrush(m_nHatchStyle, m_colorBrush);	// Hatch brush 객체 생성
	else
		brush.CreateSolidBrush(m_colorBrush);					// Solid brush 객체 생성
	oldbrush = pDC->SelectObject(&brush);						// brush 객체 등록

	switch (m_nDrawMode)
	{
	case LINE_MODE:			// 직선 그리기
		pDC->MoveTo(m_ptStart);
		pDC->LineTo(m_ptPrev);
		break;
	case ELLIPSE_MODE:		// 원 그리기
		pDC->Ellipse(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
		break;
	case POLYGON_MODE:		// 다각형 그리기
		// 배열에 저장한 순서대로 연결해 마지막 다각형 그리기
		pDC->Polygon(m_ptData, m_nCount);
		break;
	}
	pDC->SelectObject(oldpen);		// 이전 pen으로 설정
	pDC->SelectObject(oldbrush);	// 이전 brush으로 설정
	pen.DeleteObject();				// pen 객체 삭제
	brush.DeleteObject();			// brush 객체 삭제
}


// CPractice5_1View 인쇄


void CPractice6_1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPractice6_1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CPractice6_1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPractice6_1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
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


// CPractice6_1View 진단

#ifdef _DEBUG
void CPractice6_1View::AssertValid() const
{
	CView::AssertValid();
}

void CPractice6_1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPractice6_1Doc* CPractice6_1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPractice6_1Doc)));
	return (CPractice6_1Doc*)m_pDocument;
}
#endif //_DEBUG


// CPractice6_1View 메시지 처리기


void CPractice6_1View::OnLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 직선그리기 모드 변경
	m_nDrawMode = LINE_MODE;

	// 메인프레임의 포인터 얻음
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	// 상태바에 그리기 모드 출력
	pFrame->m_wndStatusBar.SetWindowText(_T("직선 그리기"));
}


void CPractice6_1View::OnEllipse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 원 그리기 모드 변경 
	m_nDrawMode = ELLIPSE_MODE;

	// 메인프레임의 포인터 얻음
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	// 상태바에 그리기 모드 출력
	pFrame->m_wndStatusBar.SetWindowText(_T("원 그리기"));
}


void CPractice6_1View::OnPolygon()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 다각형 그리기 모드 변경
	m_nDrawMode = POLYGON_MODE;

	// 메인프레임의 포인터 얻음
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	// 상태바에 그리기 모드 출력
	pFrame->m_wndStatusBar.SetWindowText(_T("다각형그리기"));
}


void CPractice6_1View::OnLineColor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorDialog dlgColor;				// 색상 대화상자의 인스턴스 생성
	if (dlgColor.DoModal() == IDOK)		// 색상을 선택하고 확인을 누르면
	{
		m_colorPen = dlgColor.GetColor();		// 선택한 색상 값을 얻어 colorPen에 설정
	}
	Invalidate(true);
}


void CPractice6_1View::OnFaceColor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorDialog dlgColor;				// 색상 대화상자의 인스턴스 생성
	if (dlgColor.DoModal() == IDOK)		// 색상을 선택하고 확인을 누르면
	{
		m_colorBrush = dlgColor.GetColor();		// 선택한 색상 값을 얻어 colorBrush에 설정
	}
	Invalidate(true);
}


void CPractice6_1View::OnBdiagonal()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 왼쪽 45도 빗금 변경
	m_nHatchStyle = HS_BDIAGONAL;
	m_bHatch = true;
	Invalidate(true);
}


void CPractice6_1View::OnCross()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 십자가 빗금 변경
	m_nHatchStyle = HS_CROSS;
	m_bHatch = true;
	Invalidate(true);
}


void CPractice6_1View::OnVertical()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 수직 빗금 변경
	m_nHatchStyle = HS_VERTICAL;
	m_bHatch = true;
	Invalidate(true);
}


void CPractice6_1View::OnUpdateLine(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	// 직선 그리기 모드이면 메뉴에 체크 표시 
	pCmdUI->SetCheck(m_nDrawMode == LINE_MODE ? 1 : 0);
}


void CPractice6_1View::OnUpdateEllipse(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	// 원 그리기 모드이면 메뉴에 체크 표시 
	pCmdUI->SetCheck(m_nDrawMode == ELLIPSE_MODE ? 1 : 0);
}


void CPractice6_1View::OnUpdatePolygon(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	// 다각형 그리기 모드이면 메뉴에 체크 표시
	pCmdUI->SetCheck(m_nDrawMode == POLYGON_MODE ? 1 : 0);
}


void CPractice6_1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);  // 클라이언트 객체 얻음
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

	// 메인 프레임의 포인터 얻음
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CString strPoint;
	strPoint.Format(_T("마우스 위치 x : %d, y : %d"), point.x, point.y);
	// 새로 추가한 팬에 마우스 위치 출력
	pFrame->m_wndStatusBar.SetPaneText(1, strPoint);

	CView::OnMouseMove(nFlags, point);
}


void CPractice6_1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 각 변수들 초기화
	if (m_bFirst)
	{
		m_ptStart = m_ptPrev = 0;
		m_bLButtonDown = false;
		m_nCount = 0;
		for (int i = 0; i < 50; i++)
			m_ptData[i] = 0;
		Invalidate(true);  // 화면갱신
	}

	switch (m_nDrawMode)
	{
	case LINE_MODE:				// 직선 그리기
	case ELLIPSE_MODE:			// 원 그리기
		m_bLButtonDown = true;
		m_ptStart = m_ptPrev = point;
		m_bFirst = false;
		break;
	case POLYGON_MODE:			// 다각형 그리기
		if (m_bFirst == true)
			m_bFirst = false;
		m_ptStart = m_ptPrev = point;
		m_ptData[m_nCount] = point;
		m_nCount++;
		break;
	}

	RECT rectClient;				// 구조체 변수 선언
	SetCapture();					// 마우스 캡처
	GetClientRect(&rectClient);		// 클라이언트 영역 받음
	ClientToScreen(&rectClient);	// 스크린 좌표계 변환
	::ClipCursor(&rectClient);		// 마우스 이동범위를 클라이언트 영역으로 제한

	CView::OnLButtonDown(nFlags, point);
}


void CPractice6_1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bLButtonDown)				// 왼쪽 마우스 버튼이 눌린 상태이면
	{
		// 그리기 모드가 직선 그리기, 원 그리기 이면
		if (m_nDrawMode == LINE_MODE || m_nDrawMode == ELLIPSE_MODE)
		{
			m_bLButtonDown = false;
			m_bFirst = true;
			ReleaseCapture();		// 마우스 캡처 해제
			::ClipCursor(NULL);		// 마우스 클립 해제
			Invalidate(true);		// 화면 갱신
		}
	}

	CView::OnLButtonUp(nFlags, point);
}


void CPractice6_1View::OnNcRButtonDown(UINT nHitTest, CPoint point)
{
	// 다각형 그리기
	if (m_nDrawMode == POLYGON_MODE)
	{
		if (!m_bFirst)
		{
			m_bContextMenu = FALSE;
			// 배열에 현재 점을 저장하고 카운트 증가
			m_ptData[m_nCount] = point;
			m_nCount++;
			// 체크변수 초기화 => 다시 다각형을 그리기 위해
			m_bFirst = TRUE;
			ReleaseCapture();		// 마우스 캡처 해제
			::ClipCursor(NULL);		// 마우스 클립 해제
			Invalidate(TRUE);		// 화면갱신
		}
	}

	CView::OnNcRButtonDown(nHitTest, point);
}
