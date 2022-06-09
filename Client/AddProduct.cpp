// CAddDishDlg.cpp : implementation file
//

#include "pch.h"
#include "CourceWorkApp.h"
#include "AddProduct.h"
#include "afxdialogex.h"
#include "Formatter.h"


IMPLEMENT_DYNAMIC(CAddDlg, CDialogEx)

CAddDlg::CAddDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADD_PRODUCT, pParent)
{
	m_pObj = NULL;
	m_nResult = S_FALSE;
}

CAddDlg::~CAddDlg()
{
}

void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_TYPE, m_editType);
	DDX_Control(pDX, IDC_EDIT_1, m_edit1);
	DDX_Control(pDX, IDC_EDIT_2, m_edit2);
	DDX_Control(pDX, IDC_STATIC_INCORRECT, m_wndIncorrect);
}

BOOL CAddDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowText(bEdit ? L"Редактирование" : L"Добавление");

	m_editName.SetWindowText(bEdit ? AtoW(m_pObj->GetName()) : L"");
	m_editType.SetWindowText(bEdit ? AtoW(m_pObj->GetType()) : L"");
	m_edit1.SetWindowText(bEdit ? DoubleToStr(m_pObj->GetCost()) : L"0");
	m_edit2.SetWindowText(bEdit ? DoubleToStr(m_pObj->GetPower()) : L"0");


	m_wndIncorrect.ShowWindow(SW_HIDE);

	return TRUE;
}

void CAddDlg::UpdatePage()
{

}

BOOL CAddDlg::PreTranslateMessage(MSG* pMsg)
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

int CAddDlg::DoModal(Car* obj)
{
	if (!obj)
		return 0;

	m_pObj = obj;
	CString str = AtoW(m_pObj->GetName());
	if (str.GetLength())
		bEdit = TRUE;
	CDialogEx::DoModal();

	return m_nResult;
}


BEGIN_MESSAGE_MAP(CAddDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddDlg::OnBnClickedOk)
	ON_MESSAGE_VOID(MSG_UPDATE, UpdatePage)
END_MESSAGE_MAP()


void CAddDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	CString str;

	m_editName.GetWindowText(str);
	if (str.IsEmpty()) { m_wndIncorrect.ShowWindow(SW_SHOW); return; }
	m_pObj->SetName(WtoA(str));

	m_editType.GetWindowText(str);
	if (str.IsEmpty()) { m_wndIncorrect.ShowWindow(SW_SHOW); return; }
	m_pObj->SetType(WtoA(str));

	m_edit1.GetWindowText(str);
	if (str.IsEmpty() || _wtof(str) == 0) { m_wndIncorrect.ShowWindow(SW_SHOW); return; }
	m_pObj->SetCost(_wtof(str));

	m_edit2.GetWindowText(str);
	if (str.IsEmpty() || _wtof(str) == 0) { m_wndIncorrect.ShowWindow(SW_SHOW); return; }
	m_pObj->SetPower(_wtof(str));

	UpdateData(FALSE);

	m_nResult = S_OK;

	CDialogEx::OnOK();
}
