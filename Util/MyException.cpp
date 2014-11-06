#include "StdAfx.h"
#include "MyException.hpp"


CMyException::CMyException(void)
{
}

CMyException::CMyException(const wchar_t* wcs)
{
	wcsMessage=wcs;
}

CMyException::~CMyException(void)
{
}
