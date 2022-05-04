
// Exercise4_2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Exercise4_2.h"
#include "Exercise4_2Dlg.h"
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


// CExercise42Dlg 대화 상자



CExercise42Dlg::CExercise42Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXERCISE4_2_DIALOG, pParent)
	, m_strCurrentValue(_T(""))
	, m_strConvertedValue(_T(""))
	, m_bViewTable(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExercise42Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CURRENT_VALUE, m_strCurrentValue);
	DDX_Text(pDX, IDC_EDIT_CONVERTED_VALUE, m_strConvertedValue);
	DDX_Control(pDX, IDC_COMBO_CONVERT_UNIT, m_cbConvertUnit);
	DDX_Control(pDX, IDC_COMBO_CURRENT_UNIT, m_cbCurrentUnit);
	DDX_Control(pDX, IDC_EDIT_CURRENT_VALUE, m_edCurrentValue);
}

BEGIN_MESSAGE_MAP(CExercise42Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDC_RADIO_LENGTH, &CExercise42Dlg::OnRadioLength)
	ON_COMMAND(IDC_RADIO_WEIGHT, &CExercise42Dlg::OnRadioWeight)
	ON_BN_CLICKED(IDC_BUTTON_CONVERT, &CExercise42Dlg::OnClickedButtonConvert)
	ON_BN_CLICKED(IDC_BUTTON_TABLE, &CExercise42Dlg::OnClickedButtonTable)
	ON_EN_CHANGE(IDC_EDIT_CURRENT_VALUE, &CExercise42Dlg::OnChangeEditCurrentValue)
END_MESSAGE_MAP()


// CExercise42Dlg 메시지 처리기

BOOL CExercise42Dlg::OnInitDialog()
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
	// Radio Button 초기화
	((CButton*)GetDlgItem(IDC_RADIO_LENGTH))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO_WEIGHT))->SetCheck(FALSE);

	// 멤버 변수 초기화
	m_bRadioChecked[0] = m_bRadioChecked[1] = FALSE;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CExercise42Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CExercise42Dlg::OnPaint()
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
HCURSOR CExercise42Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExercise42Dlg::OnRadioLength()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bRadioChecked[0] = TRUE;
	m_bRadioChecked[1] = FALSE;
	UpdateComboBox();
}


void CExercise42Dlg::OnRadioWeight()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bRadioChecked[1] = TRUE;
	m_bRadioChecked[0] = FALSE;
	UpdateComboBox();
}


void CExercise42Dlg::OnClickedButtonConvert()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strCbCurrent, strCbConvert; // 선택된 아이템의 문자열 저장할 변수
	double currentNum = 0; // 계산에 사용할 변수
	double convertNum = 0; // 계산에 사용할 변수
	int nIndex_current = m_cbCurrentUnit.GetCurSel();  // 선택된 아이템의 인덱스를 구함
	int nIndex_convert = m_cbConvertUnit.GetCurSel();  // 선택된 아이템의 인덱스를 구함

	m_cbCurrentUnit.GetLBText(nIndex_current, strCbCurrent);  // 선택된 아이템의 인덱스에 해당하는 문자열을 변수에 저장
	m_cbConvertUnit.GetLBText(nIndex_convert, strCbConvert);  // 선택된 아이템의 인덱스에 해당하는 문자열을 변수에 저장
	m_edCurrentValue.GetWindowTextW(m_strCurrentValue);  // 현재 값의 입력 값 받아오기

	currentNum = _wtof(m_strCurrentValue);  // CString -> double

	// 단위 변환 계산
	if (strCbCurrent == "야드")  // 현재 단위가 야드이면
	{
		if (strCbConvert == "야드")  // 변환 단위가 야드이면
			convertNum = currentNum;
		else if (strCbConvert == "미터")  // 변환 단위가 미터이면
			convertNum = 0.9122 * currentNum;
		else  // 변환 단위가 인치이면
			convertNum = 36 * currentNum;
	}
	else if (strCbCurrent == "미터")  // 현재 단위가 미터이면
	{
		if (strCbConvert == "야드")  // 변환 단위가 야드이면
			convertNum = 1.093613 * currentNum;
		else if (strCbConvert == "미터")  // 변환 단위가 미터이면
			convertNum = currentNum;
		else  // 변환 단위가 인치이면
			convertNum = 39.370079 * currentNum;
	}
	else if (strCbCurrent == "인치")  // 현재 단위가 인치이면
	{
		if (strCbConvert == "야드")  // 변환 단위가 야드이면
			convertNum = 0.027778 * currentNum;
		else if (strCbConvert == "미터")  // 변환 단위가 미터이면
			convertNum = 0.0254 * currentNum;
		else  // 변환 단위가 인치이면
			convertNum = currentNum;
	}
	else if (strCbCurrent == "파운드")  // 현재 단위가 파운드이면
	{
		if (strCbConvert == "파운드")  // 변환 단위가 파운드이면
			convertNum = currentNum;
		else if (strCbConvert == "온즈")  // 변환 단위가 온즈이면
			convertNum = 16 * currentNum;
		else  // 변환 단위가 그램이면
			convertNum = 453.59237 * currentNum;
	}
	else if (strCbCurrent == "온즈")  // 현재 단위가 온즈이면
	{
		if (strCbConvert == "파운드")  // 변환 단위가 파운드이면
			convertNum = 0.0625 * currentNum;
		else if (strCbConvert == "온즈")  // 변환 단위가 온즈이면
			convertNum = currentNum;
		else  // 변환 단위가 그램이면
			convertNum = 28.3495223 * currentNum;
	}
	else  // 현재 단위가 그램이면
	{
		if (strCbConvert == "파운드")  // 변환 단위가 파운드이면
			convertNum = 0.002205 * currentNum;
		else if (strCbConvert == "온즈")  // 변환 단위가 온즈이면
			convertNum = 0.035274 * currentNum;
		else  // 변환 단위가 그램이면
			convertNum = currentNum;
	}
	m_strConvertedValue.Format(_T("%f"), convertNum);
	SetDlgItemText(IDC_EDIT_CONVERTED_VALUE, m_strConvertedValue);
}


void CExercise42Dlg::OnClickedButtonTable()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_bViewTable == false)
	{
		m_dlgUnitTable.Create(IDD_DIALOG_TABLE, this);

		CRect rectMain, rectTable;
		GetWindowRect(&rectMain);

		m_dlgUnitTable.GetWindowRect(&rectTable);
		m_dlgUnitTable.MoveWindow(rectMain.right, rectMain.top, rectTable.Width(),
			rectTable.Height());

		m_dlgUnitTable.ShowWindow(SW_SHOW);
		m_bViewTable = true;
	}
	else
	{
		m_dlgUnitTable.ShowWindow(SW_HIDE);
		m_dlgUnitTable.DestroyWindow();
		m_bViewTable = false;
	}
}


void CExercise42Dlg::UpdateComboBox()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_bRadioChecked[0])  // 라디오버튼에 길이가 선택된 경우
	{
		m_cbCurrentUnit.ResetContent();  // 콤보 박스의 모든 아이템 삭제
		m_cbConvertUnit.ResetContent();  // 콤보 박스의 모든 아이템 삭제

		m_cbCurrentUnit.AddString(_T("야드"));
		m_cbCurrentUnit.AddString(_T("미터"));
		m_cbCurrentUnit.AddString(_T("인치"));

		m_cbConvertUnit.AddString(_T("야드"));
		m_cbConvertUnit.AddString(_T("미터"));
		m_cbConvertUnit.AddString(_T("인치"));
	}
	if (m_bRadioChecked[1])  // 라디오버튼에 무게가 선택된 경우
	{
		m_cbCurrentUnit.ResetContent();  // 콤보 박스의 모든 아이템 삭제
		m_cbConvertUnit.ResetContent();  // 콤보 박스의 모든 아이템 삭제

		m_cbCurrentUnit.AddString(_T("파운드"));
		m_cbCurrentUnit.AddString(_T("온즈"));
		m_cbCurrentUnit.AddString(_T("그램"));

		m_cbConvertUnit.AddString(_T("파운드"));
		m_cbConvertUnit.AddString(_T("온즈"));
		m_cbConvertUnit.AddString(_T("그램"));
	}
}


void CExercise42Dlg::OnChangeEditCurrentValue()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_edCurrentValue.GetWindowTextW(m_strCurrentValue);  // 현재 값의 입력 값 받아오기
	int nCharIndex;
	nCharIndex = m_strCurrentValue.GetLength();

	if (nCharIndex == 0)	// 입력된 값의 길이가 0이면 = 입력 값이 없으면
	{
		AfxMessageBox(_T("변환할 값을 입력하세요."),
			MB_OK | MB_ICONWARNING);
	}
}
