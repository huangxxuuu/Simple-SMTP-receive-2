#include "pch.h"
#include "Base64.h"

int TranBase64(void* buffer, char** out)  //char* 类型的buffer  返回值为解码前的字节数
{
	char* str = (char*)buffer;
	int i = 0;
	bool isok = true;
	while (isok) {  //将base64的字符映射转换回去，并记录字符长度用于返回值
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
	//现在，i=str的长度。是4的倍数
	int j = 0;
	int h = 0;
	char temp = 0;
	while (j < i) {  //将每4个字节去掉最高两位，合并成3个字节
		// 合并后的第1个字节
		str[h] = str[j++] << 2;
		temp = str[j] >> 4;
		str[h++] |= temp;
		// 合并后的第2个字节
		str[h] = str[j++] << 4;
		temp = str[j] >> 2;
		str[h++] |= temp;
		// 合并后的第3个字节
		str[h] = str[j++] << 6;
		str[h++] |= str[j++];
	}
	str[h] = 0; //在解码后的字符数组结尾加上'\0'
	*out = str;
	return i;
}

int enter(std::string &str, int i) { //计算直到\r\n（包括）共有多少个字符
	//int i = 0;
	while (i < str.size() && str[i] != '\r' && str[i] != '\n') {
		i++;
	}
	if (i == str.size()) {
		return i;
	}
	i = i + 2; //因为报文行都以\r\n结尾，所以直接+2，表示\r\n对应的长度
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