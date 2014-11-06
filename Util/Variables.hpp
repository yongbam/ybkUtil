#pragma once

#include <string>
#include "MyDefine.hpp"

#pragma warning(disable:4201)

////////////////////////////////////////////////////////////////////////
// Test

/// @struct _MYINT2
/// @brief int struct that have 2 int
struct _MYINT2
{
	union
	{
		struct
		{
			int x, y;
		};
		struct
		{
			int width, height;
		};
	};
	
	_MYINT2(int x=0, int y=0)
	{
		this->x = x;
		this->y = y;
	}
	inline int mul(){return this->x * this->y;}

};
#define _DIMENSION _MYINT2
#define _POINT _MYINT2

/// @struct _MYINT3
/// @brief int struct that have 2 int
struct _MYINT3
{
	union
	{
		struct
		{
			int x, y, z;
		};
		struct
		{
			int width, height, depth;
			
		};
	};

	_MYINT3(int x=0, int y=0, int z=0)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	void operator=(const _MYINT2 v)
	{
		this->width = v.width;
		this->height = v.height;
		this->depth = 0;
	}
};

#define _VOLUME _MYINT3


////////////////////////////////////////////////////////////////////////
// Ok

/// @struct _MATIRX
/// @brief convert XMMATRIX to custom type
struct _MATRIX
{
	union {
		struct _s{
			FLOAT _11, _12, _13, _14;
			FLOAT _21, _22, _23, _24;
			FLOAT _31, _32, _33, _34;
			FLOAT _41, _42, _43, _44;

		};
		FLOAT _m[4][4];
	};

	_MATRIX( FLOAT _f11, FLOAT _f12, FLOAT _f13, FLOAT _f14,
		FLOAT _f21, FLOAT _f22, FLOAT _f23, FLOAT _f24,
		FLOAT _f31, FLOAT _f32, FLOAT _f33, FLOAT _f34,
		FLOAT _f41, FLOAT _f42, FLOAT _f43, FLOAT _f44 );
	_MATRIX();
	_MATRIX(const float* pArray);
	_MATRIX( FLOAT _f11, FLOAT _f22, FLOAT _f33, FLOAT _f44);

//	std::string _s;
//	const char* ToString(const char* name);
	int _MATRIX::ToString(const char* name, char* OutputString);

	const char* operator=(_MATRIX&) const;
	void operator=(const FLOAT* pArray);
	void operator=(FLOAT* pArray);
	void operator=(FLOAT m[4][4]);

};
typedef _MATRIX MATRIX;

/// @struct _MYFLOAT2
/// @brief convert XMFLOAT2 to custom type
typedef struct _MYFLOAT2
{
	union
	{
		struct
		{
			FLOAT x;
			FLOAT y;

		};
		FLOAT f[2];

	};

#ifdef __cplusplus

	_MYFLOAT2() : x(0), y(0) {};
	_MYFLOAT2(FLOAT _x, FLOAT _y) : x(_x), y(_y) {};
	_MYFLOAT2(const FLOAT* pArray);
	_MYFLOAT2& operator= (const FLOAT* pArray);
	_MYFLOAT2& operator= (const _MYFLOAT2& pArray);

#endif

} MYFLOAT2;

//! convert XMFLOAT3 to custom type
typedef struct _MYFLOAT3
{
	union
	{
		struct
		{
			float x;
			float y;
			float z;

		};
		struct
		{
			float r;
			float g;
			float b;

		};
		float f[3];

	};
		
#ifdef __cplusplus

	_MYFLOAT3() : x(0), y(0), z(0) {};
	_MYFLOAT3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};
	_MYFLOAT3(const float* pArray);
	_MYFLOAT3& operator= (const float* pArray);
	_MYFLOAT3& operator= (const _MYFLOAT3& pArray);
	_MYFLOAT3 operator+ (const _MYFLOAT3& pArray);
	_MYFLOAT3& operator+= (const _MYFLOAT3& pArray);
	_MYFLOAT3 operator/ (const _MYFLOAT3& pArray);
	_MYFLOAT3 operator/ (const float& value);
	_MYFLOAT3 operator- (const _MYFLOAT3& pArray);

#endif

} MYFLOAT3;

//! convert XMFLOAT4 to custom type
typedef struct _MYFLOAT4
{
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;

		};
		struct
		{
			float r;
			float g;
			float b;
			float a;

		};
		float f[4];
	};

#ifdef __cplusplus

	_MYFLOAT4(float _x=0.0f, float _y=0.0f, float _z=0.0f, float _w=0.0f) 
		: x(_x), y(_y), z(_z), w(_w) {};
	_MYFLOAT4(const float *pArray);
	_MYFLOAT4& operator= (const float* pArray);
	operator const float* ();

#endif // __cplusplus

} MYFLOAT4;

#define MYCOLOR _MYFLOAT4

#pragma warning(default:4201)