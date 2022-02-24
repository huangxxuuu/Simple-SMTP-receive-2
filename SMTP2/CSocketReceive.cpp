#include "pch.h"
#include "CSocketReceive.h"
#include "CReceiveDialog.h"
#include "Base64.h"
#include <ctime>
#include <string>
#include "resource.h"

inline bool check(std::string& s, int start, char *str) {
	if (start < 0 || strlen(str) + start > s.size()) {
		return false;
	}
	size_t n = strlen(str);
	size_t i = 0;
	while (i < n) {
		if (s[start + i] != str[i]) {
			return false;
		}
		++i;
	}
	return true;
}

void CSocketReceive::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	memset(buffer, 0, BUFFERSIZE * sizeof(char));
	if (state == 0) {
		Receive(buffer, BUFFERSIZE);
		wbuffer.Format(_T("%S"), buffer);
		std::string ret;
		if (wbuffer.Left(4) == L"EHLO" || wbuffer.Left(4) == L"HELO") {
			ret = "250 OK\r\n";
		}
		else if (wbuffer.Left(9) == L"MAIL FROM") {
			ret = "250 OK\r\n";
		}
		else if (wbuffer.Left(7) == L"RCPT TO") {
			ret = "250 OK\r\n";
		}
		else if (wbuffer.Left(4) == L"DATA") {
			ret = "354 Start mail input\r\n";
			datafile.clear();
			state = 1;
		}
		else if (wbuffer.Left(4) == L"QUIT") {
			ret = "221 CLOSE\r\n";
		}
		else {   //ʹ��if else�����Ϊ�˵�û��ƥ�������ʱ�򣬻ظ�500�﷨����
			ret = "500 Syntax error\r\n";
		}
		((CReceiveDlg*)pRDlg)->m_listLog.InsertString(-1, L"C:"+wbuffer);
		Send(ret.c_str(), ret.size());
		wbuffer.Format(_T("S:%S"), ret.c_str());
		((CReceiveDlg*)pRDlg)->m_listLog.InsertString(-1, L""+wbuffer);
		PostMessage(pRDlg->m_hWnd, WM_MY_PROCESSMAIL, 0, 0);
	}
	else {
		int n = Receive(buffer, BUFFERSIZE);
		datafile.append(buffer, 0, n);
		if (check(datafile, datafile.size()-5, "\r\n.\r\n")) {
			/*time_t t = time(NULL);
			filename = std::to_string(t) + "+" + std::to_string(threadID);
			std::ofstream out(filename, std::ios::binary);
			out.write(datafile.c_str(), datafile.size());
			out.close();
			datafile.clear();
			datafile.shrink_to_fit();*/
			Send("250 OK\r\n", 8);
			((CReceiveDlg*)pRDlg)->m_listLog.InsertString(-1, L"S:250 OK\r\n");
			PostMessage(pRDlg->m_hWnd, WM_MY_PROCESSMAIL, (WPARAM)threadID, (LPARAM) & datafile);
			state = 0;
		}
	}

	__super::OnReceive(nErrorCode);
}


int CSocketReceive::ParseMail()
{
	// TODO: �ڴ˴����ʵ�ִ���.
	size_t i = 0;
	size_t len = datafile.size()-5; // ������β��\r\n.\r\n
	size_t j = 0;
	while (i < len) {
		j = enter(datafile, i);
		if (check(datafile, i, "Content-Type: image") || check(datafile, i, "Content-Type: application")) {
			binfile = true; // �ж��Ƿ������ն������ļ���ģʽ
		}
		if (binfile) { // ��ȡ�ļ���
			if (check(datafile, i, "\tname=\"")) {
				filename.clear();
				for (int temp = i + 7; datafile[temp] != '"'; temp++) {
					filename.push_back(datafile[temp]);
				}
				wbuffer.Format(_T("%S"), filename.c_str());
				((CReceiveDlg*)pRDlg)->m_listAttachment.InsertString(-1, L"" + wbuffer);
			}
		}
		if (base64) { // ���н���Ĳ���
			if (encode) { // ���ڽ���
				if (check(datafile, i, "--")) {  //���"--"����ν���������Ϊ���������־
					if (!binfile) { // �����ı��ĵĴ���
						content += "\r\n";
						char* a = (char*)content.c_str();
						char* s;
						int len = TranBase64(a, &s);
						wbuffer.Format(_T("S:%S"), content.c_str());
						((CReceiveDlg*)pRDlg)->m_editText = s;
						content.clear();
						content.shrink_to_fit();
					}
					else {
						picstr += "\r\n";
						char* a = (char*)picstr.c_str();
						char* s;
						size_t len = TranBase64(a, &s);
						picture.open(filename, std::ios::binary | std::ios::out | std::ios::trunc);
						picture.write(a, len / 4 * 3);
						picture.close();
						picstr.clear();
						picstr.shrink_to_fit();
						wbuffer.Format(_T("S:%S"), filename.c_str());
						((CReceiveDlg*)pRDlg)->m_listLog.InsertString(-1, wbuffer);
						filename.clear();
					}
					base64 = false;
					encode = false;
					binfile = false;
				}
				else {
					size_t start = i;
					j = picenter(datafile, i);  // [i,j)
					if (binfile) {	//���ڶ��������͵Ĵ���
						picstr = datafile.substr(start, i - start);
					}
					else {			//����text���͵Ĵ���
						content = datafile.substr(start, i - start);
					}
				}
			}
			else { // �жϽ��뿪ʼ�Ŀ���
				if (check(datafile, i, "\r\n")) {
					encode = true;
				}
			}
		}
		else {  // �ж��Ƿ���Ҫ����
			if (check(datafile, i, "Content-Transfer-Encoding: base64")) {
				base64 = true;
			}
		}
		i = j;
	}
	PostMessage(pRDlg->m_hWnd, WM_MY_PROCESSMAIL, 0, 0);
	AddDatafilecount();
	AfxEndThread(0);
	return 0;
}


int CSocketReceive::AddDatafilecount()
{
	// TODO: �ڴ˴����ʵ�ִ���.
	++datafileCount;
	if (datafileCount == 2) {
		datafile.clear();
		datafile.shrink_to_fit();
	}
	return 0;
}
