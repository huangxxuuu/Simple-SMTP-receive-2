#include "pch.h"
#include "CSocketReceiveThread.h"
#include "resource.h"

IMPLEMENT_DYNCREATE(CSocketReceiveThread, CWinThread)

BEGIN_MESSAGE_MAP(CSocketReceiveThread, CWinThread)
	ON_MESSAGE(WM_MY_PARSEMAIL, (LRESULT(__cdecl CWnd::*)(WPARAM, LPARAM))& CSocketReceiveThread::OnMyParsemail)
END_MESSAGE_MAP()


BOOL CSocketReceiveThread::InitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	//bool c = AfxSocketInit();
	socket.Attach(handSocket);
	socket.datafileCount = 0;
	socket.pRDlg = dlg;
	socket.threadID = this->m_nThreadID;
	char* s = "220 SMTPServer is ready\r\n";
	socket.Send(s, strlen(s));
	return true;
}


int CSocketReceiveThread::Run()
{
	// TODO: 在此添加专用代码和/或调用基类

	return CWinThread::Run();
}

afx_msg LRESULT CSocketReceiveThread::OnMyParsemail(WPARAM wParam, LPARAM lParam)
{
	socket.AddDatafilecount();
	socket.ParseMail();
	return 0;
}

int CSocketReceiveThread::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	return CWinThread::ExitInstance();
}
