#include "pch.h"
#include "CSocketMain.h"
#include "CReceiveDialog.h"
#include "CSocketReceive.h"
#include "resource.h"


void CSocketMain::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	CAsyncSocket* pSocket = new CAsyncSocket();
	Accept(*pSocket);
	SOCKET t = pSocket->Detach();
	PostMessage(AfxGetMainWnd()->m_hWnd,WM_MY_RECEIVESOCKET, (WPARAM)t, 0);
	delete pSocket;
	CAsyncSocket::OnAccept(nErrorCode);
}


void CSocketMain::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CAsyncSocket::OnReceive(nErrorCode);
}
