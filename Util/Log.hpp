#pragma once

#include <assert.h>

#define  MYAPP_DEBUG_TRACE

static bool IsLogPrint=true;
void MyLogErrorHandleCheck(HRESULT hr);

#ifdef COLOR_RGB
#undef COLOR_RGB
#else
#define COLOR_RGB(r, g, b) ((DWORD)(((((r))<<16)|(((g))<<8)|((b)))))
#endif

#ifdef __cplusplus
	inline void null_func(wchar_t *format, ...) { }
	#define DbgEmpty null_func
#else
	#define DbgEmpty { }
#endif

#define SET_PRINT_LOG IsLogPrint = true;
#define SET_NOT_PRINT_LOG IsLogPrint = false;

/* Debug Trace Enabled */
#ifdef  MYAPP_DEBUG_TRACE
	#define DEBUG_PRINT wprintf
	#define FUNC_IN_LOG(x) \
		std::cout<<"\t"<<__LINE__ << " " <<x<<std::endl; __check__flag__++;
#define FUNC_IN_LOG_WITH_INT(desc, d) \
	std::cout << "\t" << __LINE__ << " " << desc << " " << d << std::endl; __check__flag__++;
#else
/* Debug Trace Disabled */
	#define DEBUG_PRINT DbgEmpty
#endif

//! [01] Relese and NOT null setting
#define RELEASE_(x) { if(x==NULL) {} else  {x->Release(); x=NULL;} } 

//! [02] Release and null setting
#define DELETE_(x) { \
	if(x==NULL){} else {delete x; x=NULL;} };

//! [03] x 객체 Release 함수 실행 후 delete
#define DELETE_RELEASE_(x)  { \
	if(x==NULL){} else { int iRet=x->Release(); \
	if( iRet != 0 ){std::cout<< __LINE__ << " Release failed"<<std::endl;} \
	else {delete x; x=NULL;} } }

//! [04] 02 를 배열 포인터에 적용, 05 의 간편화
#define DELETE_ARRAY__(x)  { if(x==NULL){} else {delete [] x; x=NULL;} }

//! [05] 02 를 삭제하려는 포인터를 가진 배열에 적용
#define DELETE_ARRAY_(x, num_elem)  { \
	if(x==NULL){} else { for(int i=0; i<num_elem; ++i ) { \
	int iRet=x->Release(); \
	if( iRet != 0 ){std::cout<< __LINE__ << " Release failed"<<std::endl;} }\
	else {delete [] x;} } }

//!
#define N_(x, object) { \
	x=NULL; \
	x = new object; \
	if(NULL==x)\
	{std::cout<<__LINE__<<" Initialize failed"<<std::endl;}

//!
#define N_ARRAY_(x, object, num) { \
	x=NULL; \
	x = new object[num]; \
	if(NULL==x)\
	{std::cout<<__LINE__<<" Initialize failed"<<std::endl;}

//! [06] Set x to new object and check null
#define N_INIT_(x, object) { \
	x=NULL; \
	x = new object; \
	if(NULL==x){std::cout<<__LINE__<<" Initialize failed"<<std::endl;} \
	else { x->Initialize(); } }

//! [07]
#define CHECK_FUNC_RETURN_HANDLE_(x) \
	CHECK_FUNC_RETURN_HANDLE_DESC_(x, "Function return false");

#define CHECK_HANDLE_CODE_(hr) std::cout << __FILE__ << " "; MyLogErrorHandleCheck(hr);

	//!
#define CHECK_FUNC_RETURN_HANDLE_DESC_(x, desc) \
	hr = x; \
	if( S_OK== hr){} \
	else{ CHECK_HANDLE_CODE_(hr); \
	CHECK_FUNC_RETURN_CODE_DESC_(1, desc);}

	//!
#define CHECK_FUNC_RETURN_CODE_(x) \
	CHECK_FUNC_RETURN_CODE_DESC_(x, "Function return false");

	//! Console warning font color
#define DEFAULT_COLOR \
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

	//! Console error font color
#define ERROR_COLOR \
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE);

	//!
#define CHECK_CONFIRM_UPPER_0_(x, var_name) \
	CHECK_COMPARE_VALUE_(x, 1, var_name);

#define CHECK_CONFIRM_NOT_MINUS_(x, var_name) \
	CHECK_COMPARE_VALUE_(x, 0, var_name);

#define CHECK_COMPARE_VALUE_(x, d, var_name) \
	ERROR_COLOR; \
	if( d<= x){} \
	else{ std::wcout<<"("<<__LINE__<<")" << var_name << " contains value = " << x <<std::endl; \
	{assert(false);}} \
	DEFAULT_COLOR;

#define CHECK_NULL_(x, var_name) \
	CHECK_NULL_DEFAULT_(x, var_name, true);

	//!
#define CHECK_NULL_DEFAULT_(x, var_name, stop_option) \
	ERROR_COLOR; \
	if( NULL!= x){} \
	else{ std::wcout<<"("<<__LINE__<<")" << var_name << " is null"<<std::endl; \
	if(stop_option) {assert(false);}} \
	DEFAULT_COLOR;

#define CHECK_FUNC_RETURN_CODE_DESC_NOT_STOP_(x, desc) \
	CHECK_FUNC_RETURN_CODE_DESC_DEFAULT_(x, desc, false);

	//! 중간에 멈추는 에러
#define CHECK_FUNC_RETURN_CODE_DESC_(x, desc) \
	CHECK_FUNC_RETURN_CODE_DESC_DEFAULT_(x, desc, true);

	//! 기본 오류, 에러 발생
#define CHECK_FUNC_RETURN_CODE_DESC_DEFAULT_(x, desc, stop_option) \
	ERROR_COLOR; \
	_nRetCode = x; \
	if( 0== _nRetCode){} \
	else{ std::wcout<<"("<<__LINE__<<")" << desc<<std::endl; \
	if(stop_option) {assert(false);}} \
	DEFAULT_COLOR;

#define INITIALIZE_FIRST_ \
	{ int __check__flag__=0; \
	int _nCheckMemory=0; int _nRetCode=0; HRESULT hr=S_OK; \
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN); \
	if(IsLogPrint)std::cout<<"<"<<__FUNCTION__<<":"<<__LINE__<<std::endl; \
	DEFAULT_COLOR;

#define LAST_CHECK_MEMORY_ \
	if(0==_nCheckMemory){} \
	ERROR_COLOR; \
	std::cout<<__LINE__<<" Memory Not Released"<<std::endl; \
	_nRetCode=1;DEFAULT_COLOR;

#define RETURN_CODE_ \
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN); \
	__check__flag__=0; if(IsLogPrint)std::cout<<"/"<<__FUNCTION__<<">"<<std::endl; \
	DEFAULT_COLOR;return _nRetCode; }
#define RETURN_CODE_NORANGE \
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN); \
	__check__flag__=0; if(IsLogPrint)std::cout<<"/"<<__FUNCTION__<<">"<<std::endl; \
	DEFAULT_COLOR;return _nRetCode;

#define RETURN_UNKNOWN_ERROR \
	{std::wcout<< __LINE__ << " " << "Return 1" << std::endl; assert(false); return 1;}

#define RETURN_ERROR_CODE_(hr) \
	if(hr == S_OK){} \
	else{CHECK_HANDLE_CODE_(hr); std::wcout << __LINE__ << " " << hr << std::endl; return 1;}

#define RETURN_EROR_CODE_DEFAULT_ RETURN_ERROR_CODE_(E_FAIL);

//! Return Statement For HRESULT Return Function
#define RETURN_HANDLE_ \
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN); \
	__check__flag__=0; if(IsLogPrint)std::cout<<"/"<<__FUNCTION__<<">"<<std::endl; \
	DEFAULT_COLOR;return hr; }

//! Shpw Error Text on Return Statement For HRESULT Return Function
#define RETURN_ERROR_HANDLE_ \
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN); \
	__check__flag__=0; std::cout<<"/"<<__FUNCTION__<<">"<<std::endl; \
	DEFAULT_COLOR;return hr;

//! Return Statement For Void Return Function
#define RETURN_ \
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN); \
	__check__flag__=0; if(IsLogPrint)std::cout<<"/"<<__FUNCTION__<<">"<<std::endl; \
	DEFAULT_COLOR;return; }

#include <fstream>
class CLog
{
public:
	CLog(bool useHtmlLog=false);
	~CLog(void);

	void Write(wchar_t* );
	int Release();
	int Initialize();

	int InitHtmlLog();
	int HtmlPrint( unsigned long color, char* sz );

	FILE* _ConsoleLog;
	std::ofstream m_HtmlLog;

};

typedef CLog Logging;

//#include <errno.h>
int CheckErrNo(errno_t _errno);
