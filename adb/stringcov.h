#include <string>
#include <windows.h>
void GBK_to_UTF8(const char* in, size_t len, std::string& out);
void UTF8_to_GBK(const char* in, size_t len, std::string& out);
void Unicode_to_UTF8(const wchar_t* in, size_t len, std::string& out);
void UTF8_to_Unicode(const char* in, size_t len, std::wstring& out);