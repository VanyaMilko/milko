#include "pch.h"
#include "framework.h"
#include "CourceWorkApp.h"
#include "Menu.h"
#include "afxdialogex.h"
#include "UserControl.h"
#include "ExpertChoice.h"
#include "ExpertMethod.h"
#include "Authorization.h"
#include "Registration.h"
#include "Formatter.h"
#include "AddProduct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define INDEX_NAME    0
#define INDEX_TYPE    1
#define INDEX_COST    2
#define INDEX_WEIGHT  3
#define INDEX_MARK    4

#define ID_START 6666

CMenuDlg::CMenuDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PATTERN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_TypeOfUser = TypeOfUser::UNDEFINED;

	nMinCost = -1;
	nMaxCost = -1;
	dMinMark = -1.0;
	dMaxMark = -1.0;
	dMinWeight = -1.0;
	dMaxWeight = -1.0;
}

void CMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BUTTON_USER_CONTROL, m_wndBtnUser);
	DDX_Control(pDX, IDC_BUTTON_EXPERT_METHOD, m_wndBtnExpert);
	DDX_Control(pDX, IDC_BUTTON_EXIT, m_wndBtnExit);
	DDX_Control(pDX, IDC_LIST_PRODUCTS, m_wndReportCtrl);
	DDX_Control(pDX, IDC_BUTTON_FILTER_APPLY, m_wndBtnApplyFilter);
	DDX_Control(pDX, IDC_BUTTON_SEARCH_APPLY, m_wndBtnApplySearch);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_wndBtnAdd);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_wndBtnDel);
	DDX_Control(pDX, IDC_BUTTON_EDIT, m_wndBtnEdit);
	DDX_Control(pDX, IDC_EDIT_1_FROM, m_wndEdit1From);
	DDX_Control(pDX, IDC_EDIT_1_TO, m_wndEdit1To);
	DDX_Control(pDX, IDC_EDIT_2_FROM, m_wndEdit2From);
	DDX_Control(pDX, IDC_EDIT_2_TO, m_wndEdit2To);
	DDX_Control(pDX, IDC_EDIT_MARK_FROM, m_wndEditMarkFrom);
	DDX_Control(pDX, IDC_EDIT_MARK_TO, m_wndEditMarkTo);
	DDX_Control(pDX, IDC_EDIT_SEARCH_NAME, m_wndEditFilterName);
	DDX_Control(pDX, IDC_EDIT_SEARCH_TYPE, m_wndEditFilterType);
	DDX_Control(pDX, IDC_BUTTON_REPORT, m_wndBtnReport);
}

BEGIN_MESSAGE_MAP(CMenuDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_USER_CONTROL, OnBtnUserClck)
	ON_BN_CLICKED(IDC_BUTTON_EXPERT_METHOD, OnBtnExpertClck)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnBtnExitClck)
	ON_MESSAGE_VOID(ID_START, OnStart)
	ON_MESSAGE_VOID(MSG_UPDATE, UpdatePage)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnBnClickedAdd)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, OnBnClickedEdit)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnBnClickedDel)
	ON_BN_CLICKED(IDC_BUTTON_FILTER_APPLY, OnBnClickedFilter)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_APPLY, OnBnClickedSearch)
	ON_BN_CLICKED(IDC_BUTTON_REPORT, OnBnClickedReport)
END_MESSAGE_MAP()

void CMenuDlg::UpdatePage()
{
	m_wndBtnAdd.EnableWindow(m_TypeOfUser == TypeOfUser::ADMIN ? TRUE : FALSE);
	m_wndBtnEdit.EnableWindow(m_TypeOfUser == TypeOfUser::ADMIN ? TRUE : FALSE);
	m_wndBtnDel.EnableWindow(m_TypeOfUser == TypeOfUser::ADMIN ? TRUE : FALSE);

	m_Dishes = m_pModule->getAllObj();
	m_wndReportCtrl.DeleteAllItems();

	for (auto iter : m_Dishes)
	{
		bool bShow = true;
		if (!strNameFilter.IsEmpty())bShow &= AtoW(iter.GetName()).Find(strNameFilter) != -1;
		if (!strTypeFilter.IsEmpty())bShow &= AtoW(iter.GetType()).Find(strTypeFilter) != -1;

		if (nMinCost != -1) bShow &= iter.GetCost() >= nMinCost;
		if (nMaxCost != -1) bShow &= iter.GetCost() <= nMaxCost;

		if (dMinMark != -1.0) bShow &= iter.GetMark() >= dMinMark;
		if (dMaxMark != -1.0) bShow &= iter.GetMark() <= dMaxMark;

		if (dMinWeight != -1.0) bShow &= iter.GetPower() >= dMinWeight;
		if (dMaxWeight != -1.0) bShow &= iter.GetPower() <= dMaxWeight;

		if (bShow)AddToReport(iter);
	}
}

BOOL CMenuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	m_pModule = new ClientConnectionModule();
	//m_pConnectionModule->registration(TypeOfUser::ADMIN, "admin", "admin");

	m_wndReportCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_wndReportCtrl.InsertColumn(INDEX_NAME, L"Название", 0, 220);
	m_wndReportCtrl.InsertColumn(INDEX_TYPE, L"Тип", 0, 150);
	m_wndReportCtrl.InsertColumn(INDEX_COST, L"Стоимость, руб.", 0, 80);
	m_wndReportCtrl.InsertColumn(INDEX_WEIGHT, L"Мощность, л.с.", 0, 150);
	m_wndReportCtrl.InsertColumn(INDEX_MARK, L"Оценка", 0, 56);

	PostMessage(ID_START);
	return TRUE;
}

void CMenuDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

CMenuDlg::~CMenuDlg()
{
	delete m_pModule;
}

HCURSOR CMenuDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMenuDlg::OnBtnUserClck()
{
	CUserControlDlg dlg(m_pModule);
	dlg.DoModal();
}

void CMenuDlg::OnBtnExpertClck()
{
	std::vector<Car> dishes;
	CExpertMethodDlg dlg(m_pModule, dishes);
	dlg.DoModal();

	if (dishes.size() == 5)
	{
		CExpDlg dlgExp(dishes);
		dlgExp.DoModal();
		for (auto i : dishes)
		{
			m_pModule->editOneObj(i);
		}
	}
}

void CMenuDlg::OnBtnExitClck()
{
	PostMessage(WM_CLOSE);
}

void CMenuDlg::OnStart()
{
	CAuthorizationDlg dlg(this);
	m_TypeOfUser = dlg.DoModal(m_pModule);

	if (m_TypeOfUser == TypeOfUser::REGISTRATION)
	{
		CRegistrationDlg regDlg;
		m_TypeOfUser = regDlg.DoModal(m_pModule);
	}

	switch (m_TypeOfUser)
	{
	case TypeOfUser::UNDEFINED:
		PostMessage(WM_CLOSE);
		break;
	case TypeOfUser::ADMIN:
		m_wndBtnExpert.EnableWindow(FALSE);
		break;
	case TypeOfUser::CLIENT:
		m_wndBtnUser.EnableWindow(FALSE);
		m_wndBtnExpert.EnableWindow(FALSE);
		break;
	case TypeOfUser::EXPERT:
		m_wndBtnUser.EnableWindow(FALSE);
		break;
	}
	PostMessage(MSG_UPDATE);
}

BOOL CMenuDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;                // Do not process further
		}
	}

	return CWnd::PreTranslateMessage(pMsg);
}

void CMenuDlg::OnBnClickedAdd()
{
	Car cloth;
	CAddDlg dlg;

	if (dlg.DoModal(&cloth) == S_OK)
	{
		m_pModule->addOneObj(cloth);
	}

	UpdatePage();
}

void CMenuDlg::OnBnClickedEdit()
{
	auto pos = m_wndReportCtrl.GetFirstSelectedItemPosition();

	if (!pos)
		return;

	int index = m_wndReportCtrl.GetNextSelectedItem(pos);

	Car obj;

	obj.SetName(WtoA(m_wndReportCtrl.GetItemText(index, INDEX_NAME)));
	obj.SetType(WtoA(m_wndReportCtrl.GetItemText(index, INDEX_TYPE)));
	obj.SetCost(_wtof(m_wndReportCtrl.GetItemText(index, INDEX_COST)));
	obj.SetPower(_wtof(m_wndReportCtrl.GetItemText(index, INDEX_WEIGHT)));
	obj.SetMark(_wtof(m_wndReportCtrl.GetItemText(index, INDEX_MARK)));

	for (auto iter : m_Dishes)
	{
		if (obj == iter)
		{
			obj.SetId(iter.GetId());
			break;
		}
	}

	CAddDlg dlg;

	if (dlg.DoModal(&obj) == S_OK)
	{
		auto answer = m_pModule->editOneObj(obj);
		switch (answer)
		{
		case AnswerFromServer::_ERROR: MessageBox(L"ERROR"); break;
		case AnswerFromServer::UNKNOWN_COMMAND: MessageBox(L"Неизвестная команда"); break;
		}
	}

	UpdatePage();
}

void CMenuDlg::OnBnClickedDel()
{
	auto pos = m_wndReportCtrl.GetFirstSelectedItemPosition();

	if (!pos)
		return;

	int index = m_wndReportCtrl.GetNextSelectedItem(pos);

	Car obj;

	obj.SetName(WtoA(m_wndReportCtrl.GetItemText(index, INDEX_NAME)));
	obj.SetType(WtoA(m_wndReportCtrl.GetItemText(index, INDEX_TYPE)));
	obj.SetCost(_wtof(m_wndReportCtrl.GetItemText(index, INDEX_COST)));
	obj.SetPower(_wtof(m_wndReportCtrl.GetItemText(index, INDEX_WEIGHT)));
	obj.SetMark(_wtof(m_wndReportCtrl.GetItemText(index, INDEX_MARK)));

	for (auto iter : m_Dishes)
	{
		if (obj == iter)
		{
			obj = iter;
			break;
		}
	}

	auto answer = m_pModule->delOneObj(obj);
	switch (answer)
	{
	case AnswerFromServer::_ERROR: MessageBox(L"ERROR"); break;
	case AnswerFromServer::UNKNOWN_COMMAND: MessageBox(L"Неизвестная команда"); break;
	}

	UpdatePage();
}

void CMenuDlg::OnBnClickedSearch()
{
	m_wndEditFilterName.GetWindowText(strNameFilter);
	m_wndEditFilterType.GetWindowText(strTypeFilter);

	UpdatePage();
}

void CMenuDlg::OnBnClickedFilter()
{
	CString str;

	m_wndEdit1From.GetWindowText(str);
	nMinCost = (str.GetLength() ? _wtoi(str) : -1);

	m_wndEdit1To.GetWindowText(str);
	nMaxCost = (str.GetLength() ? _wtoi(str) : -1);

	m_wndEdit2From.GetWindowText(str);
	dMinWeight = (str.GetLength() ? _wtof(str) : -1.0);

	m_wndEdit2To.GetWindowText(str);
	dMaxWeight = (str.GetLength() ? _wtof(str) : -1.0);

	m_wndEditMarkFrom.GetWindowText(str);
	dMinMark = (str.GetLength() ? _wtof(str) : -1.0);

	m_wndEditMarkTo.GetWindowText(str);
	dMaxMark = (str.GetLength() ? _wtof(str) : -1.0);

	UpdatePage();
}

void CMenuDlg::OnBnClickedReport()
{
	int nRated = 0;
	for (auto iter : m_Dishes)
	{
		if (iter.GetMark() != 0)nRated++;
	}

	CStdioFile  fl;
	fl.Open(L"Отчет.txt", CFile::modeCreate | CFile::modeWrite);
	CString str = L"Количетво записей: " + IntToStr(m_Dishes.size()) + L"\n";
	fl.WriteString(str);
	str = L"Количетво оцененных записей: " + IntToStr(nRated) + L"\n";
	fl.WriteString(str);
	for (auto iter : m_Dishes)
	{
		str = L"Название: " + AtoW(iter.GetName()) + L"\n";
		fl.WriteString(str);
		str = L"Тип: " + AtoW(iter.GetType()) + L"\n";
		fl.WriteString(str);
		str = L"Стоимость: " + IntToStr(iter.GetCost()) + L" руб.\n";
		fl.WriteString(str);
		str = L"Мощность: " + DoubleToStr(iter.GetPower()) + L"л.с.\n";
		fl.WriteString(str);
		str = L"Оценка экспертов: " + DoubleToStr(iter.GetMark()) + L"\n";
		fl.WriteString(str);
	}
	MessageBox(L"Отчет сохранен в локальной папке под названием \"Отчет.txt\"");
	//o.close();
}

void CMenuDlg::AddToReport(Car& obj)
{
	CString strFormat;
	int index = m_wndReportCtrl.InsertItem(INDEX_NAME, AtoW(obj.GetName()));
	m_wndReportCtrl.SetItemText(index, INDEX_TYPE, AtoW(obj.GetType()));
	strFormat.Format(L"%0.2lf", obj.GetCost());
	m_wndReportCtrl.SetItemText(index, INDEX_COST, strFormat);
	strFormat.Format(L"%0.2lf", obj.GetPower());
	m_wndReportCtrl.SetItemText(index, INDEX_WEIGHT, strFormat);
	strFormat.Format(L"%0.2lf", obj.GetMark());
	m_wndReportCtrl.SetItemText(index, INDEX_MARK, strFormat);
}



