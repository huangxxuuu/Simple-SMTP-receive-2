#pragma once
#include <afxwin.h>
#include "CSocketMain.h"
//#define WM_MYMESSAGE  (WM_USER + 1)
class CSocketMainThread :
    public CWinThread
{
    DECLARE_DYNCREATE(CSocketMainThread)
public:
    //afx_msg LRESULT OnThreadMessage(LPARAM lparam, WPARAM wparam);
    virtual BOOL InitInstance();
    virtual int ExitInstance();
    virtual int Run();
    virtual BOOL OnIdle(LONG lCount);
    DECLARE_MESSAGE_MAP()
    CSocketMain socketMain;
};

