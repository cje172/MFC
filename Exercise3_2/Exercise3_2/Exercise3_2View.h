
// Exercise3_2View.h: CExercise32View 클래스의 인터페이스
//

#pragma once


class CExercise32View : public CView
{
protected: // serialization에서만 만들어집니다.
	CExercise32View() noexcept;
	DECLARE_DYNCREATE(CExercise32View)

// 특성입니다.
public:
	CExercise32Doc* GetDocument() const;

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
	virtual ~CExercise32View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	CString m_strOutput;	// 문자열 저장
	CPoint m_ptLocation;	// 문자열이 출력되는 위치 저장
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CPoint m_ptClientSize;	// 윈도우 클라이언트 영역의 크기 저장
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	bool m_bDrag;	// 드래그의 시작을 알리는 플래그
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // Exercise3_2View.cpp의 디버그 버전
inline CExercise32Doc* CExercise32View::GetDocument() const
   { return reinterpret_cast<CExercise32Doc*>(m_pDocument); }
#endif

