#pragma once
#include <ctype.h>
#include <string>

int TranBase64(void* buffer, char** out);  //char* ���͵�buffer  ����ֵΪ����ǰ���ֽ���

int enter(std::string &str, int i); //����ֱ��\r\n�����������ж��ٸ��ַ�

int picenter(std::string &str, size_t&start);  // ����/r/n�ַ���ֻ����base64������ַ���������λ����Ϊ0����������֮ǰ�ĳ���

