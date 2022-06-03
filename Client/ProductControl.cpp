#include "pch.h"
//// CProductCtrlDlg.cpp : implementation file
////
//
//#include "pch.h"
//#include "CourceWorkApp.h"
//#include "ProductControl.h"
//#include "afxdialogex.h"
//#include "../SerializableEntities/Object.h"
//#include "AddProduct.h"
//#include "Formatter.h"
//#include <fstream>
//#include <iomanip>
//
//#define INDEX_NAME    0
//#define INDEX_TYPE    1
//#define INDEX_COST    2
//#define INDEX_WEIGHT  3
//#define INDEX_MARK    4
//
//// CProductCtrlDlg dialog
//
//IMPLEMENT_DYNAMIC(CProductCtrlDlg, CDialogEx)
//
//CProductCtrlDlg::CProductCtrlDlg(ClientConnectionModule* pModule, TypeOfUser type, CWnd* pParent /*=nullptr*/)
//	: CDialogEx(IDD_DIALOG_PRODUCT_CONTROL, pParent)
//{
//	m_pModule = pModule;
//	m_TypeOfUser = type;
//
//	nMinCost = -1;
//	nMaxCost = -1;
//	dMinMark = -1.0;
//	dMaxMark = -1.0;
//	dMinWeight = -1.0;
//	dMaxWeight = -1.0;
//}
//
//CProductCtrlDlg::~CProductCtrlDlg()
//{
//}
//
//BOOL CProductCtrlDlg::OnInitDialog()
//{
//	CDialogEx::OnInitDialog();
//
//	m_wndReportCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);
//
//	m_wndReportCtrl.InsertColumn(INDEX_NAME, L"Название", 0, 220);
//	m_wndReportCtrl.InsertColumn(INDEX_TYPE, L"Тип", 0, 150);
//	m_wndReportCtrl.InsertColumn(INDEX_COST, L"Стоимость, руб.", 0, 80);
//	m_wndReportCtrl.InsertColumn(INDEX_WEIGHT, L"Вес, кг.", 0, 150);
//	m_wndReportCtrl.InsertColumn(INDEX_MARK, L"Оценка", 0, 56);
//
//	PostMessage(MSG_UPDATE);
//	return 0;
//}
//
//void CProductCtrlDlg::DoDataExchange(CDataExchange* pDX)
//{
//	CDialogEx::DoDataExchange(pDX);
//	DDX_Control(pDX, IDC_LIST_PRODUCTS, m_wndReportCtrl);
//	DDX_Control(pDX, IDC_BUTTON_FILTER_APPLY, m_wndBtnApplyFilter);
//	DDX_Control(pDX, IDC_BUTTON_SEARCH_APPLY, m_wndBtnApplySearch);
//	DDX_Control(pDX, IDC_BUTTON_ADD, m_wndBtnAdd);
//	DDX_Control(pDX, IDC_BUTTON_DELETE, m_wndBtnDel);
//	DDX_Control(pDX, IDC_BUTTON_EDIT, m_wndBtnEdit);
//	DDX_Control(pDX, IDC_EDIT_1_FROM, m_wndEdit1From);
//	DDX_Control(pDX, IDC_EDIT_1_TO, m_wndEdit1To);
//	DDX_Control(pDX, IDC_EDIT_2_FROM, m_wndEdit2From);
//	DDX_Control(pDX, IDC_EDIT_2_TO, m_wndEdit2To);
//	DDX_Control(pDX, IDC_EDIT_MARK_FROM, m_wndEditMarkFrom);
//	DDX_Control(pDX, IDC_EDIT_MARK_TO, m_wndEditMarkTo);
//	DDX_Control(pDX, IDC_EDIT_SEARCH_NAME, m_wndEditFilterName);
//	DDX_Control(pDX, IDC_EDIT_SEARCH_TYPE, m_wndEditFilterType);
//	DDX_Control(pDX, IDC_BUTTON_REPORT, m_wndBtnReport);
//}
//
//BEGIN_MESSAGE_MAP(CProductCtrlDlg, CDialogEx)
//	ON_MESSAGE_VOID(MSG_UPDATE, UpdatePage)
//	ON_BN_CLICKED(IDC_BUTTON_ADD, OnBnClickedAdd)
//	ON_BN_CLICKED(IDC_BUTTON_EDIT, OnBnClickedEdit)
//	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnBnClickedDel)
//	ON_BN_CLICKED(IDC_BUTTON_FILTER_APPLY, OnBnClickedFilter)
//	ON_BN_CLICKED(IDC_BUTTON_SEARCH_APPLY, OnBnClickedSearch)
//	ON_BN_CLICKED(IDC_BUTTON_REPORT, OnBnClickedReport)
//END_MESSAGE_MAP()
//
//void CProductCtrlDlg::UpdatePage()
//{
//	m_wndBtnAdd.EnableWindow(m_TypeOfUser == TypeOfUser::ADMIN ? TRUE : FALSE);
//	m_wndBtnEdit.EnableWindow(m_TypeOfUser == TypeOfUser::ADMIN ? TRUE : FALSE);
//	m_wndBtnDel.EnableWindow(m_TypeOfUser == TypeOfUser::ADMIN ? TRUE : FALSE);
//
//	m_Dishes = m_pModule->getAllObj();
//	m_wndReportCtrl.DeleteAllItems();
//
//	for (auto iter : m_Dishes)
//	{
//		bool bShow = true;
//		if (!strNameFilter.IsEmpty())bShow &= AtoW(iter.GetName()).Find(strNameFilter) != -1;
//		if (!strTypeFilter.IsEmpty())bShow &= AtoW(iter.GetType()).Find(strTypeFilter) != -1;
//
//		if (nMinCost != -1) bShow &= iter.GetCost() >= nMinCost;
//		if (nMaxCost != -1) bShow &= iter.GetCost() <= nMaxCost;
//
//		if (dMinMark != -1.0) bShow &= iter.GetMark() >= dMinMark;
//		if (dMaxMark != -1.0) bShow &= iter.GetMark() <= dMaxMark;
//
//		if (dMinWeight != -1.0) bShow &= iter.GetWeight() >= dMinWeight;
//		if (dMaxWeight != -1.0) bShow &= iter.GetWeight() <= dMaxWeight;
//
//		if (bShow)AddToReport(iter);
//	}
//}
//
//void CProductCtrlDlg::OnBnClickedAdd()
//{
//	Tractor cloth;
//	CAddDlg dlg;
//
//	if (dlg.DoModal(&cloth) == S_OK)
//	{
//		m_pModule->addOneObj(cloth);
//	}
//
//	UpdatePage();
//}
//
//void CProductCtrlDlg::OnBnClickedEdit()
//{
//	auto pos = m_wndReportCtrl.GetFirstSelectedItemPosition();
//
//	if (!pos)
//		return;
//
//	int index = m_wndReportCtrl.GetNextSelectedItem(pos);
//
//	Tractor obj;
//
//	obj.SetName(WtoA(m_wndReportCtrl.GetItemText(index, INDEX_NAME)));
//	obj.SetType(WtoA(m_wndReportCtrl.GetItemText(index, INDEX_TYPE)));
//	obj.SetCost(_wtof(m_wndReportCtrl.GetItemText(index, INDEX_COST)));
//	obj.SetWeight(_wtof(m_wndReportCtrl.GetItemText(index, INDEX_WEIGHT)));
//	obj.SetMark(_wtof(m_wndReportCtrl.GetItemText(index, INDEX_MARK)));
//
//	for (auto iter : m_Dishes)
//	{
//		if (obj == iter)
//		{
//			obj.SetId(iter.GetId());
//			break;
//		}
//	}
//
//	CAddDlg dlg;
//
//	if (dlg.DoModal(&obj) == S_OK)
//	{
//		auto answer = m_pModule->editOneObj(obj);
//		switch (answer)
//		{
//		case AnswerFromServer::_ERROR: MessageBox(L"ERROR"); break;
//		case AnswerFromServer::UNKNOWN_COMMAND: MessageBox(L"Неизвестная команда"); break;
//		}
//	}
//
//	UpdatePage();
//}
//
//void CProductCtrlDlg::OnBnClickedDel()
//{
//	auto pos = m_wndReportCtrl.GetFirstSelectedItemPosition();
//
//	if (!pos)
//		return;
//
//	int index = m_wndReportCtrl.GetNextSelectedItem(pos);
//
//	Tractor obj;
//
//	obj.SetName(WtoA(m_wndReportCtrl.GetItemText(index, INDEX_NAME)));
//	obj.SetType(WtoA(m_wndReportCtrl.GetItemText(index, INDEX_TYPE)));
//	obj.SetCost(_wtof(m_wndReportCtrl.GetItemText(index, INDEX_COST)));
//	obj.SetWeight(_wtof(m_wndReportCtrl.GetItemText(index, INDEX_WEIGHT)));
//	obj.SetMark(_wtof(m_wndReportCtrl.GetItemText(index, INDEX_MARK)));
//
//	for (auto iter : m_Dishes)
//	{
//		if (obj == iter)
//		{
//			obj = iter;
//			break;
//		}
//	}
//
//	auto answer = m_pModule->delOneObj(obj);
//	switch (answer)
//	{
//	case AnswerFromServer::_ERROR: MessageBox(L"ERROR"); break;
//	case AnswerFromServer::UNKNOWN_COMMAND: MessageBox(L"Неизвестная команда"); break;
//	}
//
//	UpdatePage();
//}
//
//void CProductCtrlDlg::OnBnClickedSearch()
//{
//	m_wndEditFilterName.GetWindowText(strNameFilter);
//	m_wndEditFilterType.GetWindowText(strTypeFilter);
//
//	UpdatePage();
//}
//
//BOOL CProductCtrlDlg::PreTranslateMessage(MSG* pMsg)
//{
//	if (pMsg->message == WM_KEYDOWN)
//	{
//		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
//		{
//			return TRUE;                // Do not process further
//		}
//	}
//
//	return CWnd::PreTranslateMessage(pMsg);
//}
//
//void CProductCtrlDlg::OnBnClickedFilter()
//{
//	CString str;
//
//	m_wndEdit1From.GetWindowText(str);
//	nMinCost = (str.GetLength() ? _wtoi(str) : -1);
//
//	m_wndEdit1To.GetWindowText(str);
//	nMaxCost = (str.GetLength() ? _wtoi(str) : -1);
//
//	m_wndEdit2From.GetWindowText(str);
//	dMinWeight = (str.GetLength() ? _wtof(str) : -1.0);
//
//	m_wndEdit2To.GetWindowText(str);
//	dMaxWeight = (str.GetLength() ? _wtof(str) : -1.0);
//
//	m_wndEditMarkFrom.GetWindowText(str);
//	dMinMark = (str.GetLength() ? _wtof(str) : -1.0);
//
//	m_wndEditMarkTo.GetWindowText(str);
//	dMaxMark = (str.GetLength() ? _wtof(str) : -1.0);
//
//	UpdatePage();
//}
//
//void CProductCtrlDlg::OnBnClickedReport()
//{
//	int nRated = 0;
//	for (auto iter : m_Dishes)
//	{
//		if (iter.GetMark() != 0)nRated++;
//	}
//
//	CStdioFile  fl;
//	fl.Open(L"Отчет.txt", CFile::modeCreate | CFile::modeWrite);
//	CString str = L"Количетво записей: " + IntToStr(m_Dishes.size()) + L"\n";
//	fl.WriteString(str);
//	str = L"Количетво оцененных записей: " + IntToStr(nRated) + L"\n";
//	fl.WriteString(str);
//	for (auto iter : m_Dishes)
//	{
//		str = L"Название: " + AtoW(iter.GetName()) + L"\n";
//		fl.WriteString(str);
//		str = L"Тип: " + AtoW(iter.GetType()) + L"\n";
//		fl.WriteString(str);
//		str = L"Стоимость: " + IntToStr(iter.GetCost()) + L" руб.\n";
//		fl.WriteString(str);
//		str = L"Вес: " + DoubleToStr(iter.GetWeight()) + L"кг.\n";
//		fl.WriteString(str);
//		str = L"Оценка экспертов: " + DoubleToStr(iter.GetMark()) + L"\n";
//		fl.WriteString(str);
//	}
//	MessageBox(L"Отчет сохранен в локальной папке под названием \"Отчет.txt\"");
//	//o.close();
//}
//
//void CProductCtrlDlg::AddToReport(Tractor& obj)
//{
//	CString strFormat;
//	int index = m_wndReportCtrl.InsertItem(INDEX_NAME, AtoW(obj.GetName()));
//	m_wndReportCtrl.SetItemText(index, INDEX_TYPE, AtoW(obj.GetType()));
//	strFormat.Format(L"%0.2lf", obj.GetCost());
//	m_wndReportCtrl.SetItemText(index, INDEX_COST, strFormat);
//	strFormat.Format(L"%0.2lf", obj.GetWeight());
//	m_wndReportCtrl.SetItemText(index, INDEX_WEIGHT, strFormat);
//	strFormat.Format(L"%0.2lf", obj.GetMark());
//	m_wndReportCtrl.SetItemText(index, INDEX_MARK, strFormat);
//}
