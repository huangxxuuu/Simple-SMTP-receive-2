#pragma once
#include <ctype.h>
#include <string>

int TranBase64(void* buffer, char** out);  //char* 类型的buffer  返回值为解码前的字节数

int enter(std::string &str, int i); //计算直到\r\n（包括）共有多少个字符

int picenter(std::string &str, size_t&start);  // 跳过/r/n字符，只保留base64本身的字符，将结束位置设为0。返回跳过之前的长度

