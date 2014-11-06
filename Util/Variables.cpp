#include "StdAfx.h"
#include "Variables.hpp"

///////////////////////////////////////////////////////////////////////////
// _MATRIX

_MATRIX::_MATRIX( FLOAT _f11, FLOAT _f12, FLOAT _f13, FLOAT _f14,
	FLOAT _f21, FLOAT _f22, FLOAT _f23, FLOAT _f24,
	FLOAT _f31, FLOAT _f32, FLOAT _f33, FLOAT _f34,
	FLOAT _f41, FLOAT _f42, FLOAT _f43, FLOAT _f44 )
{
	_f11 = 0;
	_f12 = 0;
	_f13 = 0;
	_f14 = 0;
	_f21 = 0;
	_f22 = 0;
	_f23 = 0;
	_f24 = 0;
	_f31 = 0;
	_f32 = 0;
	_f33 = 0;
	_f34 = 0;
	_f41 = 0;
	_f42 = 0;
	_f43 = 0;
	_f44 = 0;
	
}

_MATRIX::_MATRIX()
{
	memset((char*)_m, 0, sizeof(float)*16);
}

_MATRIX::_MATRIX(const float* pArray)
{
	memcpy( _m, pArray, sizeof(float)*16);
}

_MATRIX::_MATRIX( FLOAT _f11, FLOAT _f22, FLOAT _f33, FLOAT _f44)
{
	for(int i=0; i<4; ++i)
		for( int j=0; j<4; ++j)
			_m[i][j]=0;

	_m[0][0]=_f11;
	_m[1][1]=_f22;
	_m[2][2]=_f33;
	_m[3][3]=_f44;
}

int _MATRIX::ToString(const char* name, char* OutputString)
{
	if(NULL == OutputString)
		return 1;

	char buf[16];
	memset((char*)buf, 0, sizeof(char)*16);
	string _s="";

	_s+="mat";
	_s+="|";
	errno_t err = _itoa_s(16, buf, 16, 10);
	if( 0 != err )
		return err;
	
	_s+=buf;
	_s+="|";
	_s+=name;

	for(int i=0; i<4; ++i)
		for(int j=0; j<4; ++j)
		{
			_s+="|";
			if(abs(_m[i][j])<0.000001f)
				_s+="0";
			else
			{
				memset((char*)buf, 0, sizeof(char)*16 );
				sprintf_s(buf, 16, "%f", _m[i][j]);
				// buf 에서 뒤의 필요없는 0 제거
				for(int l=15; l>0; --l)
				{
					if( buf[l]>48) 
						break;
					// 48 == '0'
					if(buf[l]==48) 
						buf[l]=0;
				}

				_s+=buf;

			}

		}
	_s+="|";

//	return _s.c_str();
	strcpy_s(OutputString, _s.length(), _s.c_str() );

	return 0;

}

const char* _MATRIX::operator=(_MATRIX&) const
{
	return "";
}

void _MATRIX::operator=(const float* pArray)
{
	memcpy( _m, pArray, sizeof(float)*16);
}

void _MATRIX::operator=(float* pArray)
{
	memcpy( _m, pArray, sizeof(float)*16);
}

void _MATRIX::operator=(float m[4][4])
{
	memcpy( _m, m, sizeof(float)*16);

}

///////////////////////////////////////////////////////////////////////////
// _MYFLOAT2

_MYFLOAT2::_MYFLOAT2(const FLOAT* pArray)
{
	for( int i=0; i<2; ++i)
		f[i]=pArray[i];
}

_MYFLOAT2& _MYFLOAT2::operator= (const FLOAT* pArray)
{
	for(int i=0; i<2; ++i)
		this->f[i]=pArray[i];

	return *this;
}

_MYFLOAT2& _MYFLOAT2::operator= (const _MYFLOAT2& pArray)
{
	this->x = pArray.x;
	this->y = pArray.y;

	return *this;
}

///////////////////////////////////////////////////////////////////////////
// _MYFLOAT3

_MYFLOAT3::_MYFLOAT3(const float* pArray)
{
	for( int i=0; i<3; ++i)
		f[i]=pArray[i];
}

_MYFLOAT3& _MYFLOAT3::operator= (const float* pArray)
{
	for(int i=0; i<3; ++i)
		this->f[i]=pArray[i];

	return *this;
}

_MYFLOAT3& _MYFLOAT3::operator= (const _MYFLOAT3& pArray)
{
	this->x = pArray.x;
	this->y = pArray.y;
	this->z = pArray.z;

	return *this;
}

_MYFLOAT3 _MYFLOAT3::operator+ (const _MYFLOAT3& pArray)
{

	_MYFLOAT3 temp;
	temp.x = this->x + pArray.x;
	temp.y = this->y + pArray.y;
	temp.z = this->z + pArray.z;

	return temp;
}
_MYFLOAT3& _MYFLOAT3::operator+= (const _MYFLOAT3& pArray)
{
	this->x = this->x + pArray.x;
	this->y = this->y + pArray.y;
	this->z = this->z + pArray.z;

	return *this;
}

_MYFLOAT3 _MYFLOAT3::operator/ (const _MYFLOAT3& pArray)
{
	_MYFLOAT3 temp;
	temp.x = this->x + pArray.x;
	temp.y = this->y + pArray.y;
	temp.z = this->z + pArray.z;

	return temp;
}

_MYFLOAT3 _MYFLOAT3::operator/ (const float& value)
{
	_MYFLOAT3 temp;
	temp.x = this->x / value;
	temp.y = this->y / value;
	temp.z = this->z / value;

	return temp;
}

_MYFLOAT3 _MYFLOAT3::operator- (const _MYFLOAT3& pArray)
{
	_MYFLOAT3 temp;
	temp.x = this->x - pArray.x;
	temp.y = this->y - pArray.y;
	temp.z = this->z - pArray.z;

	return temp;
}

///////////////////////////////////////////////////////////////////////////
// _MYFLOAT4

_MYFLOAT4::_MYFLOAT4(const float *pArray)
{
	for(int i=0; i<4; ++i)
		f[i]=pArray[i];
}

_MYFLOAT4& _MYFLOAT4::operator= (const float* pArray)
{
	for(int i=0; i<4; ++i)
		this->f[i]=pArray[i];

	return *this;
}
_MYFLOAT4::operator const float* ()
{
	return f;
}