#pragma once
#include <afxsock.h>
#include <fstream>
#include <string>
#include <vector>
constexpr auto BUFFERSIZE = 1024;  // smtp�����в�����78���ַ�
constexpr auto FILENAMESIZE = 256;
class CSocketReceive :
    public CAsyncSocket
{
    //DECLARE_DYNCREATE(CSocketReceive)
public:
    virtual void OnReceive(int nErrorCode);
	char buffer[BUFFERSIZE];//���ڴ�tcp�������л�ȡ�ַ�
	CString wbuffer;// �������յ����������ַ�ת����unicode
	std::string datafile; // ����������յ�SMTP�������ݡ�

	int state;	//��ʾSMTP��ǰ״̬
				//0 ��ʾ�����ģʽ
				//1 ��ʾ����DATA���Ķβ�����			
	std::string filename;	//��ʾ�����ʼ����ĵ��ļ���
	bool binfile;			//��ʾ�Ƿ��ڶ������ļ�����ģʽ��Content-Type: image��Content-Type: application
	bool base64;		//��¼����Content-Transfer-Encoding: base64��׼������
	bool encode;		//base64Ϊ��������ĵ�һ�����У���ʼ����
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

