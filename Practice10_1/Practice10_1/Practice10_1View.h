
// Practice10_1View.h: CPractice101View 클래스의 인터페이스
//

#pragma once


class CPractice101View : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CPractice101View() noexcept;
	DECLARE_DYNCREATE(CPractice101View)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_PRACTICE10_1_FORM };
#endif

// 특성입니다.
public:
	CPractice101Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CPractice101View();
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
	CString m_strText;
	int m_nRed;
	int m_nGreen;
	int m_nBlue;
	int m_nX;
	int m_nY;
	CSliderCtrl m_sliderX;
	CSliderCtrl m_sliderY;
	COLORREF m_colorText;
	afx_msg void OnClickedButtonOutput();
	afx_msg void OnClickedButtonColor();
	afx_msg void OnClickedButtonReset();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnChangeEditRed();
	afx_msg void OnChangeEditGreen();
	afx_msg void OnChangeEditBlue();
	afx_msg void OnChangeEditText();
	virtual void OnDraw(CDC* pDC);
};

#ifndef _DEBUG  // Practice10_1View.cpp의 디버그 버전
inline CPractice101Doc* CPractice101View::GetDocument() const
   { return reinterpret_cast<CPractice101Doc*>(m_pDocument); }
#endif

