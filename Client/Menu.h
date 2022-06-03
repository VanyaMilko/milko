#pragma once
#include "ClientConnectionModule.h"

class CMenuDlg : public CDialogEx
{
public:
	CMenuDlg(CWnd* pParent = nullptr);
	~CMenuDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PATTERN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	void UpdatePage();
protected:

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnBtnUserClck();
	afx_msg void OnBtnExpertClck();
	afx_msg void OnBtnExitClck();
	afx_msg void OnStart();

	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedEdit();
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedFilter();
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedReport();
	void AddToReport(Car& cloth);

	DECLARE_MESSAGE_MAP()

	HICON m_hIcon;
	ClientConnectionModule* m_pModule;
	TypeOfUser m_TypeOfUser;

	CButton m_wndBtnUser;
	CButton m_wndBtnExpert;
	CButton m_wndBtnExit;

	std::list<Car> m_Dishes;

	CString strNameFilter;
	CString strTypeFilter;

	double nMinCost;
	double nMaxCost;
	double dMinMark;
	double dMaxMark;
	double dMinWeight;
	double dMaxWeight;

	CListCtrl m_wndReportCtrl;

	CButton m_wndBtnApplyFilter;
	CButton m_wndBtnApplySearch;
	CButton m_wndBtnAdd;
	CButton m_wndBtnDel;
	CButton m_wndBtnEdit;

	CEdit m_wndEdit1From;
	CEdit m_wndEdit1To;
	CEdit m_wndEdit2From;
	CEdit m_wndEdit2To;
	CEdit m_wndEditMarkFrom;
	CEdit m_wndEditMarkTo;
	CEdit m_wndEditFilterName;
	CEdit m_wndEditFilterType;
	CButton m_wndBtnReport;
};
