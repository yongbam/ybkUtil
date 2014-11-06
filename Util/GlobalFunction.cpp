#include "StdAfx.h"
#include "YbkUtil.hpp"

std::string delimiter_div = "\\";
std::string delimiter_point = ".";
size_t pos;
size_t pos1;
std::string w1;
std::string www;

const char* GetFileRootDirWithDivChar (const char * file_name)
{
	w1 = file_name;
	pos1 = w1.rfind(delimiter_div);
	if( pos == std::string::npos)
		return NULL;

	//	std::cout <<w1.substr(0, pos1 ).c_str();
	//	return w1.substr(0, pos1 ).c_str();
	www = w1.substr(0, pos1+delimiter_div.length() ).c_str();
	return www.c_str();
}

const char* GetFileRootDir (const char * file_name)
{
	w1 = file_name;
	pos1 = w1.rfind(delimiter_div);
	if( pos == std::string::npos)
		return NULL;

//	std::cout <<w1.substr(0, pos1 ).c_str();
//	return w1.substr(0, pos1 ).c_str();
	www = w1.substr(0, pos1 ).c_str();
	return www.c_str();
}

const char* GetFileNameExt (const char * file_name)
{
	w1 = file_name;
	pos = w1.find(delimiter_point);
	pos1 = w1.rfind(delimiter_div);
	if( pos == std::string::npos)
		return NULL;

	www = w1.substr(pos1+delimiter_div.length(), pos ).c_str();
//	return w1.substr(pos1, pos ).c_str();
	return www.c_str();
}

const char* GetFileName (const char * file_name)
{
	w1 = file_name;
	pos = w1.find(delimiter_point);
	pos1 = w1.rfind(delimiter_div);
	if( pos == std::string::npos)
		return NULL;

	w1.erase(pos);
	www = w1.substr(pos1+delimiter_div.length() ).c_str();
	//	return w1.substr(pos1, pos ).c_str();
	return www.c_str();
}

const char* GetFileExtenstion (const char * file_name)
{
	/*
	int file_name_len = strlen (file_name); 
	file_name +=file_name_len ;

	char *file_ext ;
	for(int i =0 ; i <file_name_len ; i ++)
	{
		if(* file_name == '.' )
		{
			file_ext = file_name +1 ;
			break;
		} 
		file_name --;
	} 
	return file_ext ;
	*/
	w1 = file_name;
	// . 이 여러 개 있는 경우로 인해서 rfind, instead of find
	pos = w1.rfind(delimiter_point);
	if( pos == std::string::npos)
		return NULL;

	www=w1.substr(pos+delimiter_point.length(), w1.length() ).c_str();
//	www=w1.substr(pos+delimiter_point.length(), w1.length() ).c_str();
//	return w1.substr(pos+delimiter1.length(), w1.length() ).c_str();
	return www.c_str();
}

// http://zero-one-space.blogspot.kr/2012/03/errnot.html
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

int wcs_to_mbs(char* buf, const wchar_t* wstr, int dst_size)
{
	int src_size = wcslen(wstr);
	size_t i =0;
	errno_t _errno;

	// Conversion
	_errno = wcstombs_s(&i, buf, (size_t)dst_size, 
		wstr, (size_t)src_size );

	buf[i-1]= '\0';

	return CheckErrNo(_errno);
}

std::wstring mbs_to_wcs(
	std::string const& str, std::locale const& loc )
{
	typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_t;
	codecvt_t const& codecvt = std::use_facet<codecvt_t>(loc);
	std::mbstate_t state = std::mbstate_t();
	std::vector<wchar_t> buf(str.size() + 1);
	char const* in_next = str.c_str();
	wchar_t* out_next = &buf[0];
	std::codecvt_base::result r = codecvt.in(state,
		str.c_str(), str.c_str() + str.size(), in_next,
		&buf[0], &buf[0] + buf.size(), out_next);
	if (r == std::codecvt_base::error)
		throw std::runtime_error("can't convert string to wstring");  
	return std::wstring(&buf[0]);
}

std::string wcs_to_mbs(
	std::wstring const& str, std::locale const& loc )
{
	typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_t;
	codecvt_t const& codecvt = std::use_facet<codecvt_t>(loc);
	std::mbstate_t state = std::mbstate_t();
	std::vector<char> buf((str.size() + 1) * codecvt.max_length());
	wchar_t const* in_next = str.c_str();
	char* out_next = &buf[0];
	std::codecvt_base::result r = codecvt.out(state,
		str.c_str(), str.c_str() + str.size(), in_next,
		&buf[0], &buf[0] + buf.size(), out_next);
	if (r == std::codecvt_base::error)
		throw std::runtime_error("can't convert wstring to string");  
	return std::string(&buf[0]);
}

int del_delimiter(char* v, bool include_space)
{
	int ascii= 31;
	if( include_space)
		ascii = 32; // space
	int len = strlen(v);
	int st = 0;
	for( int i=0; i<len; ++i)
	{
		if(v[i]> ascii )
		{
			st = i;
			break;
		}
	}
	int cnt = 0;
	for(int i=st, j=0; i<len; ++i, ++j)
	{
		v[j]=v[i];
		cnt++;
	}
	for(int i=cnt; i<len; ++i)
	{
		v[i]=NULL;
	}

	return 0;
}