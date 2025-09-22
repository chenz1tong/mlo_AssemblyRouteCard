#include <windows.h>
#include <string>
#include "CADControl_global.h"
#include <xlocbuf>
#include <iostream>
#include <locale>
#include <codecvt>
using namespace std;
class CADCONTROL_EXPORT FormatHandle
{
public:
	static std::string StringToUTF8(const std::string& gbkData)
	{
		const char* GBK_LOCALE_NAME = "CHS";  //GBK在windows下的locale name(.936, CHS ), linux下的locale名可能是"zh_CN.GBK"

		std::wstring_convert<std::codecvt<wchar_t, char, mbstate_t>>
			conv(new std::codecvt<wchar_t, char, mbstate_t>(GBK_LOCALE_NAME));
		std::wstring wString = conv.from_bytes(gbkData);    // string => wstring

		std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
		std::string utf8str = convert.to_bytes(wString);     // wstring => utf-8

		return utf8str;
	}
	static void OutputToDebugWindow(const std::string& message) {
		// 将 std::string 转换为宽字符字符串
		int len = MultiByteToWideChar(CP_UTF8, 0, message.c_str(), -1, NULL, 0);
		if (len > 0) {
			wchar_t* wideMessage = new wchar_t[len];
			MultiByteToWideChar(CP_UTF8, 0, message.c_str(), -1, wideMessage, len);
			OutputDebugStringW(wideMessage);
			delete[] wideMessage;
		}
	}
	static std::string AnsiToUtf8(const char* ansiStr) {
		int len = MultiByteToWideChar(CP_ACP, 0, ansiStr, -1, NULL, 0);
		if (len <= 0) return "";

		wchar_t* wideStr = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, ansiStr, -1, wideStr, len);

		len = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, NULL, 0, NULL, NULL);
		if (len <= 0) {
			delete[] wideStr;
			return "";
		}

		char* utf8Str = new char[len];
		WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, utf8Str, len, NULL, NULL);

		std::string result(utf8Str);
		delete[] wideStr;
		delete[] utf8Str;
		return result;
	}
};

