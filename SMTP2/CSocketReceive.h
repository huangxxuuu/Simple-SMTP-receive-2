#pragma once
#include <afxsock.h>
#include <fstream>
#include <string>
#include <vector>
constexpr auto BUFFERSIZE = 1024;  // smtp报文行不超过78个字符
constexpr auto FILENAMESIZE = 256;
class CSocketReceive :
    public CAsyncSocket
{
    //DECLARE_DYNCREATE(CSocketReceive)
public:
    virtual void OnReceive(int nErrorCode);
	char buffer[BUFFERSIZE];//用于从tcp输入流中获取字符
	CString wbuffer;// 用来把收到的输入流字符转化成unicode
	std::string datafile; // 用来缓存接收的SMTP报文数据。

	int state;	//表示SMTP当前状态
				//0 表示命令交互模式
				//1 表示接收DATA报文段并处理			
	std::string filename;	//表示保存邮件报文的文件名
	bool binfile;			//表示是否处于二进制文件接收模式，Content-Type: image或Content-Type: application
	bool base64;		//记录遇到Content-Transfer-Encoding: base64，准备解码
	bool encode;		//base64为真后，遇到的第一个空行，开始解码
	std::ofstream picture;
	std::string picstr;
	//virtual void OnClose(int nErrorCode);
	CWnd* pRDlg;
	DWORD threadID;
	int ParseMail();
	int datafileCount;
	int AddDatafilecount();
	std::string content;
//	std::vector<std::string> filenames;
};

