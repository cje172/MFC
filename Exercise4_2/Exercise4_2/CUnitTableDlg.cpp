// CUnitTableDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Exercise4_2.h"
#include "CUnitTableDlg.h"
#include "afxdialogex.h"


// CUnitTableDlg 대화 상자

IMPLEMENT_DYNAMIC(CUnitTableDlg, CDialogEx)

CUnitTableDlg::CUnitTableDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TABLE, pParent)
{

}

CUnitTableDlg::~CUnitTableDlg()
{
}

void CUnitTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUnitTableDlg, CDialogEx)
END_MESSAGE_MAP()


// CUnitTableDlg 메시지 처리기
