#include "stringcov.h"
#define CP_GBK (936) 
void GBK_to_UTF8(const char* in, size_t len, std::string& out)
{
	int wbufferlen = (int)::MultiByteToWideChar(CP_GBK, MB_PRECOMPOSED, in, (int)len, NULL, 0);
	wchar_t* pwbuffer = new wchar_t[wbufferlen + 4];
	if (NULL == pwbuffer)
	{
		return;
	}
	wbufferlen = (int)::MultiByteToWideChar(CP_GBK, MB_PRECOMPOSED, in, (int)len, pwbuffer, wbufferlen + 2);
	//wchar_t -> UTF8
	int bufferlen = ::WideCharToMultiByte(CP_UTF8, 0, pwbuffer, wbufferlen, NULL, 0, NULL, NULL);
	char* pBuffer = new char[bufferlen + 4];
	if (NULL == pBuffer)
	{
		delete[] pwbuffer;
		return;
	}
	int out_len = ::WideCharToMultiByte(CP_UTF8, 0, pwbuffer, wbufferlen, pBuffer, bufferlen + 2, NULL, NULL);
	pBuffer[bufferlen] = '\0';
	out.assign(pBuffer, out_len);
	delete[] pwbuffer;
	delete[] pBuffer;
	return;
}
void UTF8_to_GBK(const char* in, size_t len, std::string& out)
{

	//1) UTF-8 -> whcar_t
	int wbufferlen = (int)::MultiByteToWideChar(CP_UTF8, 0, in, (int)len, NULL, 0);    //may cause error
	wchar_t* pwbuffer = new wchar_t[wbufferlen + 4];
	if (NULL == pwbuffer)
	{
		return;
	}
	wbufferlen = (int)::MultiByteToWideChar(CP_UTF8, 0, in, (int)len, pwbuffer, wbufferlen + 2);
	//2) wchar_t -> GBK
	int bufferlen = (int)::WideCharToMultiByte(CP_GBK, 0, pwbuffer, wbufferlen, NULL, 0, NULL, NULL);
	char* pBuffer = new char[bufferlen + 4];
	if (NULL == pBuffer)
	{
		delete[] pwbuffer;
		return;
	}
	int out_len = ::WideCharToMultiByte(CP_GBK, 0, pwbuffer, wbufferlen, pBuffer, bufferlen + 2, NULL, NULL);
	pBuffer[bufferlen] = '\0';
	out.assign(pBuffer, out_len);
	delete[] pwbuffer;
	delete[] pBuffer;

	return;
}
// Unicode ×ª»»UTF8

void Unicode_to_UTF8(const wchar_t* in, size_t len, std::string& out)
{
	size_t out_len = len * 3 + 1;
	char* pBuf = new char[out_len];
	if (NULL == pBuf)
	{
		return;
	}
	char* pResult = pBuf;
	memset(pBuf, 0, out_len);

	out_len = ::WideCharToMultiByte(CP_UTF8, 0, in, len, pBuf, len * 3, NULL, NULL);
	out.assign(pResult, out_len);
	delete[] pResult;
	pResult = NULL;
	return;
}



// utf8 ×ª»»Unicode

void UTF8_to_Unicode(const char* in, size_t len, std::wstring& out)
{
	wchar_t* pBuf = new wchar_t[len + 1];
	if (NULL == pBuf)
	{
		return;
	}
	size_t out_len = (len + 1) * sizeof(wchar_t);
	memset(pBuf, 0, (len + 1) * sizeof(wchar_t));
	wchar_t* pResult = pBuf;

	out_len = ::MultiByteToWideChar(CP_UTF8, 0, in, len, pBuf, len * sizeof(wchar_t));
	out.assign(pResult, out_len);
	delete[] pResult;
	pResult = NULL;
}