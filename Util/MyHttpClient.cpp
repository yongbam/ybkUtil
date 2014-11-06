#include "StdAfx.h"

//#include <WinSock2.hpp>
#include <ws2tcpip.h>
#include "MyHttpClient.hpp"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

WSADATA wsaData;
SOCKET ConnectSocket;

CYbkHttpClient::CYbkHttpClient(void)
{
}


CYbkHttpClient::~CYbkHttpClient(void)
{
}

int CYbkHttpClient::GetLastError(char* errMsg)
{
	errMsg = errorMessage;
	return 0;
}

int CYbkHttpClient::Initialize()
{
	ConnectSocket = INVALID_SOCKET;
	ZeroMemory((char*)recvbuf, sizeof(char)*DEFAULT_BUFLEN);
	iResult=0;
	recvbuflen = DEFAULT_BUFLEN;
	bUsed=false;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0) 
	{
		sprintf_s(errorMessage, DEFAULT_BUFLEN, 
			"WSAStartup failed with error: %d", iResult);
		return 1;
	}

	return 0;
}

int CYbkHttpClient::Connect(const char* addr, const char* port)
{
	addrinfo *result=NULL, *ptr=NULL, hints;

	ZeroMemory( &hints, sizeof(hints) );
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	//	iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
	iResult = getaddrinfo(addr, port, &hints, &result);
	if ( iResult != 0 ) 
	{
		printf("getaddrinfo failed with error: %d", iResult);
		WSACleanup();
		return 1;
	}

	// Attempt to connect to an address until one succeeds
	for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {
		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) 
		{
			sprintf_s(errorMessage, DEFAULT_BUFLEN, 
				"socket failed with error: %ld", WSAGetLastError());
			WSACleanup();
			return 1;
		}

		// Connect to server.
		iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		sprintf_s(errorMessage, DEFAULT_BUFLEN,
			"Unable to connect to server");
		WSACleanup();
		return 1;
	}

	bUsed=true;
	return 0;
}

int CYbkHttpClient::Send(const char* msg)
{
	if(!bUsed)
		return 0;

	iResult = send( ConnectSocket, msg, (int)strlen(msg), 0 );
	if (iResult == SOCKET_ERROR) {
		sprintf_s(errorMessage, DEFAULT_BUFLEN,
			"send failed with error: %d", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	printf("%s\n", msg);
	printf("Bytes Sent: %ld\n", iResult);

	return 0;
}

int CYbkHttpClient::Release()
{
	if( !bUsed)
		return 1;

	// shutdown the connection since no more data will be sent
	iResult = shutdown(ConnectSocket, SD_BOTH);
	if (iResult == SOCKET_ERROR) {
		sprintf_s(errorMessage, DEFAULT_BUFLEN,
			"shutdown failed with error: %d", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();

	return 0;
}