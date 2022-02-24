#pragma once
#include <afxsock.h>
class CSocketReceive :
    public CAsyncSocket,
    public CWinThread
{
    //DECLARE_DYNCREATE(CSocketReceive)
public:

    DECLARE_MESSAGE_MAP()
    virtual void OnReceive(int nErrorCode);
};

