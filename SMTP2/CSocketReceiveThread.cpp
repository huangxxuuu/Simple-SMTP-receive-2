#include "pch.h"
#include "CSocketReceiveThread.h"
#include "resource.h"

IMPLEMENT_DYNCREATE(CSocketReceiveThread, CWinThread)

BEGIN_MESSAGE_MAP(CSocketReceiveThread, CWinThread)
	ON_MESSAGE(WM_MY_PARSEMAIL, (LRESULT(__cdecl CWnd::*)(WPARAM, LPARAM))& CSocketReceiveThread::OnMyParsemail)
	ON_MESSAGE(WM_MY_QUITHREAD, (LRESULT(__cdecl CWnd::*)(WPARAM, LPARAM))& CSocketReceiveThread::OnMyQuit)
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

afx_msg LRESULT CSocketReceiveThread::OnMyParsemail(WPARAM wParam, LPARAM lParam)
{
	socket.AddDatafilecount();
	socket.ParseMail();
	PostQuitMessage(0);
	return 0;
}

int CSocketReceiveThread::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类

	socket.outfileCache.clear();
	socket.outfileCache.shrink_to_fit();
	socket.datafile.clear();
	socket.datafile.shrink_to_fit();
	socket.content.clear();
	socket.content.shrink_to_fit();
	socket.wbuffer.Empty();
	socket.wbuffer.FreeExtra();
	if (socket.outfileStream.is_open()) {
		socket.outfileStream.close();
	}
	return CWinThread::ExitInstance();
}

afx_msg LRESULT CSocketReceiveThread::OnMyQuit(WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
	return 0;
}
