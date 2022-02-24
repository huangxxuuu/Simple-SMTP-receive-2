#pragma once
#include <afxwin.h>
#include "CSocketReceive.h"
class CSocketReceiveThread :
    public CWinThread
{
    DECLARE_DYNCREATE(CSocketReceiveThread)
protected:
    afx_msg LRESULT OnMyParsemail(WPARAM wParam, LPARAM lParam);
public:

    virtual BOOL InitInstance();
    CSocketReceive socket;
    SOCKET handSocket;
    virtual int Run();
    CWnd* dlg;

    DECLARE_MESSAGE_MAP()
    virtual int ExitInstance();
};

