#pragma once
#include <string>
#include <vector>
#include "commondef.h"

std::wstring a2w(const std::string& str);
std::string w2a(const std::wstring& str);
int Utf8Ascii(char* utf8, int utf8_len, char* ascii, int len);
std::string utf82ascii(const std::wstring& utf8);
std::wstring ascii2utf8(const std::string& ascii);
std::string unicode2utf8(const std::wstring& ustr);
