#include "pch.h"
#include "CSocketReceive.h"

//IMPLEMENT_DYNCREATE(CSocketReceive, CWinThread, CAsyncSocket)

BEGIN_MESSAGE_MAP(CSocketReceive, CWinThread)
END_MESSAGE_MAP()

void CSocketReceive::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	__super::OnReceive(nErrorCode);
}
