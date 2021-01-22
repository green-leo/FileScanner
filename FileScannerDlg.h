
// FileScannerDlg.h : header file
//

#pragma once


// CFileScannerDlg dialog
class CFileScannerDlg : public CDialogEx
{
// Construction
public:
	CFileScannerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILESCANNER_DIALOG };
#endif

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
	afx_msg void OnEnChangeEditPath();
	afx_msg void OnEnChangeEditFilename();
	afx_msg void OnBnClickedFind();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnLvnItemchangedListfile(NMHDR* pNMHDR, LRESULT* pResult);
	
	void AddData(CListCtrl& ctrl, int row, int col, CString str);
	CString TimeConvert(FILETIME time);

	CListCtrl m_listCtrl;
	CString m_filepath;
	CString m_filename;
	CEdit m_filepathCtrl;
	CEdit m_filenameCtrl;
};
