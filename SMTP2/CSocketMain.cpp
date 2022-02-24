#include "pch.h"
#include "CSocketMain.h"


void CSocketMain::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CAsyncSocket::OnAccept(nErrorCode);
}
