// StdAfx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#pragma warning(disable:4005)
// TODO: reference additional headers your program requires here
// c header
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <io.h>

// c++ header
#include <iostream>
#include <fstream>

// c++ stl
#include <vector>
#include <string>

// windows
#include <windows.h>
/*
#ifndef _USE_OLD_IOSTREAMS
	using namespace std;
#endif
	*/
using namespace std;
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/copy.hpp>
using namespace boost::iostreams;

#include <boost/interprocess/streams/vectorstream.hpp>
using namespace boost::interprocess;