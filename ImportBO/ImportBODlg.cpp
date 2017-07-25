
// ImportBODlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImportBO.h"
#include "ImportBODlg.h"
#include "afxdialogex.h"

#include "odbcinst.h"
#include "afxdb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CImportBODlg dialog



CImportBODlg::CImportBODlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CImportBODlg::IDD, pParent)
	, m_nPort(0)
	, m_dwIpAddr(0)
	, m_szTable(_T(""))
	, m_bSkipHeader(FALSE)
	, m_nMySqlPort(0)
	, m_szSql(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImportBODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDV_MinMaxInt(pDX, m_nPort, 1024, 65535);
	DDX_IPAddress(pDX, IDC_IP_HOST, m_dwIpAddr);
	DDX_Text(pDX, IDC_EDIT_TABLE, m_szTable);
	DDV_MaxChars(pDX, m_szTable, 30);
	DDX_Check(pDX, IDC_CHK_SKIP_HDR, m_bSkipHeader);
	DDX_Text(pDX, IDC_EDIT_MYSQLPORT, m_nMySqlPort);
	DDV_MinMaxInt(pDX, m_nMySqlPort, 1024, 65536);
	DDX_Text(pDX, IDC_EDIT_SQL, m_szSql);
	DDV_MaxChars(pDX, m_szSql, 4096);
}

BEGIN_MESSAGE_MAP(CImportBODlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ADDCSV, &CImportBODlg::OnBnClickedBtnAddcsv)
	ON_BN_CLICKED(IDC_BTN_SEND, &CImportBODlg::OnBnClickedBtnSend)
	ON_BN_CLICKED(IDC_BTN_EXECUTE, &CImportBODlg::OnBnClickedBtnExecute)
END_MESSAGE_MAP()


// CImportBODlg message handlers

BOOL CImportBODlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	m_nPort = 9091;
	m_bSkipHeader = TRUE;
	m_szSql = L"INSERT INTO ";
	m_nMySqlPort = 3306;
	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CImportBODlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CImportBODlg::OnPaint()
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
HCURSOR CImportBODlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CImportBODlg::OnBnClickedBtnAddcsv()
{
	CFileDialog dlg(TRUE);
    dlg.m_ofn.lpstrFilter = _T("csv Files (*.csv)\0*.csv\0All Files (*.*)\0*.*\0\0");
    //dlg.m_ofn.lpstrTitle = _T("Select csv file to import");
 
    CString filename;
 
    if(dlg.DoModal() == IDOK)
    {
        filename = dlg.GetPathName();
		GetDlgItem(IDC_EDIT_FILENAME)->SetWindowText(filename);
    }
}


void CImportBODlg::OnBnClickedBtnSend()
{
	UpdateData(TRUE);
	CString filename;
	GetDlgItem(IDC_EDIT_FILENAME)->GetWindowText(filename);

	if (filename.IsEmpty()) {
		AfxMessageBox(_T("No file is selected."));
		return;
	}
	if (0 == m_dwIpAddr || 0 == m_nPort) {
		AfxMessageBox(_T("Invalid host ip address or port number."));
		return;
	}
	if (m_szTable.IsEmpty()) {
		AfxMessageBox(_T("Table name is required."));
		return;
	}

	CString msg;
	HANDLE hCsvFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hCsvFile) {
		msg.Format(_T("Fail to open '%s': %d"), filename, ::GetLastError());
		AfxMessageBox(msg);
		return;
	}

	struct sockaddr_in  addrBo;
	SOCKET skBo = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == skBo) {
		AfxMessageBox(_T("Fail to create socket!"));
		return;
	}

	ZeroMemory(&addrBo, sizeof(addrBo));
    addrBo.sin_family = AF_INET;
	addrBo.sin_addr.S_un.S_addr = htonl(m_dwIpAddr);
    addrBo.sin_port = htons(m_nPort);
	if (connect(skBo, (struct sockaddr*)&addrBo, sizeof(addrBo)) == ERROR_SUCCESS) {
		char csvHdr[48] = {0}; // "csv\x01<table>\x0skip_lines=1"
		csvHdr[0] = 'c';
		csvHdr[1] = 's';
		csvHdr[2] = 'v';
		csvHdr[3] = 1;

		size_t szConverted = 0;
		wcstombs_s(&szConverted, &csvHdr[4], sizeof(csvHdr)-4, m_szTable, _TRUNCATE);

		int nHdrLen = strlen(&csvHdr[4]) + 5;
		if (m_bSkipHeader) {
			strcpy_s(&csvHdr[nHdrLen], sizeof(csvHdr) - nHdrLen, "skip_lines=1");
			nHdrLen += 13;
		}

		TRANSMIT_FILE_BUFFERS sndBuf = {0};
		sndBuf.Head = csvHdr;
		sndBuf.HeadLength = nHdrLen;

		if (!TransmitFile(skBo, hCsvFile, 0, 0, NULL, &sndBuf, 0))
			msg.Format(_T("Fail to transmit file '%s': %d"), filename, ::GetLastError());
		else
			msg.Format(_T("Transmit '%s' done."), filename);
	}
	else
		msg.Format(_T("Fail to connect to Bigobject: %d"), ::GetLastError());

	shutdown(skBo, SD_BOTH);
	closesocket(skBo);
	AfxMessageBox(msg);
}


void CImportBODlg::OnBnClickedBtnExecute()
{
	UpdateData(TRUE);

	CString szErr;
	CDatabase database;
	CString szDriver = L"MySQL ODBC 5.3 ANSI Driver";
	CString szDsn;

	if (0 == m_dwIpAddr || 0 == m_nMySqlPort) {
		AfxMessageBox(_T("Invalid host ip address or port number."));
		return;
	}

	CString szSqlLower = m_szSql;
	szSqlLower.MakeUpper();
	if (0 != szSqlLower.Find(L"INSERT") &&
		0 != szSqlLower.Find(L"CREATE")) {
		AfxMessageBox(L"Support 'CREATE' and 'INSERT' statements only.");
		return;
	}

	struct in_addr host;
	host.S_un.S_addr = htonl(m_dwIpAddr);
	WCHAR wszHost[32] = {0};
	if (0 == MultiByteToWideChar(CP_ACP, 0, inet_ntoa(host), -1, wszHost, sizeof(wszHost)/sizeof(wszHost[0]))) {
		szErr.FormatMessage(_T("Convert to wide-chart fail: %d"), ::GetLastError());
		AfxMessageBox(szErr);
		return;
	}

	szDsn.Format(L"ODBC;DRIVER={%s};SERVER=%s;DATABASE=bigobject;USER=dummy;PASSWORD=dummy;OPTION=3;", szDriver, wszHost);
	TRY {
		if (database.Open(NULL, FALSE, FALSE, szDsn, FALSE)) {
			database.ExecuteSQL(m_szSql);
			database.Close();
			if (0 == szSqlLower.Find(L"INSERT"))
				AfxMessageBox(L"Insert data succeed.");
			else
				AfxMessageBox(L"Create table succeed.");
		}
	}
	CATCH(CDBException, e) {
	   AfxMessageBox(_T("Database error: ") + e->m_strError);
	}
	END_CATCH;
}
