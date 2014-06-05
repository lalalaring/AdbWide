#include "common.h"
#include <string>
#include <Windows.h>
#include <vector>
#include <iostream>
#include <ctime>
#include <ShlObj.h>
#include <Shellapi.h>
#include <algorithm>
#include <vector>
#include <fstream>


#pragma comment(lib, "Shell32.lib")


std::wstring a2w(const std::string& str)
{
	int size = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, 0, 0);
	FastBuffer<wchar_t> ch(size); 
	if (!MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, ch._buf, size)) {
		return L"";
	}
	return std::wstring(ch._buf);
}

std::string w2a(const std::wstring& str)
{
	int size = WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, 0, 0, 0, 0);
	FastBuffer<char> ch(size); 
	if (!WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, ch._buf, size, 0, 0)) {
		return "";
	}
	return std::string(ch._buf);
}

int Utf8Ascii(char* utf8, int utf8_len, char* ascii, int len)
{
    FastBuffer<wchar_t> tmp(utf8_len);
    int _len = MultiByteToWideChar(CP_UTF8, 0, utf8, utf8_len, tmp._buf, utf8_len);
    return WideCharToMultiByte(CP_ACP, 0, tmp._buf, _len, ascii, len, nullptr, nullptr);
}

std::string utf82ascii(const std::wstring& utf8)
{
	int utf8_size = utf8.length() * sizeof(wchar_t);
	FastBuffer<char> utf8_buf(utf8_size);
	memcpy(utf8_buf._buf, utf8.c_str(), utf8_size);
    FastBuffer<wchar_t> tmp(utf8.length());
    int _len = MultiByteToWideChar(CP_UTF8, 0, (LPCCH)utf8.c_str(), utf8_size, tmp._buf, utf8_size);
	FastBuffer<char> ascii(_len);
    WideCharToMultiByte(CP_ACP, 0, tmp._buf, -1, ascii.buf, _len, nullptr, nullptr);
	return std::string(ascii._buf);
}

std::wstring ascii2utf8(const std::string& ascii)
{
	int size = MultiByteToWideChar(CP_UTF8, 0, ascii.c_str(), -1, 0, 0);
	FastBuffer<wchar_t> ch(size); 
	if (!MultiByteToWideChar(CP_UTF8, 0, ascii.c_str(), -1, ch._buf, size)) 
	{
		return L"";
	}
	return std::wstring(ch._buf);
}

std::string unicode2utf8(const std::wstring& ustr)
{
    int ulen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)ustr.c_str(), -1, NULL, 0, NULL, NULL);
	FastBuffer<char> ch(ulen);
	::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)ustr.c_str(), -1, ch._buf, ulen, NULL, NULL);
    return std::string(ch._buf);
}
