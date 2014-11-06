#pragma once

// For windef.hpp
#include <Windows.h>

#define UNICODE_STRING std::wstring
#define CINT	const int
#define CBOOL	const bool
#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HEIGHT 480
#define NOT_IMPLEMENT -101

#define COLOR_RGB(r, g, b) ((DWORD)(((((r))<<16)|(((g))<<8)|((b)))))