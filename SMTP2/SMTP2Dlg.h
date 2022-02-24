﻿
// SMTP2Dlg.h: 头文件
//

#pragma once
#include "CSocketMainThread.h"

// CSMTP2Dlg 对话框
class CSMTP2Dlg : public CDialogEx
{
// 构造
public:
	CSMTP2Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SMTP2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_ip;
	int m_port;
//	afx_msg void OnBnClickedOk();
//	afx_msg void OnBnClickedCancel();
	CStatic m_ready;
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedClose();
	CSocketMainThread* pSocketMainThread;
protected:
	afx_msg LRESULT OnMyReceivesocket(WPARAM wParam, LPARAM lParam);
};
