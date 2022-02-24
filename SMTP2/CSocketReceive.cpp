#include "pch.h"
#include "CSocketReceive.h"

//IMPLEMENT_DYNCREATE(CSocketReceive, CWinThread, CAsyncSocket)

BEGIN_MESSAGE_MAP(CSocketReceive, CWinThread)
END_MESSAGE_MAP()

void CSocketReceive::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	__super::OnReceive(nErrorCode);
}
