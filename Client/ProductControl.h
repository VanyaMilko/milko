//#pragma once
//#include "../SerializableEntities/Object.h"
//#include "ClientConnectionModule.h"
//
//// CProductCtrlDlg dialog
//
//class CProductCtrlDlg : public CDialogEx
//{
//	DECLARE_DYNAMIC(CProductCtrlDlg)
//
//public:
//	CProductCtrlDlg(ClientConnectionModule* pModule, TypeOfUser type, CWnd* pParent = nullptr);   // standard constructor
//	virtual ~CProductCtrlDlg();
//	virtual BOOL OnInitDialog();
//	BOOL PreTranslateMessage(MSG* pMsg);
//	void UpdatePage();
//	// Dialog Data
//#ifdef AFX_DESIGN_TIME
//	enum { IDD = IDD_DIALOG_PRODUCT_CONTROL };
//#endif
//
//protected:
//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
//
//	void AddToReport(Tractor& cloth);
//
//	afx_msg void OnBnClickedAdd();
//	afx_msg void OnBnClickedEdit();
//	afx_msg void OnBnClickedDel();
//	afx_msg void OnBnClickedFilter();
//	afx_msg void OnBnClickedSearch();
//	afx_msg void OnBnClickedReport();
//
//	DECLARE_MESSAGE_MAP()
//
//	ClientConnectionModule* m_pModule;
//	TypeOfUser m_TypeOfUser;
//
//	
//};
