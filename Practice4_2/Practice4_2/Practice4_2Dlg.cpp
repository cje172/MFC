﻿
// Practice4_2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Practice4_2.h"
#include "Practice4_2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPractice4_2Dlg 대화 상자



CPractice4_2Dlg::CPractice4_2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PRACTICE4_2_DIALOG, pParent)
	, m_strYear(_T(""))
	, m_strMonth(_T(""))
	, m_strDay(_T(""))
	, m_strAMPM(_T(""))
	, m_strHour(_T(""))
	, m_strMinute(_T(""))
	, m_strSecond(_T(""))
	, m_bCheckYear(false)
	, m_bCheckHour(false)
	, m_bRadioClockType(false)
	, m_bViewHelp(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPractice4_2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_YEAR, m_strYear);
	DDX_Text(pDX, IDC_EDIT_MONTH, m_strMonth);
	DDX_Text(pDX, IDC_EDIT_DAY, m_strDay);
	DDX_Text(pDX, IDC_EDIT_AMPM, m_strAMPM);
	DDX_Text(pDX, IDC_EDIT_HOUR, m_strHour);
	DDX_Text(pDX, IDC_EDIT_MINUTE, m_strMinute);
	DDX_Text(pDX, IDC_EDIT_SECOND, m_strSecond);
}

BEGIN_MESSAGE_MAP(CPractice4_2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDC_RADIO_12, &CPractice4_2Dlg::OnRadio12)
	ON_COMMAND(IDC_RADIO_24, &CPractice4_2Dlg::OnRadio24)
	ON_BN_CLICKED(IDC_CHECK_YEAR, &CPractice4_2Dlg::OnClickedCheckYear)
	ON_BN_CLICKED(IDC_CHECK_HOUR, &CPractice4_2Dlg::OnClickedCheckHour)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CPractice4_2Dlg::OnClickedButtonHelp)
END_MESSAGE_MAP()


// CPractice4_2Dlg 메시지 처리기

BOOL CPractice4_2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	// Radio Button과 Check Box 초기화
	((CButton*)GetDlgItem(IDC_RADIO_12))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_CHECK_HOUR))->SetCheck(TRUE);

	// 년, 월, 일 Edit Control 초기화
	GetDlgItem(IDC_EDIT_YEAR)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_MONTH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_DAY)->ShowWindow(SW_HIDE);

	// 년, 월, 일 Static Text 초기화
	GetDlgItem(IDC_STATIC_YEAR)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_MONTH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_DAY)->ShowWindow(SW_HIDE);

	// 멤버 변수 초기화
	m_bRadioClockType = true;
	m_bCheckHour = true;
	m_bCheckYear = false;

	SetTimer(0, 1000, NULL);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CPractice4_2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CPractice4_2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CPractice4_2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPractice4_2Dlg::OnEnChangeEdit3()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CPractice4_2Dlg::OnEnChangeEdit4()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CPractice4_2Dlg::OnEnChangeEdit5()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CPractice4_2Dlg::OnRadio12()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bRadioClockType = true;
}


void CPractice4_2Dlg::OnRadio24()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bRadioClockType = false;
}


void CPractice4_2Dlg::OnClickedCheckYear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_bCheckYear == false)	// "년월일 표시" 체크박스가 눌렸을 때
	{
		GetDlgItem(IDC_EDIT_YEAR)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_MONTH)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_DAY)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_YEAR)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_MONTH)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_DAY)->ShowWindow(SW_SHOW);
		m_bCheckYear = true;
	}
	else	// "년월일 표시" 체크박스가 눌리지 않았을 때
	{
		GetDlgItem(IDC_EDIT_YEAR)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_MONTH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_DAY)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_YEAR)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_MONTH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_DAY)->ShowWindow(SW_HIDE);
		m_bCheckYear = false;
	}
}


void CPractice4_2Dlg::OnClickedCheckHour()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_bCheckHour == false)	// "시분초 표시" 체크박스가 눌렸을 때
	{
		GetDlgItem(IDC_EDIT_HOUR)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_MINUTE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_SECOND)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_AMPM)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_HOUR)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_MINUTE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_SECOND)->ShowWindow(SW_SHOW);
		m_bCheckHour = true;
	}
	else	// "시분초 표시" 체크박스가 눌리지 않았을 때
	{
		GetDlgItem(IDC_EDIT_HOUR)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_MINUTE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_SECOND)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_AMPM)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_HOUR)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_MINUTE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SECOND)->ShowWindow(SW_HIDE);
		m_bCheckHour = false;
	}
}


void CPractice4_2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int hour;
	CTime timer;
	timer = CTime::GetCurrentTime();

	m_strYear.Format(_T("%d"), timer.GetYear());  // 년도 출력
	m_strMonth.Format(_T("%d"), timer.GetMonth());  // 월 출력
	m_strDay.Format(_T("%d"), timer.GetDay());  // 일 출력

	hour = timer.GetHour();
	if (m_bRadioClockType)  // 12시 베이스
	{
		if (hour >= 12)  // 시간이 12시보다 크면 PM 출력
		{
			m_strAMPM = _T("PM");
			if (hour >= 13)
				hour = hour - 12;
		}
		else  // 시간이 12시보다 작으면 AM 출력
		{
			m_strAMPM = _T("AM");
		}
	}
	else  // 24시간 베이스
	{
		m_strAMPM.Empty();
	}
	m_strHour.Format(_T("%d"), hour);  // 시 출력
	m_strMinute.Format(_T("%d"), timer.GetMinute());  // 분 출력
	m_strSecond.Format(_T("%d"), timer.GetSecond());  // 초 출력
	UpdateData(FALSE);

	CDialogEx::OnTimer(nIDEvent);
}


void CPractice4_2Dlg::OnClickedButtonHelp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_bViewHelp == false)
	{
		m_dlgClockHelp.Create(IDD_DIALOG_HELP, this);

		CRect rectMain, rectHelp;
		GetWindowRect(&rectMain);

		m_dlgClockHelp.GetWindowRect(&rectHelp);
		m_dlgClockHelp.MoveWindow(rectMain.right, rectMain.top, rectHelp.Width(),
			rectHelp.Height());

		m_dlgClockHelp.ShowWindow(SW_SHOW);
		m_bViewHelp = true;
	}
	else
	{
		m_dlgClockHelp.ShowWindow(SW_HIDE);
		m_dlgClockHelp.DestroyWindow();
		m_bViewHelp = false;
	}
}
