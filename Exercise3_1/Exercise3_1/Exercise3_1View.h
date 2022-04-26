
// Exercise3_1View.h: CExercise31View 클래스의 인터페이스
//

#pragma once


class CExercise31View : public CView
{
protected: // serialization에서만 만들어집니다.
	CExercise31View() noexcept;
	DECLARE_DYNCREATE(CExercise31View)

// 특성입니다.
public:
	CExercise31Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CExercise31View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	CString m_strStopWatch;  // 출력되는 스톱워치 문자열을 저장
	CString m_strRecord[40];  // 기록된 내용을 저장하는 문자열 배열
	int m_nCount;  // 기록된 내용의 개수
	int m_nMinute;  // 분을 나타냄
	int m_nSecond;  // 초를 나타냄
	int m_nMSec;  // 1/100초를 나타냄
	bool m_strStopWatchRun;  // 스톱워치가 작동되는지를 저장
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
//	afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // Exercise3_1View.cpp의 디버그 버전
inline CExercise31Doc* CExercise31View::GetDocument() const
   { return reinterpret_cast<CExercise31Doc*>(m_pDocument); }
#endif

