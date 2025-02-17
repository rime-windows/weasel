#pragma once
#include <string>

// UTF-8 conversion
inline const char* wcstoutf8(const WCHAR* wstr)
{
	const int buffer_len = 1024;
	static char buffer[buffer_len];
	memset(buffer, 0, sizeof(buffer));
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, buffer, buffer_len - 1, NULL, NULL);
	return buffer;
}

inline const WCHAR* utf8towcs(const char* utf8_str)
{
	const int buffer_len = 4096;
	static WCHAR buffer[buffer_len];
	memset(buffer, 0, sizeof(buffer));
	MultiByteToWideChar(CP_UTF8, 0, utf8_str, -1, buffer, buffer_len - 1);
	return buffer;
}

inline int utf8towcslen(const char* utf8_str, int utf8_len)
{
	return MultiByteToWideChar(CP_UTF8, 0, utf8_str, utf8_len, NULL, 0);
}

inline std::wstring getUsername() {
	DWORD len = 0;
	GetUserNameW(NULL, &len);

	if (len <= 0) {
		return L"";
	}

	wchar_t *username = new wchar_t[len + 1];

	GetUserNameW(username, &len);
	if (len <= 0) {
		delete[] username;
		return L"";
	}
	auto res = std::wstring(username);
	delete[] username;
	return res;
}

// data directories
std::wstring WeaselUserDataPath();

const char* weasel_shared_data_dir();
const char* weasel_user_data_dir();

// resource
std::string GetCustomResource(const char *name, const char *type);