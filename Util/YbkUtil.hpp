/// @mainpage Default utility
/// @section ABOUT About doxygen
/// @see http://neotrinity.egloos.com/943385
/// @see http://kieuns.com/wiki/doku.php?id=tool:doxygen
/// @section OINFO The 1st goal
/// - Add plane, Set plane vertex to sin to wave (wrong)
/// - Add height map, Set plane vertex to sin to wave
/// - Add cube, set collision between wave plane and cube bottom
/// - Check cube moving with wave plane
/// @section INFO Info
/// - Creator		: yongilKim(yongbam)
/// - Create date	: 2014-08-25
/// - Done 1st date	: ?
/// - Progress time : ? days
/// @section PGINFO Progress
/// - Write date   / Coder    : Detail
/// - 2014. 09. 18 / yongbam  : copy from source
/// - 2014. 09. 26 / yongbam  : check error if file not exist, document work
/// couldn't remember how to do it before
/// @section MINFO Modify
/// - Modify date  / Modifier : Detail
/// @section BINFO Bug
/// - Find date    / Finder   : Problem/fix date
/// - 2014. 09. 26 / yongbam  : so many things fix but forget it...

#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Setting import library

// http://stackoverflow.com/questions/13794130/visual-studio-how-to-check-used-c-platform-toolset-programmatically
#ifdef _DEBUG
	#ifdef WIN32
		#ifdef _MSC_FULL_VER
		#if   _MSC_FULL_VER == 170061030
			// MSVS 2012; Platform Toolset v110
			#pragma comment(lib,"YbkLibDefault_x86v110d.lib")
		#elif   _MSC_FULL_VER == 170060315
			// MSVS 2012; Platform Toolset v110
			#pragma comment(lib,"YbkLibDefault_x86v110d.lib")
		#elif _MSC_FULL_VER == 170051025
			// MSVS 2012; Platform Toolset v120_CTP_Nov2012
		#elif _MSC_FULL_VER == 180020617
		// MSVS 2013; Platform Toolset v120
		#else		
			#pragma comment(lib,"YbkLibDefault_x86v100d.lib")
		#endif
	#endif // _MSC_FULL_VER
	#else
		#ifdef _VC2012
		//			#pragma comment(lib,"YbkLibDefault_x64v110Debug.lib")
		#endif
		#ifdef _VC2010
		//			#pragma comment(lib,"YbkLibDefault_x64v100Debug.lib")
		#endif
	#endif
#else
	#ifdef WIN32
		#ifdef _MSC_FULL_VER
			#if   _MSC_FULL_VER == 170061030
				// MSVS 2012; Platform Toolset v110
				#pragma comment(lib,"YbkLibDefault_x86v110.lib")
			#elif   _MSC_FULL_VER == 170060315
				// MSVS 2012; Platform Toolset v110
				#pragma comment(lib,"YbkLibDefault_x86v110.lib")
			#elif _MSC_FULL_VER == 170051025
				// MSVS 2012; Platform Toolset v120_CTP_Nov2012
			#elif _MSC_FULL_VER == 180020617
				// MSVS 2013; Platform Toolset v120
			#else		
				#pragma comment(lib,"YbkLibDefault_x86v100.lib")
			#endif
		#endif // _MSC_FULL_VER
		#else
		#ifdef _VC2012
		//			#pragma comment(lib,"YbkLibDefault_x64v110Debug.lib")
		#endif
		#ifdef _VC2010
		//			#pragma comment(lib,"YbkLibDefault_x64v100Debug.lib")
		#endif
	#endif
#endif

#include "IOHelper.hpp"
#include "MyDefine.hpp"
#include "MyException.hpp"
#include "MyHttpClient.hpp"
#include "Variables.hpp"
#include "Log.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// common

#include <string.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// global function

/// @brief Get File's extension ( a."exe" )
/// @param file_name File name
/// @return Return file's extension
/// @remark It's just remark tag test
const char* GetFileExtenstion (const char * file_name);

/// @brief Get File's root directory like as "C:\"
/// @param file_name File name
/// @return Return file's root directory
const char* GetFileRootDir (const char * file_name);

/// @brief Get File's root directory like as "C:\"
/// @param file_name File name
/// @return Return file's root directory
const char* GetFileRootDirWithDivChar (const char * file_name);

/// @brief Get File's root directory like as "C:\"
/// @param file_name File name
/// @return Return file's root directory
const char* GetFileName (const char * file_name);

/// @brief Get File's root directory like as "C:\"
/// @param file_name File name
/// @return Return file's root directory
const char* GetFileNameExt (const char * file_name);

/// @brief Get File's root directory like as "C:\"
/// @param file_name File name
/// @return Return file's root directory
int del_delimiter(char* v, bool include_space=true);

/// @brief Multi byte string to wide byte string ( char to wchar_t )
std::wstring mbs_to_wcs(std::string const& str, std::locale const& loc = std::locale() );

/// @brief Wide byte string to Multi byte string ( wchar_t to char )
std::string wcs_to_mbs(std::wstring const& str, std::locale const& loc = std::locale() );

/// @brief Wide byte string to Multi byte string ( wchar_t to char ) but not return
/// @see http://msdn.microsoft.com/ko-kr/library/s7wzt4be.aspx
int wcs_to_mbs(char* buf, const wchar_t* wstr, int dst_size = 512);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// progress bar

/// @class CProgressBar
class CProgressBar
{
public:
	void Start(char* header, int cnt=0);
	void PrintBar();
	void End();

	float p_count;
	int before_count;
	float base_count;

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// timer

/// @class CMyTimer
class CMyTimer
{
public:

private:
	double countsPerSecond;
	__int64 CounterStart;
	int frameCount;
	int fps;
	__int64 frameTimeOld;
	double frameTime;

public:
	CMyTimer(void);
	~CMyTimer(void);

	int StartTimer();
	double GetTime();
	double GetFrameTime();
	int AddFrameCounter();	
	int SetFrameCounter();
	int SetFps();
	int GetFps();

	int CheckStart();
	int CheckEnd(int& hour, 
		int& minute, int& second, 
		double& nano_second);

};

typedef CMyTimer MyTimer;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Math

/// @class CYbkMath
class CYbkMath
{
public:
	CYbkMath(void);
	~CYbkMath(void);

	int BaseConv(char* v, int base);
	int GetOct(char* str, int base);
	int Pow(int val, int cnt);
	double Round(double val, int precision=0, bool isFloor=true);
	//! 숫자를 한글단어로 변환(ex. 12121 = 만이천백이십일)
	int IntToKoreanWord(int value, char* OutputNumString);
	//	const char* IntToKoreanWord(int value, int* errno = NULL);

};
