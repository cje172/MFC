
// Exercise5_1View.h: CExercise5_1View 클래스의 인터페이스
//

#pragma once
#include "Exercise5_1Doc.h"


class CExercise5_1View : public CView
{
protected: // serialization에서만 만들어집니다.
	CExercise5_1View() noexcept;
	DECLARE_DYNCREATE(CExercise5_1View)

// 특성입니다.
public:
	CExercise5_1Doc* GetDocument() const;

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
	virtual ~CExercise5_1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;
	CString m_strSex;
	CString m_strHobby;
};

#ifndef _DEBUG  // 2020111414Exercise5View.cpp의 디버그 버전
inline CMy2020111414Exercise5Doc* CMy2020111414Exercise5View::GetDocument() const
   { return reinterpret_cast<CMy2020111414Exercise5Doc*>(m_pDocument); }
#endif

