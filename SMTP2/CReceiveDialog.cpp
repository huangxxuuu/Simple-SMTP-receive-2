// CReceiveDialog.cpp: 实现文件
//

#include "pch.h"
#include "SMTP2.h"
#include "afxdialogex.h"
#include "CReceiveDialog.h"
#include <string>
#include <vector>


// CReceiveDialog 对话框

IMPLEMENT_DYNAMIC(CReceiveDlg, CDialogEx)

CReceiveDlg::CReceiveDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RECEIVE_DIALOG, pParent)
{
	//m_rectShowPic.GetWindowRect(&picrect);
	//ScreenToClient(&picrect);
	pThread = 0;
}

CReceiveDlg::~CReceiveDlg()
{
}

void CReceiveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LOG, m_listLog);
	DDX_Text(pDX, IDC_EDIT_MAIL, m_editMail);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_editText);
	DDX_Control(pDX, IDC_LIST_ATTACHMENT, m_listAttachment);
	DDX_Control(pDX, IDC_RECT_SHOWPIC, m_rectShowPic);
}


BEGIN_MESSAGE_MAP(CReceiveDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SHOWPIC, &CReceiveDlg::OnBnClickedButtonShowpic)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_MY_PROCESSMAIL, &CReceiveDlg::OnMyProcessmail)
END_MESSAGE_MAP()


// CReceiveDialog 消息处理程序


void CReceiveDlg::OnBnClickedButtonShowpic()
{
	// TODO: 在此添加控件通知处理程序代码
	// 附件数量为0
	if (m_listAttachment.GetCount() == 0) {
		picname = L"";
		return;
	}
	// 没有选中文件
	if (m_listAttachment.GetCurSel() == LB_ERR) {
		picname = L"";
		return;
	}
	// 获取文件名
	m_listAttachment.GetText(m_listAttachment.GetCurSel(), picname);
	// 重绘图片区域
	m_rectShowPic.GetWindowRect(&picrect);
	ScreenToClient(&picrect);
	InvalidateRect(picrect);

}


void CReceiveDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CString s = picname;
	s.MakeLower(); // 有些文件的后缀可能是大写的
	if (s.GetLength() > 0) {
		if (s.Right(4) != L".jpg" && s.Right(4) != L".bmp" && s.Right(4) != L".png") {
			MessageBox(L"非图片类型");
			return;
		}
		CImage image;
		image.Load(s);
		if (image.IsNull()) {
			MessageBox(L"图片加载失败");
			return;
		}
		HDC hdc = dc.GetSafeHdc();
		SetStretchBltMode(hdc, COLORONCOLOR);
		image.Draw(hdc, picrect);
	}
}


void CReceiveDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码

}


void CReceiveDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 释放占用的空间
	m_editMail.Empty();
	m_editMail.FreeExtra();
	m_editText.Empty();
	m_editText.FreeExtra();
	pThread->ResumeThread();
	CDialogEx::OnClose();
}


afx_msg LRESULT CReceiveDlg::OnMyProcessmail(WPARAM wParam, LPARAM lParam)
{
	if (wParam != 0) {  // 进程ID
		std::string* mail = (std::string*)lParam;
		m_editMail.Format(_T("%S"),(mail->c_str()));
		PostThreadMessage(wParam, WM_MY_PARSEMAIL, 1, 0);
	}
	UpdateData(false);
	return 0;
}
