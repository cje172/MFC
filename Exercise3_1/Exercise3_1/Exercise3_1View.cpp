
// Exercise3_1View.cpp: CExercise31View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Exercise3_1.h"
#endif

#include "Exercise3_1Doc.h"
#include "Exercise3_1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExercise31View

IMPLEMENT_DYNCREATE(CExercise31View, CView)

BEGIN_MESSAGE_MAP(CExercise31View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	//	ON_WM_NCRBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CExercise31View 생성/소멸

CExercise31View::CExercise31View() noexcept
	: m_strStopWatch(_T("00 : 00. 00"))
	, m_strStopWatchRun(false)
	, m_strRecord()
	, m_nCount(0)
	, m_nMinute(0), m_nSecond(0), m_nMSec(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CExercise31View::~CExercise31View()
{
}

BOOL CExercise31View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CExercise31View 그리기

void CExercise31View::OnDraw(CDC* pDC)
{
	CExercise31Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CRect rect;
	GetClientRect(&rect);
	// 윈도우 영역 정 중앙에 m_strStopWatch 출력
	pDC->DrawText(m_strStopWatch, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	// Point(10,10)부터 y 좌표를 20씩 증가시키면서 m_strRecord 배열 출력
	for (int i = 0; i < 40; i++)
	{
		pDC->TextOut(10, 10 + i * 20, m_strRecord[i]);
	}
}


// CExercise31View 인쇄

BOOL CExercise31View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CExercise31View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CExercise31View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CExercise31View 진단

#ifdef _DEBUG
void CExercise31View::AssertValid() const
{
	CView::AssertValid();
}

void CExercise31View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExercise31Doc* CExercise31View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExercise31Doc)));
	return (CExercise31Doc*)m_pDocument;
}
#endif //_DEBUG


// CExercise31View 메시지 처리기


void CExercise31View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	m_nMSec++;
	if (m_nMSec == 100)  // m_nSec 값이 100일 때
	{
		m_nSecond++;
		m_nMSec = 0;

		if (m_nSecond == 60)  // m_nSecond 값이 60일 때
		{
			m_nMinute++;
			m_nSecond = 0;
		}
	}

	// m_strStopWatch에 문자열 생성
	m_strStopWatch.Format(_T("%02d: %02d. %02d"), m_nMinute, m_nSecond, m_nMSec);
	Invalidate();  // 화면 갱신

	CView::OnTimer(nIDEvent);
}


void CExercise31View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_strStopWatchRun == false)	 // 스톱워치가 작동 중이 아닐 때
	{
		SetTimer(0, 10, NULL);  // 스톱워치 실행
		m_strStopWatchRun = true;
	}
	else  // 스톱워치가 작동 중일 때
	{
		KillTimer(0);  // 스톱워치 정지
		m_strStopWatchRun = false;
	}

	CView::OnLButtonDown(nFlags, point);
}


void CExercise31View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_strStopWatchRun == true)  // 스톱워치가 작동 중일 때
	{
		if (nChar == VK_SPACE)  // 스페이스 키를 누를 때
		{
			m_strRecord[m_nCount] = m_strStopWatch;	 // m_strRecord 배열에 기록 값 넣기
			m_nCount++;  // m_nCount 값 증가

			if (m_nCount >= 40)  // 기록 개수가 40개 이상일 때
			{
				// m_strRecord 배열 초기화
				for (int i = 0; i < 40; i++)
					m_strRecord[i] = "";
				m_nCount = 0;  // 기록 개수 초기화 
			}
		}
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CExercise31View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_strStopWatchRun)  // 스톱워치가 작동 중일 때
	{
		// 메시지 박스 띄우기
		AfxMessageBox(_T("작동중에는 스톱워치를 초기화시킬 수 없습니다"));
	}
	else  // 스톱워치가 작동하지 않을 때
	{
		// 메시지 박스 띄우기
		if (AfxMessageBox(_T("스톱워치를 초기화 하시겠습니까?"),
			MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			// 스톱워치 초기화
			for (int i = 0; i < 40; i++)
				m_strRecord[i].Empty();
			
			m_strStopWatch = _T("00: 00. 00");
			m_nCount = 0;
			m_nMinute = 0;
			m_nSecond = 0;
			m_nMSec = 0;
		}
	}
	Invalidate();  // 화면 갱신

	CView::OnRButtonDown(nFlags, point);
}
