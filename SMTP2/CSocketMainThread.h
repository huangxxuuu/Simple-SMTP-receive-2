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
    CSocketMain socketMain;
    afx_msg LRESULT CSocketMainThread::OnMyQuit(WPARAM wParam, LPARAM lParam);
    DECLARE_MESSAGE_MAP()
};

