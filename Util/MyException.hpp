#pragma once

#include <string>

class CMyException
{
public:
	CMyException(void);
	CMyException(const wchar_t*);
	~CMyException(void);

	std::wstring wcsMessage;
};

