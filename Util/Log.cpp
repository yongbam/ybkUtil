#include "StdAfx.h"
#include "Log.hpp"
#include <d3d11.h>
#include <d3dx10core.h>
//#include "MyDefine.hpp"

#include <iostream>
void MyLogErrorHandleCheck(HRESULT hr)
{
	std::wcout << "Handle : " << std::hex << hr;

	switch(hr)
	{
	case D3D11_ERROR_FILE_NOT_FOUND:
		std::wcout<<L"(FileNotFound)The file not found"<<std::endl;
		break;
	case D3DERR_INVALIDCALL:
		std::wcout<<L"(INVALIDCALL)The method call is invalid"<<std::endl;
		std::wcout<<L"For example, a method's parameter may not be a valid pointer."<<std::endl;
		break;
	case DXGI_ERROR_INVALID_CALL:
		std::wcout<<L"(DXGI_ERROR_INVALID_CALL)The method call is invalid"<<std::endl; 
		std::wcout<<L"For example, a method's parameter may not be a valid pointer."<<std::endl;
		break;
	case E_FAIL:
		std::wcout<<L"(E_FAIL)Unknown Error"<<std::endl;
		break;
	case E_OUTOFMEMORY:
		std::wcout<<L"(E_OUTOFMEMORY)Unknown Error"<<std::endl;
		break;
	case S_FALSE:
		std::wcout<<L"(S_FALSE)Half Error"<<std::endl;
		break;
	case E_INVALIDARG:
		std::wcout<<L"(E_INVALIDARG)";
		std::wcout<<L"An invalid parameter was passed to the returning function."<<std::endl;
		break;
	case E_HANDLE:
		std::wcout << L"Invalid Handle" << std::endl;
		break;
	default:
		std::wcout << "Submit, added this error to log.hpp" << std::endl;
		break;
	}	
}

static int CheckErrNo(errno_t _errno)
{
	char errbuf[512];
	memset((char*)errbuf, 0, sizeof(char)*512);
	if(_errno == 0)
	{
		return 0;
	}
	else
	{
		strerror_s(errbuf, 512, _errno);
		return 1;
	}
}

CLog::CLog(bool useHtmlLog)
{
#ifdef MYAPP_DEBUG_TRACE
	/*	hConsoleOut = CreateConsoleScreenBuffer( GENERIC_READ | GENERIC_WRITE, 
		FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL );
	if( hConsoleOut == INVALID_HANDLE_VALUE ) 
		return D_ERROR;
*/
	if(useHtmlLog)
	{
		if( 1 == InitHtmlLog() ) 
			MessageBox(NULL, L"Console Error", L"Error", MB_OK);
		HtmlPrint( COLOR_RGB(128, 128, 0 ), "HELLO WORLD!" );
	}

	if(AllocConsole())
	{
		errno_t err;
		// PS. IF USE TEXT MODE freopen_s RETURN D_ERROR
		// USE "wb" OPTION
		err = freopen_s(&_ConsoleLog, "CONOUT$", "wt", stdout);
		if( 0 != err ) 
			MessageBox(NULL, L"Console Error", L"Error", MB_OK);

		SetConsoleTitle(L"MyApp : Debug Console");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
			FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		// FOREGROUND_GREEN | FOREGROUND_BLUE 1
		printf("\n");
		printf(" MyApp Debug Console\n");
		printf("\n");

	}
#endif
}

CLog::~CLog(void)
{
}

void CLog::Write(wchar_t* str)
{
}

int CLog::Initialize()
{
	return 0;

}

int CLog::Release()
{
	fclose( _ConsoleLog );
	m_HtmlLog.close();

	return 0;
}

int CLog::HtmlPrint( unsigned long color, char* sz )
{
	m_HtmlLog <<"<span style=\"color:#";
	m_HtmlLog.width(6);	// 0x000000 r(2)g(2)b(2) size
	m_HtmlLog.fill('0');	// if r = 0 r is delete than 0xffff so fill 0 of r or b or g
	m_HtmlLog << std::right<< std::hex << color  << std::dec;
	m_HtmlLog<< "\">"
		<< sz
		<< "</span><br />"
		<< std::endl;

	return 0;
}

int CLog::InitHtmlLog()
{
	m_HtmlLog.open( "LOG\\LOG.HTML");
	if( !m_HtmlLog.is_open() ) 
		return 1;

	m_HtmlLog << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<< std::endl
		<<"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" "
		<< " \"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">"<< std::endl
		<<"<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\">"<< std::endl
		<<"<head>"<< std::endl
		<<"<title>DEBUG INFO HTML FILE</title>"<< std::endl
		<<"<meta http-equiv=\"generator\" content=\"My HTML Editor\" />"<< std::endl
		<<"<meta name=\"created\" content=\"Thursday, 06 5 2010 04:12:39 GMT\" />"<< std::endl
		<<"<meta name=\"description\" content=\"\" />"<< std::endl
		<<"<meta name=\"keywords\" content=\"\" />"<< std::endl
		<<"</head>" <<std::endl
		<<"<body bgcolor=\"#FFFFFF\" text=\"#000000\" \
		  link=\"#0000FF\" vlink=\"#800080\" alink=\"#FF0000\">" << std::endl;

	return 0;

}