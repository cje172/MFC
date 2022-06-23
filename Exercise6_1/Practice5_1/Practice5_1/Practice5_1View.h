
// Practice5_1View.h : CPractice5_1View 클래스의 인터페이스
//
#include "atltypes.h"
enum DRAW_MODE {LINE_MODE, ELLIPSE_MODE, POLYGON_MODE, BEZIER_MODE };

#pragma once


class CPractice5_1View : public CView
{
protected: // serialization에서만 만들어집니다.
	CPractice5_1View();
	DECLARE_DYNCREATE(CPractice5_1View)

// 특성입니다.
public:
	CPractice5_1Doc* GetDocument() const;

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
	virtual ~CPractice5_1View();
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
	afx_msg void OnLine();
	afx_msg void OnEllipse();
	afx_msg void OnPolygon();
	afx_msg void OnLineColor();
	afx_msg void OnFaceColor();
	afx_msg void OnBdiagonal();
	afx_msg void OnCross();
	afx_msg void OnVertical();
	int m_nDrawMode;
	int m_nHatchStyle;
	afx_msg void OnUpdateLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEllipse(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePolygon(CCmdUI *pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CPoint m_ptStart;
	CPoint m_ptPrev;
	bool m_bFirst;
	bool m_bLButtonDown;
	bool m_bContextMenu;
	bool m_bHatch;
	CPoint m_ptData[50];
	int m_nCount;
	COLORREF m_colorPen;
	COLORREF m_colorBrush;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBezier();
	afx_msg void OnUpdateBezier(CCmdUI *pCmdUI);
	int m_nCtrlPointNum;
	COLORREF m_colorCurve;
	COLORREF m_colorPolygon;
	COLORREF m_colorPoint;
	CPoint m_ptControl[50];
};

#ifndef _DEBUG  // Practice5_1View.cpp의 디버그 버전
inline CPractice5_1Doc* CPractice5_1View::GetDocument() const
   { return reinterpret_cast<CPractice5_1Doc*>(m_pDocument); }
#endif

