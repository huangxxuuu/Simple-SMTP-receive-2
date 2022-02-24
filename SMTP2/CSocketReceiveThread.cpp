#include "pch.h"
#include "CSocketReceiveThread.h"
#include "resource.h"

IMPLEMENT_DYNCREATE(CSocketReceiveThread, CWinThread)

BEGIN_MESSAGE_MAP(CSocketReceiveThread, CWinThread)
	ON_MESSAGE(WM_MY_PARSEMAIL, (LRESULT(__cdecl CWnd::*)(WPARAM, LPARAM))& CSocketReceiveThread::OnMyParsemail)
END_MESSAGE_MAP()


BOOL CSocketReceiveThread::InitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
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
	// TODO: �ڴ����ר�ô����/����û���

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
	// TODO: �ڴ����ר�ô����/����û���
	return CWinThread::ExitInstance();
}
