
// Practice3_3View.cpp: CPractice3_3View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Practice3_3.h"
#endif

#include "Practice3_3Doc.h"
#include "Practice3_3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPractice3_3View

IMPLEMENT_DYNCREATE(CPractice3_3View, CView)

BEGIN_MESSAGE_MAP(CPractice3_3View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CPractice3_3View 생성/소멸

CPractice3_3View::CPractice3_3View() noexcept
	: m_strOutput(_T(""))
	, m_ptLocation(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CPractice3_3View::~CPractice3_3View()
{
}

BOOL CPractice3_3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPractice3_3View 그리기

void CPractice3_3View::OnDraw(CDC* pDC)
{
	CPractice3_3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	pDC->TextOutW(m_ptLocation.x, m_ptLocation.y, m_strOutput);
}


// CPractice3_3View 인쇄

BOOL CPractice3_3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CPractice3_3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPractice3_3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CPractice3_3View 진단

#ifdef _DEBUG
void CPractice3_3View::AssertValid() const
{
	CView::AssertValid();
}

void CPractice3_3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPractice3_3Doc* CPractice3_3View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPractice3_3Doc)));
	return (CPractice3_3Doc*)m_pDocument;
}
#endif //_DEBUG


// CPractice3_3View 메시지 처리기


void CPractice3_3View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int nCharIndex;
	nCharIndex = m_strOutput.GetLength();

	if (nChar == VK_BACK)
		m_strOutput.Delete(nCharIndex - 1, 1);
	else
		m_strOutput += (WCHAR)nChar;

	Invalidate();
	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CPractice3_3View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar)
	{
		case VK_LEFT:
			m_ptLocation.x--;
			break;
		case VK_RIGHT:
			m_ptLocation.x++;
			break;
		case VK_UP:
			m_ptLocation.y--;
			break;
		case VK_DOWN:
			m_ptLocation.y++;
			break;
		case VK_PRIOR:
			m_ptLocation.y -= 50;
			break;
		case VK_NEXT:
			m_ptLocation.y += 50;
			break;
		case VK_HOME:
			m_ptLocation = CPoint(0, 0);
		break;
	}

	if (m_ptLocation.x < 0)
	{
		m_ptLocation.x = 0;
		AfxMessageBox(_T("왼쪽으로 더 이상 이동할 수 없습니다."));
	}
	if (m_ptLocation.y < 0)
	{
		m_ptLocation.y = 0;
		AfxMessageBox(_T("위쪽으로 더 이상 이동할 수 없습니다."));
	}
	if (m_ptLocation.x > m_ptClientSize.x)
	{
		m_ptLocation.x = m_ptClientSize.x;
		AfxMessageBox(_T("오른쪽으로 더 이상 이동할 수 없습니다."));
	}
	if (m_ptLocation.y > m_ptClientSize.y)
	{
		m_ptLocation.y = m_ptClientSize.y;
		AfxMessageBox(_T("아래쪽으로 더 이상 이동할 수 없습니다."));
	}
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CPractice3_3View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_ptClientSize.x = cx;
	m_ptClientSize.y = cy;

	Invalidate();
}


void CPractice3_3View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_ptLocation.x = point.x;
	m_ptLocation.y = point.y;
	Invalidate();

	CView::OnLButtonDown(nFlags, point);
}


void CPractice3_3View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_strOutput.IsEmpty() == false)
	{
		if (AfxMessageBox(_T("문자를 모두 지우시겠습니까?"),
			MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			m_strOutput.Empty();
		}
	}
	else
	{
		AfxMessageBox(_T("문자열을 입력하시오"));
	}
	Invalidate();

	CView::OnRButtonDown(nFlags, point);
}
