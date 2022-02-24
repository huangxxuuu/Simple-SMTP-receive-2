#pragma once
class CSocketMain :
    public CAsyncSocket
{
public:
    virtual void OnAccept(int nErrorCode);
};

