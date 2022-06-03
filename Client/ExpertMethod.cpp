// CExpDlg.cpp : implementation file
//

#include "pch.h"
#include "CourceWorkApp.h"
#include "ExpertMethod.h"
#include "afxdialogex.h"
#include "Formatter.h"


// CExpDlg dialog

IMPLEMENT_DYNAMIC(CExpDlg, CDialogEx)

CExpDlg::CExpDlg(std::vector<Car>& lst, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_EXPERT_METHOD, pParent),
	vect(lst)
{

}

CExpDlg::~CExpDlg()
{
}

BOOL CExpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	static1.SetWindowText(AtoW(vect[0].GetName()));
	static2.SetWindowText(AtoW(vect[1].GetName()));
	static3.SetWindowText(AtoW(vect[2].GetName()));
	static4.SetWindowText(AtoW(vect[3].GetName()));
	static5.SetWindowText(AtoW(vect[4].GetName()));

	static1k.SetWindowText(L"");
	static1r.SetWindowText(L"");
	static2k.SetWindowText(L"");
	static2r.SetWindowText(L"");
	static3k.SetWindowText(L"");
	static3r.SetWindowText(L"");
	static4k.SetWindowText(L"");
	static4r.SetWindowText(L"");
	static5k.SetWindowText(L"");
	static5r.SetWindowText(L"");

	//PostMessage(MSG_UPDATE);

	return TRUE;
}

void CExpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC1, static1);
	DDX_Control(pDX, IDC_STATIC2, static2);
	DDX_Control(pDX, IDC_STATIC3, static3);
	DDX_Control(pDX, IDC_STATIC4, static4);
	DDX_Control(pDX, IDC_STATIC5, static5);

	DDX_Control(pDX, IDC_STATIC_K1, static1k);
	DDX_Control(pDX, IDC_STATIC_K2, static2k);
	DDX_Control(pDX, IDC_STATIC_K3, static3k);
	DDX_Control(pDX, IDC_STATIC_K4, static4k);
	DDX_Control(pDX, IDC_STATIC_K5, static5k);

	DDX_Control(pDX, IDC_STATIC_RES1, static1r);
	DDX_Control(pDX, IDC_STATIC_RES2, static2r);
	DDX_Control(pDX, IDC_STATIC_RES3, static3r);
	DDX_Control(pDX, IDC_STATIC_RES4, static4r);
	DDX_Control(pDX, IDC_STATIC_RES5, static5r);

	DDX_Control(pDX, IDC_COMBO1, edit1);
	DDX_Control(pDX, IDC_COMBO2, edit2);
	DDX_Control(pDX, IDC_COMBO3, edit3);
	DDX_Control(pDX, IDC_COMBO4, edit4);
	DDX_Control(pDX, IDC_COMBO5, edit5);
	DDX_Control(pDX, IDC_EDIT1, weight);
	DDX_Control(pDX, IDC_BUTTON_START, button);
}


BEGIN_MESSAGE_MAP(CExpDlg, CDialogEx)
	ON_MESSAGE_VOID(MSG_UPDATE, UpdatePage)
	ON_BN_CLICKED(IDC_BUTTON_START, &CExpDlg::OnBnClickedOk)
END_MESSAGE_MAP()


void CExpDlg::UpdatePage()
{

}

BOOL CExpDlg::PreTranslateMessage(MSG* pMsg)
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

// CExpDlg message handlers

void CExpDlg::OnBnClickedOk()
{
	double k1 = 0;
	double k2 = 0;
	double k3 = 0;
	double k4 = 0;
	double k5 = 0;
	double dWeight = 0;

	int index;
	CString str;
	edit1.GetWindowText(str);
	if (str.IsEmpty() || _wtoi(str) < 0 || _wtoi(str) > 100)
	{
		MessageBox(L"ќценки должны иметь значение от 0 до 100");
		return;
	}
	else k1 = _wtoi(str);
	edit2.GetWindowText(str);
	if (str.IsEmpty() || _wtoi(str) < 0 || _wtoi(str) > 100)
	{
		MessageBox(L"ќценки должны иметь значение от 0 до 100");
		return;
	}
	else k2 = _wtoi(str);
	edit3.GetWindowText(str);
	if (str.IsEmpty() || _wtoi(str) < 0 || _wtoi(str) > 100)
	{
		MessageBox(L"ќценки должны иметь значение от 0 до 100");
		return;
	}
	else k3 = _wtoi(str);
	edit4.GetWindowText(str);
	if (str.IsEmpty() || _wtoi(str) < 0 || _wtoi(str) > 100)
	{
		MessageBox(L"ќценки должны иметь значение от 0 до 100");
		return;
	}
	else k4 = _wtoi(str);
	edit5.GetWindowText(str);
	if (str.IsEmpty() || _wtoi(str) < 0 || _wtoi(str) > 100)
	{
		MessageBox(L"ќценки должны иметь значение от 0 до 100");
		return;
	}
	else k5 = _wtoi(str);
	weight.GetWindowText(str);
	if (str.IsEmpty() || _wtof(str) < 0 || _wtof(str) > 1)
	{
		MessageBox(L"ќценки должны иметь значение от 0 до 1");
		return;
	}
	else dWeight = _wtof(str);

	if (k1 + k2 + k3 + k4 + k5 != 100)
	{
		MessageBox(L"—умма оценок должна быть равна 100");
		return;
	}

	double sum = k1 + k2 + k3 + k4 + k5;
	k1 /= sum;
	k2 /= sum;
	k3 /= sum;
	k4 /= sum;
	k5 /= sum;

	k1 *= dWeight;
	k2 *= dWeight;
	k3 *= dWeight;
	k4 *= dWeight;
	k5 *= dWeight;

	vect[0].SetMark(k1);
	vect[1].SetMark(k2);
	vect[2].SetMark(k3);
	vect[3].SetMark(k4);
	vect[4].SetMark(k5);

	static1k.SetWindowText(DoubleToStr(k1));
	static2k.SetWindowText(DoubleToStr(k2));
	static3k.SetWindowText(DoubleToStr(k3));
	static4k.SetWindowText(DoubleToStr(k4));
	static5k.SetWindowText(DoubleToStr(k5));

	double max = 0;
	for (auto i : { k1, k2, k3, k4, k5 })
	{
		if (max < i)max = i;
	}

	CString winner = L"";

	if (k1 == max)
	{
		static1r.SetWindowText(L"Ћучший результат");
		winner += AtoW(vect[0].GetName());
	}
	if (k2 == max)
	{
		static2r.SetWindowText(L"Ћучший результат");
		if (!winner.IsEmpty())winner += L", ";
		winner += AtoW(vect[1].GetName());
	}
	if (k3 == max)
	{
		static3r.SetWindowText(L"Ћучший результат");
		if (!winner.IsEmpty())winner += L", ";
		winner += AtoW(vect[2].GetName());
	}
	if (k4 == max)
	{
		static4r.SetWindowText(L"Ћучший результат");
		if (!winner.IsEmpty())winner += L", ";
		winner += AtoW(vect[3].GetName());
	}
	if (k5 == max)
	{
		static5r.SetWindowText(L"Ћучший результат");
		if (!winner.IsEmpty())winner += L", ";
		winner += AtoW(vect[4].GetName());
	}

	CString strFormat;
	strFormat.Format(L"–езультат:\n%s = %.2lf\n%s = %.2lf\n%s = %.2lf\n%s = %.2lf\n%s = %.2lf\n\nЋучшие результаты у: %s\n"
		, AtoW(vect[0].GetName()), k1, AtoW(vect[1].GetName()), k2, AtoW(vect[2].GetName()), k3, AtoW(vect[3].GetName()), k4, AtoW(vect[4].GetName()), k5, winner);

	MessageBox(strFormat);

	CDialogEx::OnOK();
}
