
// MFCApplicationChattingProgramDlg.h : header file
//
#include "CTCPSocketcomm.h"
#include "Socket.h"
#pragma once


// CMFCApplicationChattingProgramDlg dialog
class CMFCApplicationChattingProgramDlg : public CDialogEx
{
// Construction
public:
	CMFCApplicationChattingProgramDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATIONCHATTINGPROGRAM_DIALOG };
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
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonClose();
private:
	CTCPSocketcomm m_server;
	CTCPSocketcomm m_client;
	CSocket m_UDPserver;
	CSocket m_UDPclient;
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnEnChangeEditSend();
	afx_msg void OnEnChangeEditReceive();
};
