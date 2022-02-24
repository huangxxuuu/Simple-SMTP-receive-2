
// SMTP2Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "SMTP2.h"
#include "SMTP2Dlg.h"
#include "afxdialogex.h"
#include "CSocketReceiveThread.h"
#include "CReceiveDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CSMTP2Dlg 对话框



CSMTP2Dlg::CSMTP2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SMTP2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_ip = _T("");
	m_port = 0;
}

void CSMTP2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_IP, m_ip);
	DDX_Text(pDX, IDC_PORT, m_port);
	DDX_Control(pDX, IDC_READY, m_ready);
}

BEGIN_MESSAGE_MAP(CSMTP2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, &CSMTP2Dlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_CLOSE, &CSMTP2Dlg::OnBnClickedClose)
	ON_MESSAGE(WM_MY_RECEIVESOCKET, &CSMTP2Dlg::OnMyReceivesocket)
END_MESSAGE_MAP()


// CSMTP2Dlg 消息处理程序

BOOL CSMTP2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	// 获取本机IP地址
	char hostName[100];
	gethostname(hostName, sizeof(hostName));
	hostent* hn = gethostbyname(hostName);
	m_ip = inet_ntoa(*(in_addr*)hn->h_addr);
	// 设置端口号
	m_port = 25;
	UpdateData(false);
	// 隐藏服务器正在监听字段，对应还没开始监听
	m_ready.ShowWindow(SW_HIDE);
	// 创建服务器端监听套接字线程,在点击开始之后

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSMTP2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSMTP2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSMTP2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSMTP2Dlg::OnBnClickedOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	pSocketMainThread = new CSocketMainThread();
	//pSocketMainThread->socketMain.Create();
	pSocketMainThread->CreateThread();
	m_ready.ShowWindow(SW_SHOW);
}


void CSMTP2Dlg::OnBnClickedClose()
{
	// TODO: 在此添加控件通知处理程序代码
	pSocketMainThread->PostThreadMessageW(WM_QUIT, 0, 0);
	m_ready.ShowWindow(SW_HIDE);
}


afx_msg LRESULT CSMTP2Dlg::OnMyReceivesocket(WPARAM wParam, LPARAM lParam)
{
	// 传入的wParam是套接字句柄
	CSocketReceiveThread* pRThread = new CSocketReceiveThread();
	CReceiveDlg* pRDlg = new CReceiveDlg();
	pRDlg->Create(IDD_RECEIVE_DIALOG);
	pRDlg->ShowWindow(SW_SHOW);
	pRDlg->pThread = pRThread;
	//pRThread->m_pMainWnd = this;
	pRThread->dlg = pRDlg;
	pRThread->handSocket = wParam;
	pRThread->CreateThread();
	return 0;
}
