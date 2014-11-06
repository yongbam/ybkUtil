#pragma once

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "1337"
#define DEFAULT_ADDR "127.0.0.1"

//! send data to remote debug client
class CYbkHttpClient
{
public:
	//! creator
	CYbkHttpClient(void);

	//! destructor
	~CYbkHttpClient(void);

	//! connect to remote
	int Connect(const char* addr=DEFAULT_ADDR, 
		const char* port=DEFAULT_PORT);

	//! send message to remote
	int Send(const char* msg);

	//! get last error
	int GetLastError(char* errMsg);

private:
	//! initialize
	int Initialize();

	//! release
	int Release();

	//! save error message
	char errorMessage[DEFAULT_BUFLEN];

	//! save data what get from sender
	char recvbuf[DEFAULT_BUFLEN];

	//! result of function
	int iResult;

	//! size of data what get from sender
	int recvbuflen;

	//! use debug or not
	bool bUsed;
};