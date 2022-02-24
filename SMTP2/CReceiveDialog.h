#pragma once
#include "afxdialogex.h"


// CReceiveDialog 对话框

class CReceiveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReceiveDlg)

public:
	CReceiveDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CReceiveDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RECEIVE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 客户端服务器命令交互日志
	CListBox m_listLog;
	// 邮件报内容
	CEdit m_editMail;
	// 邮件正文内容
	CEdit m_editText;
	// 邮件附件列表
	CListBox m_listAttachment;
	// 显示图片的区域
	CStatic m_rectShowPic;
	afx_msg void OnBnClickedButtonShowpic();
	// 将要绘制的图片名称
	CString picname;
	CRect picrect;
	afx_msg void OnPaint();
};
