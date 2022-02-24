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
    CWnd* dlg;
    afx_msg LRESULT CSocketReceiveThread::OnMyQuit(WPARAM wParam, LPARAM lParam);
    virtual int ExitInstance();
    DECLARE_MESSAGE_MAP()
};

