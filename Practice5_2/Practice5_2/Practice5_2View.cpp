
// Practice5_2View.cpp: CPractice5_2View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Practice5_2.h"
#endif

#include "Practice5_2Doc.h"
#include "Practice5_2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPractice5_2View

IMPLEMENT_DYNCREATE(CPractice5_2View, CView)

BEGIN_MESSAGE_MAP(CPractice5_2View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPractice5_2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_LINE, &CPractice5_2View::OnLine)
	ON_COMMAND(ID_ELLIPSE, &CPractice5_2View::OnEllipse)
	ON_COMMAND(ID_POLYGON, &CPractice5_2View::OnPolygon)
	ON_COMMAND(ID_LINE_COLOR, &CPractice5_2View::OnLineColor)
	ON_COMMAND(ID_FACE_COLOR, &CPractice5_2View::OnFaceColor)
	ON_COMMAND(ID_BDIAGONAL, &CPractice5_2View::OnBdiagonal)
	ON_COMMAND(ID_CROSS, &CPractice5_2View::OnCross)
	ON_COMMAND(ID_VERTICAL, &CPractice5_2View::OnVertical)
	ON_UPDATE_COMMAND_UI(ID_LINE, &CPractice5_2View::OnUpdateLine)
	ON_UPDATE_COMMAND_UI(ID_ELLIPSE, &CPractice5_2View::OnUpdateEllipse)
	ON_UPDATE_COMMAND_UI(ID_POLYGON, &CPractice5_2View::OnUpdatePolygon)
END_MESSAGE_MAP()

// CPractice5_2View 생성/소멸

CPractice5_2View::CPractice5_2View() noexcept
	: m_nDrawMode(0)
	, m_nHatchStyle(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CPractice5_2View::~CPractice5_2View()
{
}

BOOL CPractice5_2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPractice5_2View 그리기

void CPractice5_2View::OnDraw(CDC* /*pDC*/)
{
	CPractice5_2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CPractice5_2View 인쇄


void CPractice5_2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPractice5_2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CPractice5_2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPractice5_2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CPractice5_2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPractice5_2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPractice5_2View 진단

#ifdef _DEBUG
void CPractice5_2View::AssertValid() const
{
	CView::AssertValid();
}

void CPractice5_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPractice5_2Doc* CPractice5_2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPractice5_2Doc)));
	return (CPractice5_2Doc*)m_pDocument;
}
#endif //_DEBUG


// CPractice5_2View 메시지 처리기


void CPractice5_2View::OnLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = LINE_MODE;
}


void CPractice5_2View::OnEllipse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = ELLIPSE_MODE;
}


void CPractice5_2View::OnPolygon()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = POLYGON_MODE;
}


void CPractice5_2View::OnLineColor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	AfxMessageBox(_T("선의 색상을 변경합니다."));
}


void CPractice5_2View::OnFaceColor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	AfxMessageBox(_T("면의 색상을 변경합니다."));
}


void CPractice5_2View::OnBdiagonal()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nHatchStyle = HS_BDIAGONAL;
}


void CPractice5_2View::OnCross()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nHatchStyle = HS_CROSS;
}


void CPractice5_2View::OnVertical()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nHatchStyle = HS_VERTICAL;
}


void CPractice5_2View::OnUpdateLine(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nDrawMode == LINE_MODE ? 1 : 0);
}


void CPractice5_2View::OnUpdateEllipse(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nDrawMode == ELLIPSE_MODE ? 1 : 0);
}


void CPractice5_2View::OnUpdatePolygon(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nDrawMode == POLYGON_MODE ? 1 : 0);
}
