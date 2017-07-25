
// ImportBODlg.h : header file
//

#pragma once


// CImportBODlg dialog
class CImportBODlg : public CDialogEx
{
// Construction
public:
	CImportBODlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_IMPORTBO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnAddcsv();
	afx_msg void OnBnClickedBtnSend();
	afx_msg void OnBnClickedBtnExecute();
protected:
	int m_nPort;
	DWORD m_dwIpAddr;
	CString m_szTable;
	BOOL m_bSkipHeader;
	int m_nMySqlPort;
	CString m_szSql;
};
