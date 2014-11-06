#pragma once

// used for data by line
#include <vector>

/// @class Input/Output Helper
/// @brief name is IOHelper, but main act is get data from file
class IOHelper
{
private:
	/// saved data by line
	std::vector<const char*> con;

	/// data save buffer
	std::string buffer;

private:
	/// Read file, gz or not, using boost, put to buffer, if error return 1 else 0
	int GetFileDataLocal(const char* fileName);

public:
	/// constructor
	IOHelper(void);

	/// destructor
	~IOHelper(void);

	/// return buffer char array, if error return null
	const char* GetFileData(const char* fileName);

	/// return data vector by line, if error return empty vector
	std::vector<const char*> GetFileDataByLine(const char* fileName);

};

/// @class CRedirectStd
/// @brief redirect stderr to stdout, How to redirect stderr for printf
/// @see http://stackoverflow.com/questions/573724/how-can-i-redirect-stdout-to-some-visible-display-in-a-windows-application
/// @see http://stackoverflow.com/questions/7664/windows-c-how-can-i-redirect-stderr-for-calls-to-fprintf
class CRedirectStd
{
public:
	/// constructor
	CRedirectStd();

	/// destructor
	~CRedirectStd(void);

	/// initialize
	int Set(int bufferSize=1024);

	/// copy stdout to write buffer
	int OutStart();

	/// end work
	int OutStop();

	/// copy stderr to write buffer
	int ErrStart();

	/// end work
	int ErrStop();

	/// get buffer data
	int GetBuffer(char *buffer, int size);

private:
	/// stdout, stderr dup pipe
	int fdStdPipe[2];

	/// temp stdout
	int fdStdOut;

	/// temp stderr
	int fdStdErr;

};