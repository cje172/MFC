
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
END_MESSAGE_MAP()

// CPractice5_1View 생성/소멸

CPractice5_1View::CPractice5_1View()
	: m_nDrawMode(0)
	, m_nHatchStyle(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.

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

void CPractice5_1View::OnDraw(CDC* /*pDC*/)
{
	CPractice5_1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
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
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
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
	// 직선그리기 모드 변경
	m_nDrawMode = LINE_MODE;

	// 메인프레임의 포인터 얻음
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	// 상태바에 그리기 모드 출력
	pFrame->m_wndStatusBar.SetWindowText(_T("직선 그리기"));
}


void CPractice5_1View::OnEllipse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 원 그리기 모드 변경 
	m_nDrawMode = ELLIPSE_MODE;

	// 메인프레임의 포인터 얻음
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	// 상태바에 그리기 모드 출력
	pFrame->m_wndStatusBar.SetWindowText(_T("원 그리기"));
}


void CPractice5_1View::OnPolygon()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 다각형 그리기 모드 변경
	m_nDrawMode = POLYGON_MODE;

	// 메인프레임의 포인터 얻음
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	// 상태바에 그리기 모드 출력
	pFrame->m_wndStatusBar.SetWindowText(_T("다각형그리기"));
}


void CPractice5_1View::OnLineColor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 선 색상 메뉴를 선택했을 때 메시지 출력
	AfxMessageBox(_T("선의 색상을 변경합니다."));
}


void CPractice5_1View::OnFaceColor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 면 색상 메뉴를 선택했을 때 메시지 출력
	AfxMessageBox(_T("면의 색상을 변경합니다."));
}


void CPractice5_1View::OnBdiagonal()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 왼쪽 45도 빗금 변경
	m_nHatchStyle = HS_BDIAGONAL;
}


void CPractice5_1View::OnCross()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 십자가 빗금 변경
	m_nHatchStyle = HS_CROSS;
}


void CPractice5_1View::OnVertical()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 수직 빗금 변경
	m_nHatchStyle = HS_VERTICAL;
}


void CPractice5_1View::OnUpdateLine(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	// 직선 그리기 모드이면 메뉴에 체크 표시 
	pCmdUI->SetCheck(m_nDrawMode == LINE_MODE ? 1 : 0);
}


void CPractice5_1View::OnUpdateEllipse(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	// 원 그리기 모드이면 메뉴에 체크 표시 
	pCmdUI->SetCheck(m_nDrawMode == ELLIPSE_MODE ? 1 : 0);
}


void CPractice5_1View::OnUpdatePolygon(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	// 다각형 그리기 모드이면 메뉴에 체크 표시
	pCmdUI->SetCheck(m_nDrawMode == POLYGON_MODE ? 1 : 0);
}


void CPractice5_1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// 메인프레임의 포인터 얻음
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();

	CString strPoint;
	strPoint.Format(_T("마우스 위치 x : %d, y : %d"), point.x, point.y);

	// 새로 추가한 팬에 마우스 위치 출력
	pFrame->m_wndStatusBar.SetPaneText(1, strPoint);
	CView::OnMouseMove(nFlags, point);
}
