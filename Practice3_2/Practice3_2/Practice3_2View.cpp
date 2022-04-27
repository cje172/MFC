
// Practice3_2View.cpp: CPractice3_2View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Practice3_2.h"
#endif

#include "Practice3_2Doc.h"
#include "Practice3_2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPractice3_2View

IMPLEMENT_DYNCREATE(CPractice3_2View, CView)

BEGIN_MESSAGE_MAP(CPractice3_2View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CPractice3_2View 생성/소멸

CPractice3_2View::CPractice3_2View() noexcept
	: m_bTimerRun(false)
	, m_bTimerType(true)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CPractice3_2View::~CPractice3_2View()
{
}

BOOL CPractice3_2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPractice3_2View 그리기

void CPractice3_2View::OnDraw(CDC* pDC)
{
	CPractice3_2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CRect rect;
	GetClientRect(&rect);	// 윈도우 클라이언트 영역을 얻는다.
	// 윈도우의 중앙에 타이머를 출력
	pDC->DrawText(m_strTimer, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}


// CPractice3_2View 인쇄

BOOL CPractice3_2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CPractice3_2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPractice3_2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CPractice3_2View 진단

#ifdef _DEBUG
void CPractice3_2View::AssertValid() const
{
	CView::AssertValid();
}

void CPractice3_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPractice3_2Doc* CPractice3_2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPractice3_2Doc)));
	return (CPractice3_2Doc*)m_pDocument;
}
#endif //_DEBUG


// CPractice3_2View 메시지 처리기


int CPractice3_2View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	SetTimer(0, 1000, NULL);		// 타이머 설정
	m_bTimerRun = TRUE;				// 타이머 동작

	return 0;
}


void CPractice3_2View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CTime timer;						// 타이머 변수 선언
	timer = CTime::GetCurrentTime();	// 현재 시간을 얻음
	CString str;

	if (m_bTimerType)
	{
		m_strTimer.Format(_T("현재는 %d년 %d월 %d일 %d시 %d분 %d초"),
			timer.GetYear(), timer.GetMonth(), timer.GetDay(),
			timer.GetHour(), timer.GetMinute(), timer.GetSecond());
	}
	else
	{
		int hour;
		hour = timer.GetHour();

		if (hour >= 12)
		{
			str = "PM";
			if (hour >= 13)
			{
				hour = hour - 12;
			}
		}
		else
		{
			str = "AM";
		}
		m_strTimer.Format(_T("지금은 %s %d시 %d분 %d초"),
			str, hour, timer.GetMinute(), timer.GetSecond());
	}
	Invalidate();
	CView::OnTimer(nIDEvent);
}


void CPractice3_2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bTimerType)	// 년, 월, 일, 시, 분, 초 형태로 출력 중
	{
		if (AfxMessageBox(_T("시, 분, 초 형태로 표시하시겠습니까?"),
			MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			m_bTimerType = false;
		}
	}
	else         // 시, 분, 초 형태로 출력 중
	{
		if (AfxMessageBox(_T("년, 월, 일, 시, 분, 초 형태로 표시하시겠습니까?"),
			MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			m_bTimerType = true;
		}
	}
	CView::OnLButtonDown(nFlags, point);
}


void CPractice3_2View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bTimerRun == false)		// 타이머가 동작 안 할 때 메시지 출력
	{
		if (AfxMessageBox(_T("디지털시계를 동작시키겠습니까?"),
			MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			SetTimer(0, 1000, NULL);	// 타이머 설정
			m_bTimerRun = true;			// 타이머 동작 => true
		}
	}
	else                           // 타이머가 동작 중일 때 메시지 박스 출력
	{
		if (AfxMessageBox(_T("디지털시계 동작을 멈추겠습니까?"),
			MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			KillTimer(0);				// 타이머 해제
			m_bTimerRun = false;		// 타이머 동작 => false
		}
	}
	CView::OnRButtonDown(nFlags, point);
}


void CPractice3_2View::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_bTimerRun)
		KillTimer(0);		// 타이머 해제
}