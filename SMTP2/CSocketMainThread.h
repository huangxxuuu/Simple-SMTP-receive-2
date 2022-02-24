#pragma once
#include <afxwin.h>
#include "CSocketMain.h"
class CSocketMainThread :
    public CWinThread
{
    DECLARE_DYNCREATE(CSocketMainThread)
public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
    virtual int Run();
    virtual BOOL OnIdle(LONG lCount);
    DECLARE_MESSAGE_MAP()
    CSocketMain socketMain;
};

