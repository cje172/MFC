
// Exercise3_2View.cpp: CExercise32View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Exercise3_2.h"
#endif

#include "Exercise3_2Doc.h"
#include "Exercise3_2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExercise32View

IMPLEMENT_DYNCREATE(CExercise32View, CView)

BEGIN_MESSAGE_MAP(CExercise32View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CExercise32View 생성/소멸

CExercise32View::CExercise32View() noexcept
	: m_strOutput(_T(""))
	, m_ptLocation(0)
	, m_bDrag(false)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CExercise32View::~CExercise32View()
{
}

BOOL CExercise32View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CExercise32View 그리기

void CExercise32View::OnDraw(CDC* pDC)
{
	CExercise32Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	// 윈도우에 문자열 출력
	pDC->TextOut(m_ptLocation.x, m_ptLocation.y, m_strOutput);
}


// CExercise32View 인쇄

BOOL CExercise32View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CExercise32View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CExercise32View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CExercise32View 진단

#ifdef _DEBUG
void CExercise32View::AssertValid() const
{
	CView::AssertValid();
}

void CExercise32View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExercise32Doc* CExercise32View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExercise32Doc)));
	return (CExercise32Doc*)m_pDocument;
}
#endif //_DEBUG


// CExercise32View 메시지 처리기


void CExercise32View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	int nCharIndex;
	nCharIndex = m_strOutput.GetLength();		// 입력된 데이터의 길이를 얻음

	if (nChar == VK_BACK)		// 백스페이스가 눌렸을 때
		m_strOutput.Delete(nCharIndex - 1, 1);	// 한 번에 하나씩 지움
	else		// 백스페이스 이외의 키가 눌린 경우
		m_strOutput += (WCHAR)nChar;	// 키보드로 입력된 문자를 문자열에 추가

	Invalidate();	// 화면 갱신
	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CExercise32View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)		// 가상키 코드 값에 대해
	{
	case VK_LEFT:	// 왼쪽 화살표 키를 누를 때
		m_ptLocation.x--;	// 왼쪽으로 1 이동
		break;
	case VK_RIGHT:		// 오른쪽 화살표 키를 누를 때
		m_ptLocation.x++;	// 오른쪽으로 1 이동
		break;
	case VK_UP:		// 위쪽 화살표 키를 누를 때
		m_ptLocation.y--;	// 위쪽으로 1 이동
		break;
	case VK_DOWN:		// 아래쪽 화살표 키를 누를 때
		m_ptLocation.y++;	// 아래쪽으로 1 이동
		break;
	case VK_PRIOR:		// Pageup키를 누를 때
		m_ptLocation.y -= 50;	// 위쪽으로 50 이동
		break;
	case VK_NEXT:		// Pagedown키를 누를 때
		m_ptLocation.y += 50;	// 아래쪽으로 50 이동
		break;
	case VK_HOME:		// Home키를 누를 때
		m_ptLocation = CPoint(0, 0);	// 처음 위치로 이동
		break;
	}

	if (m_ptLocation.x < 0)		// x좌표가 0보다 작으면
	{
		m_ptLocation.x = 0;
		AfxMessageBox(_T("왼쪽으로 더 이상 이동할 수 없습니다."));
	}
	if (m_ptLocation.y < 0)		// y좌표가 0보다 작으면
	{
		m_ptLocation.y = 0;
		AfxMessageBox(_T("위쪽으로 더 이상 이동할 수 없습니다."));
	}
	if (m_ptLocation.x > m_ptClientSize.x)		// x좌표가 윈도우 사이즈 x값보다 크면
	{
		m_ptLocation.x = m_ptClientSize.x;
		AfxMessageBox(_T("오른쪽으로 더 이상 이동할 수 없습니다."));
	}
	if (m_ptLocation.y > m_ptClientSize.y)		// x좌표가 윈도우 사이즈 y값보다 크면
	{
		m_ptLocation.y = m_ptClientSize.y;
		AfxMessageBox(_T("아래쪽으로 더 이상 이동할 수 없습니다."));
	}
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CExercise32View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	m_ptClientSize.x = cx;		// 윈도우 영역의 가로(x) 길이를 얻음
	m_ptClientSize.y = cy;		// 윈도우 영역의 세로(y) 길이를 얻음

	Invalidate();	// 화면 갱신
}


void CExercise32View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 현재 마우스의 위치와 문자열의 위치가 일정범위(=30) 내에 해당될 때
	if (sqrt(pow((m_ptLocation.x - point.x), 2) + pow((m_ptLocation.y - point.y), 2)) <= 30)
		m_bDrag = true;		// 드래그 이동 중

	Invalidate();	// 화면 갱신

	CView::OnLButtonDown(nFlags, point);
}


void CExercise32View::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (m_strOutput.IsEmpty() == false)		// 문자열이 비어있지 않을 때
	{
		if (AfxMessageBox(_T("문자를 모두 지우시겠습니까?"),
			MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			m_strOutput.Empty();
		}
	}
	else	// 문자열이 비어있을 때
	{
		AfxMessageBox(_T("문자열을 입력하시오"));
	}
	Invalidate();	// 화면 갱신

	CView::OnRButtonDown(nFlags, point);
}


void CExercise32View::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bDrag)	// 드래그 시작할 때
	{
		m_ptLocation.x = point.x;	// 현재 움직이는 마우스의 좌표 x값 넣기
		m_ptLocation.y = point.y;	// 현재 움직이는 마우스의 좌표 y값 넣기
	}
	Invalidate();	// 화면 갱신

	CView::OnMouseMove(nFlags, point);
}


void CExercise32View::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bDrag)	// 드래그 시작할 때
	{
		m_bDrag = false;	// 드래그 중지
		m_ptLocation.x = point.x;	// 현재 움직이는 마우스의 좌표 x값 넣기
		m_ptLocation.y = point.y;	// 현재 움직이는 마우스의 좌표 y값 넣기
	}
	Invalidate();	// 화면 갱신

	CView::OnLButtonUp(nFlags, point);
}
