#pragma once
#include "../SerializableEntities/Object.h"

// CAddDishDlg dialog

class CAddDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddDlg)

public:
	CAddDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CAddDlg();
	int DoModal(Car* dish);
	BOOL PreTranslateMessage(MSG* pMsg);
	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD_PRODUCT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();
	void CAddDlg::UpdatePage();

	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

	Car* m_pObj;
	BOOL bEdit;

	int m_nResult;

	CEdit m_editName;
	CEdit m_editType;
	CEdit m_edit1;
	CEdit m_edit2;
	CEdit m_editMark;

	CStatic m_wndIncorrect;
};
