#include "StdAfx.h"
#include "IOHelper.hpp"
#include "YbkUtil.hpp"

IOHelper::IOHelper(void)
{
}


IOHelper::~IOHelper(void)
{
	for(int i=0; i<con.size(); ++i)
		delete [] con[i];

	con.clear();
}


const char* IOHelper::GetFileData(const char* fileName)
{
	if( 1 == GetFileDataLocal(fileName) )
		return NULL;

	return buffer.c_str();
}

std::vector<const char*> IOHelper::GetFileDataByLine(const char* fileName)
{
	std::string del_return = "\n";
	size_t pos=0, pos1=0, pos2;

	for(int i=0; i<con.size(); ++i)
		delete [] con[i];
	con.clear();

	if( 1 == GetFileDataLocal(fileName) )
		return con;

	while ((pos = buffer.find(del_return, pos1)) != std::string::npos)
	{
		pos2 = buffer.find("\r", pos1);
		std::string s= buffer.substr(pos1, (pos>pos2?pos2:pos)-pos1).c_str();
		int l = s.length();
		char* str = new char[l+1];
		memcpy((char*)str, s.data(), sizeof(char)*l+1);
		con.push_back(str );

		pos1 = pos+del_return.length();
	}

	return con;
}

// http://stackoverflow.com/questions/268023/what-s-the-best-way-to-check-if-a-file-exists-in-c-cross-platform
#include <boost/filesystem.hpp>
int IOHelper::GetFileDataLocal(const char* fileName)
{
	if ( !boost::filesystem::exists( fileName ) )
	{
		printf("Couldn't find file : %s\n", fileName );
		return 1;
	}

	basic_vectorstream<std::vector<char>> vectorStream;
	#define READ_BINARY std::ios_base::in | std::ios_base::binary

	std::string ext = GetFileExtenstion(fileName );

	if(ext.compare("gz") != 0)
	{
		file_mapping fm(fileName, read_only);
		// Map the file in memory
		mapped_region region(fm, read_only);
		// Get the address where the file has been mapped
		buffer = (char*)region.get_address();
//		len = region.get_size()/sizeof(char);
	}
	else
	{
		std::ifstream file(fileName, READ_BINARY);
		filtering_streambuf<input> in;
		in.push(gzip_decompressor());
		in.push(file);

		boost::iostreams::copy(in, vectorStream);

		std::string temp(vectorStream.vector().begin(), vectorStream.vector().end() );
		buffer.swap(temp);
	}

	return 0;

}

#define READ_FD 0
#define WRITE_FD 1

#define CHECK(a) if ((a)!= 0) return -1;

CRedirectStd::~CRedirectStd()
{
#ifndef _CONSOLE
	stdout->_file = -1;
	stdin->_file  = -1;

	FreeConsole();
#endif
	if( -1 != fdStdOut )
		_close(fdStdOut);
	if( -1 != fdStdErr )
		_close(fdStdErr);
	if( -1 != fdStdPipe[WRITE_FD])
		_close(fdStdPipe[WRITE_FD]);
	if( -1 != fdStdPipe[READ_FD])
		_close(fdStdPipe[READ_FD]);
}

CRedirectStd::CRedirectStd()
{
#ifndef _CONSOLE
	AllocConsole();

	stdout->_file = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
	stderr->_file  = _open_osfhandle((long)GetStdHandle(STD_ERROR_HANDLE), _O_TEXT);
#endif

}

int CRedirectStd::Set(int bufferSize)
{
	if (_pipe(fdStdPipe, bufferSize, O_TEXT)!=0)
	{
		//treat error eventually
		return 1;
	}

	fdStdOut = _dup(_fileno(stdout));
	fdStdErr = _dup(_fileno(stderr));

	return 0;
}

int CRedirectStd::OutStart()
{
	fflush( stdout );
	CHECK(_dup2(fdStdPipe[WRITE_FD], _fileno(stdout)));
	ios::sync_with_stdio();
	setvbuf( stdout, NULL, _IONBF, 0 ); // absolutely needed

	// write cuz if no string then freezing
	fprintf(stdout, "Redirect");

	return 0;
}

int CRedirectStd::OutStop()
{
	CHECK(_dup2(fdStdOut, _fileno(stdout)));
	ios::sync_with_stdio();
	return 0;
}

int CRedirectStd::ErrStart()
{
	fflush( stderr );
	CHECK(_dup2(fdStdPipe[WRITE_FD], _fileno(stderr)));
	ios::sync_with_stdio();
	setvbuf( stderr, NULL, _IONBF, 0 ); // absolutely needed

	// write cuz if no string then freezing
	fprintf(stderr, "Redirect");

	return 0;
}

int CRedirectStd::ErrStop()
{
	CHECK(_dup2(fdStdErr, _fileno(stderr)));
	ios::sync_with_stdio();
	return 0;
}

int CRedirectStd::GetBuffer(char *buffer, int size)
{
	int nOutRead = _read(fdStdPipe[READ_FD], buffer, size);
	int len = strlen("redirect");
	if(nOutRead>=len)
	{
		int i=0, j=0;
		for( i=len, j=0; i< nOutRead; ++i, ++j )
		{
			buffer[j] = buffer[i];
		}
		for(;j<nOutRead; ++j)
		{
			buffer[j] = 0;
		}
	}
	else
	{
		for(int i=0;i<nOutRead; ++i)
		{
			buffer[i] = 0;
		}
	}

	return nOutRead;
}