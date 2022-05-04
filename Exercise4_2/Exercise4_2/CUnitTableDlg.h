#pragma once


// CUnitTableDlg 대화 상자

class CUnitTableDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUnitTableDlg)

public:
	CUnitTableDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CUnitTableDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TABLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
