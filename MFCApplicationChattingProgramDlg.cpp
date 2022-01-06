
// MFCApplicationChattingProgramDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCApplicationChattingProgram.h"
#include "MFCApplicationChattingProgramDlg.h"
#include "afxdialogex.h"

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


// CMFCApplicationChattingProgramDlg dialog



CMFCApplicationChattingProgramDlg::CMFCApplicationChattingProgramDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATIONCHATTINGPROGRAM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplicationChattingProgramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplicationChattingProgramDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Send, &CMFCApplicationChattingProgramDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_Close, &CMFCApplicationChattingProgramDlg::OnBnClickedButtonClose)
	ON_EN_CHANGE(IDC_EDIT_Send, &CMFCApplicationChattingProgramDlg::OnEnChangeEditSend)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCApplicationChattingProgramDlg::OnEnChangeEditReceive)
END_MESSAGE_MAP()


// CMFCApplicationChattingProgramDlg message handlers

BOOL CMFCApplicationChattingProgramDlg::OnInitDialog()
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
	m_UDPserver.createUDPServerSocket(9000, this);
	m_UDPserver.beginReceiving();

	m_UDPclient.createUDPClientSocket(9001);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplicationChattingProgramDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplicationChattingProgramDlg::OnPaint()
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
HCURSOR CMFCApplicationChattingProgramDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCApplicationChattingProgramDlg::OnBnClickedButtonSend()
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItemText(IDC_EDIT_Send, str);
	m_UDPclient.send(str);
}


void CMFCApplicationChattingProgramDlg::OnBnClickedButtonClose()
{
	// TODO: Add your control notification handler code here
	m_UDPserver._CloseSocket();
	m_UDPclient._CloseSocket();
	CDialogEx::OnOK();
}


LRESULT CMFCApplicationChattingProgramDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	if (message == WM_MY_MESSAGE)
	{
		CString* strMessage = reinterpret_cast<CString*>(wParam);
		SetDlgItemText(IDC_EDIT2, *strMessage);

		/*PacketD* pPacketD = reinterpret_cast<PacketD*>(wParam);
		PacketD p = *pPacketD;
		
		CString str;
		str.Format(_T("%f %d %d"), p.data, p.packetNo, p.length);
		SetDlgItemText(IDC_EDIT2, str);*/
	}

	return CDialogEx::WindowProc(message, wParam, lParam);
}


void CMFCApplicationChattingProgramDlg::OnEnChangeEditSend()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CMFCApplicationChattingProgramDlg::OnEnChangeEditReceive()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
