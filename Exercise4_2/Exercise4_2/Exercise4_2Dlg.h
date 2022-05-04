
// Exercise4_2_2020111414Dlg.h: 헤더 파일
//

#pragma once
#include "CUnitTableDlg.h"

// CExercise422020111414Dlg 대화 상자
class CExercise42Dlg : public CDialogEx
{
// 생성입니다.
public:
	CExercise42Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXERCISE4_2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strCurrentValue;
	CString m_strConvertedValue;
	CComboBox m_cbConvertUnit;
	CComboBox m_cbCurrentUnit;
	bool m_bRadioChecked[2];
	afx_msg void OnRadioLength();
	afx_msg void OnRadioWeight();
	afx_msg void OnClickedButtonConvert();
	afx_msg void OnClickedButtonTable();
	bool m_bViewTable;
	CUnitTableDlg m_dlgUnitTable;
	void UpdateComboBox();
	CEdit m_edCurrentValue;
	afx_msg void OnChangeEditCurrentValue();
};
