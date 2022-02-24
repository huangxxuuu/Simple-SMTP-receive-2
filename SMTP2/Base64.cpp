#include "pch.h"
#include "Base64.h"

int TranBase64(void* buffer, char** out)  //char* ���͵�buffer  ����ֵΪ����ǰ���ֽ���
{
	char* str = (char*)buffer;
	int i = 0;
	bool isok = true;
	while (isok) {  //��base64���ַ�ӳ��ת����ȥ������¼�ַ��������ڷ���ֵ
		/*if (str[0] == 0) {
			int b = 0;
		}*/
		if (isupper(str[i])) {
			str[i] -= 'A';
		}
		else if (islower(str[i])) {
			str[i] -= 'a';
			str[i] += 26;
		}
		else if (isdigit(str[i])) {
			str[i] -= '0';
			str[i] += 52;
		}
		else {
			switch (str[i]) {
			case '+':
				str[i] = 62; break;
			case '/':
				str[i] = 63; break;
			case '=':
				str[i] = 0; break;
			case '\r':
			case '\n':
				str[i] = 0;
			default:
				isok = false;
			}
		}
		++i;
		if (!isok) {
			--i;
		}
	}
	//���ڣ�i=str�ĳ��ȡ���4�ı���
	int j = 0;
	int h = 0;
	char temp = 0;
	while (j < i) {  //��ÿ4���ֽ�ȥ�������λ���ϲ���3���ֽ�
		// �ϲ���ĵ�1���ֽ�
		str[h] = str[j++] << 2;
		temp = str[j] >> 4;
		str[h++] |= temp;
		// �ϲ���ĵ�2���ֽ�
		str[h] = str[j++] << 4;
		temp = str[j] >> 2;
		str[h++] |= temp;
		// �ϲ���ĵ�3���ֽ�
		str[h] = str[j++] << 6;
		str[h++] |= str[j++];
	}
	str[h] = 0; //�ڽ������ַ������β����'\0'
	*out = str;
	return i;
}

int enter(std::string &str, int i) { //����ֱ��\r\n�����������ж��ٸ��ַ�
	//int i = 0;
	while (i < str.size() && str[i] != '\r' && str[i] != '\n') {
		i++;
	}
	if (i == str.size()) {
		return i;
	}
	i = i + 2; //��Ϊ�����ж���\r\n��β������ֱ��+2����ʾ\r\n��Ӧ�ĳ���
	return i;
}

int picenter(std::string &str,size_t &start) {
	int i, j;
	i = j = start;
	int n = str.size();
	for (; i < n && str[i] != '-'; i++) {
		if (str[i] != '\r' && str[i] != '\n') {
			str[j] = str[i];
			j++;
		}
	}
	str[j] = 0;
	start = j;
	return i;
}