#pragma once
#include <vector>
#include "../SerializableEntities/Object.h"


// CExpDlg dialog

class CExpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CExpDlg)

public:
	CExpDlg(std::vector<Car>& lst, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CExpDlg();

	virtual BOOL OnInitDialog();
	BOOL PreTranslateMessage(MSG* pMsg);
	void UpdatePage();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_EXPERT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

	std::vector<Car>& vect;

	CStatic static1;
	CStatic static2;
	CStatic static3;
	CStatic static4;
	CStatic static5;

	CStatic static1k;
	CStatic static2k;
	CStatic static3k;
	CStatic static4k;
	CStatic static5k;

	CStatic static1r;
	CStatic static2r;
	CStatic static3r;
	CStatic static4r;
	CStatic static5r;

	CEdit edit1;
	CEdit edit2;
	CEdit edit3;
	CEdit edit4;
	CEdit edit5;

	CEdit weight;

	CButton button;
};
