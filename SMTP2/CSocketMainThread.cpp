#include "pch.h"
#include "CSocketMainThread.h"
#include "SMTP2.h"
#include "SMTP2Dlg.h"

IMPLEMENT_DYNCREATE(CSocketMainThread, CWinThread)

BEGIN_MESSAGE_MAP(CSocketMainThread, CWinThread)
END_MESSAGE_MAP()


BOOL CSocketMainThread::InitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	m_bAutoDelete = true;
	HANDLE a = m_hThread; // ��ǰ�̵߳ľ��
	DWORD b  = m_nThreadID; // ��ǰ�̵߳�ID
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
	// TODO: �ڴ����ר�ô����/����û���
	//int a = 1;
	socketMain.Close();
	return CWinThread::ExitInstance();
}


int CSocketMainThread::Run()
{
	// TODO: �ڴ����ר�ô����/����û���

	return CWinThread::Run();
}


BOOL CSocketMainThread::OnIdle(LONG lCount)
{
	// TODO: �ڴ����ר�ô����/����û���
	//int a;
	//a = 5;
	//CWinThread::OnIdle(lCount)
	return CWinThread::OnIdle(lCount);
}
