// CTextOutCtrl.cpp: 구현 파일
//

#include "pch.h"
#include "Practice5_4.h"
#include "CTextOutCtrl.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "Practice5_4Doc.h"
#include "Practice5_4View.h"


// CTextOutCtrl 대화 상자

IMPLEMENT_DYNAMIC(CTextOutCtrl, CDialogEx)

CTextOutCtrl::CTextOutCtrl(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TEXTOUT, pParent)
{

}

CTextOutCtrl::~CTextOutCtrl()
{
}

void CTextOutCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTextOutCtrl, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_TEXTOUT, &CTextOutCtrl::OnClickedButtonTextout)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, &CTextOutCtrl::OnClickedButtonColor)
	ON_BN_CLICKED(IDC_BUTTON_FONT, &CTextOutCtrl::OnClickedButtonFont)
END_MESSAGE_MAP()


// CTextOutCtrl 메시지 처리기


BOOL CTextOutCtrl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetDlgItemText(IDC_EDIT_COLOR, _T("000000"));
	SetDlgItemText(IDC_EDIT_FONT, _T("system"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CTextOutCtrl::OnClickedButtonTextout()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CPractice54View* pView = (CPractice54View*)pFrame->GetActiveView();

	GetDlgItemText(IDC_EDIT_TEXT, pView->m_strOutput);

	if (pView->m_strOutput.IsEmpty())
		AfxMessageBox(_T("글을 입력하시오"));
	else
	{
		pView->m_ptPosition.x = GetDlgItemInt(IDC_EDIT_X);
		pView->m_ptPosition.y = GetDlgItemInt(IDC_EDIT_Y);
	}
	pView->Invalidate();
}


void CTextOutCtrl::OnClickedButtonColor()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CColorDialog colorDlg;
	CString strColor;
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CPractice54View* pView = (CPractice54View*)pFrame->GetActiveView();

	if (colorDlg.DoModal() == IDOK)
	{
		pView->m_colorText = colorDlg.GetColor();

		strColor.Format(_T("%06X"), pView->m_colorText);
		SetDlgItemText(IDC_EDIT_COLOR, strColor);
		pView->Invalidate();
	}
}


void CTextOutCtrl::OnClickedButtonFont()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFontDialog fontDlg;
	CString strSize;
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CPractice54View* pView = (CPractice54View*)pFrame->GetActiveView();

	if (fontDlg.DoModal() == IDOK)
	{
		fontDlg.GetCurrentFont(&pView->m_logFont);
		SetDlgItemText(IDC_EDIT_FONT, pView->m_logFont.lfFaceName);

		pView->m_bFont = TRUE;
		pView->Invalidate();
	}
}
