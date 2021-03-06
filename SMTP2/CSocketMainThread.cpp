#include "pch.h"
#include "CSocketMainThread.h"
#include "SMTP2.h"
#include "SMTP2Dlg.h"

IMPLEMENT_DYNCREATE(CSocketMainThread, CWinThread)

BEGIN_MESSAGE_MAP(CSocketMainThread, CWinThread)
	ON_MESSAGE(WM_MY_QUITHREAD, (LRESULT(__cdecl CWnd::*)(WPARAM, LPARAM))&CSocketMainThread::OnMyQuit)
END_MESSAGE_MAP()


BOOL CSocketMainThread::InitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_bAutoDelete = true;
	HANDLE a = m_hThread; // 当前线程的句柄
	DWORD b  = m_nThreadID; // 当前线程的ID
	CWnd* c  = m_pActiveWnd; // 
	CWnd* d = m_pMainWnd; // 
	CSMTP2App* pWinApp = (CSMTP2App*)AfxGetApp();
	socketMain.Create(((CSMTP2Dlg*)(pWinApp->m_pMainWnd))->m_port, SOCK_STREAM);
	socketMain.Listen();

	//return CWinThread::InitInstance();
	return true;
}


int CSocketMainThread::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	socketMain.Close();
	return CWinThread::ExitInstance();
}


afx_msg LRESULT CSocketMainThread::OnMyQuit(WPARAM wParam, LPARAM lParam) {
	PostQuitMessage(0);
	return 0;
}