// CHobbyCtrl.cpp: 구현 파일
//

#include "pch.h"
#include "Exercise5_1.h"
#include "CHobbyCtrl.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "Exercise5_1View.h"


// CHobbyCtrl 대화 상자

IMPLEMENT_DYNAMIC(CHobbyCtrl, CDialogEx)

CHobbyCtrl::CHobbyCtrl(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TEXTOUT, pParent)
	, m_strName(_T(""))
	, m_bSex(TRUE)
	, m_bChecked{ (FALSE) }
{

}

CHobbyCtrl::~CHobbyCtrl()
{
}

void CHobbyCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_HOBBY, m_listHobby);
	DDX_Control(pDX, IDC_COMBO_SEX, m_cbSex);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
}


BEGIN_MESSAGE_MAP(CHobbyCtrl, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_SEX, &CHobbyCtrl::OnSelchangeComboSex)
	ON_COMMAND(IDC_RADIO_FEMALE, &CHobbyCtrl::OnRadioFemale)
	ON_COMMAND(IDC_RADIO_MALE, &CHobbyCtrl::OnRadioMale)
	ON_LBN_SELCHANGE(IDC_LIST_HOBBY, &CHobbyCtrl::OnSelchangeListHobby)
	ON_BN_CLICKED(IDC_CHECK_READING, &CHobbyCtrl::OnClickedCheckReading)
	ON_BN_CLICKED(IDC_CHECK_FISHING, &CHobbyCtrl::OnClickedCheckFishing)
	ON_BN_CLICKED(IDC_CHECK_SPORTS, &CHobbyCtrl::OnClickedCheckSports)
	ON_BN_CLICKED(IDC_BUTTON_RESULT, &CHobbyCtrl::OnClickedButtonResult)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CHobbyCtrl::OnChangeEditName)
END_MESSAGE_MAP()


// CHobbyCtrl 메시지 처리기


BOOL CHobbyCtrl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 리스트 박스 초기화
	m_listHobby.AddString(_T("독서"));
	m_listHobby.AddString(_T("낚시"));
	m_listHobby.AddString(_T("운동"));

	// 콤보 박스, 라디오 버튼: "남자"로 초기화
	m_cbSex.SetCurSel(0);

	CButton* pBtn;
	pBtn = (CButton*)GetDlgItem(IDC_RADIO_MALE);
	pBtn->SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CHobbyCtrl::OnSelchangeComboSex()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = m_cbSex.GetCurSel();  // 콤보 박스에서 현재 선택된 인덱스를 가져옴
	CString m_strCombo;

	CButton* pButton1 = (CButton*)GetDlgItem(IDC_RADIO_MALE);
	CButton* pButton2 = (CButton*)GetDlgItem(IDC_RADIO_FEMALE);
	m_cbSex.GetLBText(index, m_strCombo);

	if (index != CB_ERR)
	{
		if (m_strCombo == "여자")		// 콤보 박스에서 여자를 선택한 경우
		{
			pButton1->SetCheck(false);
			pButton2->SetCheck(true);
		}
		else                            // 콤보 박스에서 남자를 선택한 경우
		{
			pButton1->SetCheck(true);
			pButton2->SetCheck(false);
		}
	}
}


void CHobbyCtrl::OnRadioMale()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 라디오 버튼이 선택되면 콤보 박스에 그에 해당하는 아이템 표시
	m_cbSex.SetCurSel(0);
}


void CHobbyCtrl::OnRadioFemale()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// 라디오 버튼이 선택되면 콤보 박스에 그에 해당하는 아이템 표시
	m_cbSex.SetCurSel(1);
}


void CHobbyCtrl::OnSelchangeListHobby()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = m_listHobby.GetCurSel();  // 리스트 박스에서 현재 선택된 인덱스를 가져옴

	// 리스트 박스에서 아이템을 선택하면 그에 해당하는 체크 박스가 체크됨
	if (index == 0)
	{
		m_bChecked[0] = ((CButton*)GetDlgItem(IDC_CHECK_READING))->GetCheck();	// 체크
		((CButton*)GetDlgItem(IDC_CHECK_READING))->SetCheck(!m_bChecked[0]);	// 체크 해제
	}
	else if (index == 1)
	{
		m_bChecked[1] = ((CButton*)GetDlgItem(IDC_CHECK_FISHING))->GetCheck();	// 체크
		((CButton*)GetDlgItem(IDC_CHECK_FISHING))->SetCheck(!m_bChecked[1]);	// 체크 해제
	}
	else if (index == 2)
	{
		m_bChecked[2] = ((CButton*)GetDlgItem(IDC_CHECK_SPORTS))->GetCheck();	// 체크
		((CButton*)GetDlgItem(IDC_CHECK_SPORTS))->SetCheck(!m_bChecked[2]);	    // 체크 해제
	}
}


void CHobbyCtrl::OnClickedCheckReading()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bChecked[0] = ((CButton*)GetDlgItem(IDC_CHECK_READING))->GetCheck();

	if (m_bChecked[0])  // 체크 박스를 선택하면
		m_listHobby.SetSel(0);
	else                // 체크 박스의 체크를 해제하면
		m_listHobby.SetSel(0, false);
}


void CHobbyCtrl::OnClickedCheckFishing()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bChecked[1] = ((CButton*)GetDlgItem(IDC_CHECK_FISHING))->GetCheck();

	if (m_bChecked[1])  // 체크 박스를 선택하면
		m_listHobby.SetSel(1);
	else                // 체크 박스의 체크를 해제하면
		m_listHobby.SetSel(1, false);
}


void CHobbyCtrl::OnClickedCheckSports()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bChecked[2] = ((CButton*)GetDlgItem(IDC_CHECK_SPORTS))->GetCheck();

	if (m_bChecked[2])  // 체크 박스를 선택하면
		m_listHobby.SetSel(2);
	else                // 체크 박스의 체크를 해제하면
		m_listHobby.SetSel(2, false);
}


void CHobbyCtrl::OnClickedButtonResult()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CExercise5_1View* pView = (CExercise5_1View*)pFrame->GetActiveView();

	int index = m_cbSex.GetCurSel();  // 콤보 박스에서 현재 선택된 인덱스 가져옴
	CString strSex;
	m_cbSex.GetLBText(index, strSex);  // 인덱스에 해당하는 값을 strSex에 넣기

	int count = m_listHobby.GetSelCount();  // 리스트 박스에서 현재 선택된 아이템 개수를 가져옴
	CArray <int, int*> m_arr;
	m_arr.SetSize(count);
	m_listHobby.GetSelItems(count, m_arr.GetData());  // 배열에 선택된 아이템 개수 값 저장
	CString strHobby, str[3];

	for (int i = 0; i < m_arr.GetSize(); i++)  // 선택된 아이템의 문자열 합치기
	{
		m_listHobby.GetText(m_arr[i], str[i]);
		strHobby += str[i] + _T(" ");
	}

	// 뷰 클래스에서 선언한 변수에 값 넣어줌
	pView->m_strName = (_T("이름 : ")) + m_strName;
	pView->m_strSex = (_T("성별 : ")) + strSex;
	pView->m_strHobby = (_T("내가 선택한 취미 : ")) + strHobby;

	pView->Invalidate();
}


void CHobbyCtrl::OnChangeEditName()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	GetDlgItemText(IDC_EDIT_NAME, m_strName);
}
