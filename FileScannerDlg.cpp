
// FileScannerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "FileScanner.h"
#include "FileScannerDlg.h"
#include "afxdialogex.h"

#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <string>
#include <fileapi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFileScannerDlg dialog



CFileScannerDlg::CFileScannerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILESCANNER_DIALOG, pParent)
	, m_filepath(_T(""))
	, m_filename(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileScannerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTFILE, m_listCtrl);

	DDX_Text(pDX, IDC_EDIT_PATH, m_filepath);
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_filename);

	m_listCtrl.InsertColumn(
		0,              // Rank/order of item 
		L"ID",          // Caption for this header 
		LVCFMT_LEFT,    // Relative position of items under header 
		40);           // Width of items under header

	m_listCtrl.InsertColumn(1, L"Filename", LVCFMT_LEFT, 153);
	m_listCtrl.InsertColumn(2, L"Size", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(3, L"Full path", LVCFMT_LEFT, 160);
	m_listCtrl.InsertColumn(4, L"Date created", LVCFMT_LEFT, 130);
	m_listCtrl.InsertColumn(5, L"Date modified", LVCFMT_LEFT, 130);

	DDX_Control(pDX, IDC_EDIT_PATH, m_filepathCtrl);
	DDX_Control(pDX, IDC_EDIT_FILENAME, m_filenameCtrl);
}

BEGIN_MESSAGE_MAP(CFileScannerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_EN_CHANGE(IDC_EDIT_PATH, &CFileScannerDlg::OnEnChangeEditPath)
	ON_EN_CHANGE(IDC_EDIT_FILENAME, &CFileScannerDlg::OnEnChangeEditFilename)
	ON_BN_CLICKED(IDC_FIND, &CFileScannerDlg::OnBnClickedFind)
	ON_BN_CLICKED(IDC_Cancel, &CFileScannerDlg::OnBnClickedCancel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTFILE, &CFileScannerDlg::OnLvnItemchangedListfile)


END_MESSAGE_MAP()


// CFileScannerDlg message handlers

BOOL CFileScannerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFileScannerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFileScannerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFileScannerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFileScannerDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CFileScannerDlg::OnEnChangeEditPath()
{
	m_filepathCtrl.GetWindowTextW(m_filepath);
}


void CFileScannerDlg::OnEnChangeEditFilename()
{
	m_filenameCtrl.GetWindowTextW(m_filename);
}


void CFileScannerDlg::OnBnClickedFind()
{
	// TODO: Add your control notification handler code here
	m_listCtrl.DeleteAllItems();
	int count = 0;
	
	CString pattern(m_filepath);
	pattern.Append(_T("\\*"));

	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(pattern, &data)) != INVALID_HANDLE_VALUE) {
		do {
			CString filenameFound(data.cFileName);
			filenameFound.Remove('.');
			if (filenameFound.Find(m_filename) != -1 && !filenameFound.IsEmpty()) {
				CString id_str;
				id_str.Format(L"%d", count);
				
				HANDLE hFile;
				FILETIME ftCreate, ftWrite;
				DWORD filesize;
				CString size_str;

				hFile = CreateFile(m_filepath + '/' + data.cFileName, GENERIC_READ, FILE_SHARE_READ, NULL,
					OPEN_EXISTING, 0, NULL);
				GetFileTime(hFile, &ftCreate, NULL, &ftWrite);
				
				filesize = GetFileSize(hFile, NULL);
				filesize = (double)filesize / 1024;
				size_str.Format(L"~%d KB", filesize);

				AddData(m_listCtrl, count, 0, id_str);
				AddData(m_listCtrl, count, 1, data.cFileName);
				AddData(m_listCtrl, count, 2, size_str);
				AddData(m_listCtrl, count, 3, m_filepath + '/' + data.cFileName);
				AddData(m_listCtrl, count, 4, TimeConvert(ftCreate));
				AddData(m_listCtrl, count, 5, TimeConvert(ftWrite));

				count++;
			}
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}

	
}



void CFileScannerDlg::OnLvnItemchangedListfile(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here

	*pResult = 0;
}

void CFileScannerDlg::AddData(CListCtrl& ctrl, int row, int col, CString str)
{
	LVITEM lv;
	lv.iItem = row;
	lv.iSubItem = col;
	lv.pszText = (LPWSTR)(LPCTSTR)str;
	lv.mask = LVIF_TEXT;
	if (col == 0)
		ctrl.InsertItem(&lv);
	else
		ctrl.SetItem(&lv);
}


CString CFileScannerDlg::TimeConvert(FILETIME time) 
{
	TCHAR dateModified[1000];
	SYSTEMTIME stUTC, stLocal;
	DWORD dwRet;

	FileTimeToSystemTime(&time, &stUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

	dwRet = StringCchPrintf(dateModified, 1000,
		TEXT("%02d/%02d/%d  %02d:%02d"),
		stLocal.wMonth, stLocal.wDay, stLocal.wYear,
		stLocal.wHour, stLocal.wMinute);

	return (LPWSTR)(LPCTSTR)dateModified;
}