#include "StdAfx.h"
#include "YbkUtil.hpp"

CYbkMath::CYbkMath(void)
{
}


CYbkMath::~CYbkMath(void)
{
}

double CYbkMath::Round(double val, int precision, bool isFloor)
{
	if(precision==0)
		return (int)(val+0.5f);

	float s1 = (float)Pow(10, precision+1 );
	float s2 = s1/10.0f;
	float add_s = 1.0f/s1*5.0f;
	if( !isFloor )
		add_s = 0.0f;
	return ((int)((val+add_s)*s2 )/s2); 

}

int CYbkMath::BaseConv(char* v, int base)
{
	if(v == NULL)
		return -1;

	int len = strlen(v);
	if( len== 1 && v[0] == '0')
		return 0;

	int ret_OctVal = 0;
	int start_idx = 0;
	for(int i=0; i<len; ++i )
		if( v[i]!=' ')
		{
			start_idx = i;
			break;
		}

		if(v[len-1]>='a')
			ret_OctVal += (int(v[len-1]-'a')+10);
		else
			ret_OctVal += int(v[len-1]-'0');

		bool minus = false;
		if(v[start_idx] == '-')
		{
			minus = true;
			start_idx++;
		}

		for(int i=len-2, cnt=1; i>=start_idx; --i, ++cnt) // jump 1st
		{
			if( v[i] < 'a' ) // 0~9
			{
				// check value
//				int r = int(v[i]-'0');
//				int r1 = (Pow(base, cnt)*int(v[i]-'0') );

				ret_OctVal += (Pow(base, cnt)*int(v[i]-'0') );
			}
			else // a ~ ... (base count char)
			{
				// check value
//				int r = int(v[i]-'a')+10;
//				int r1 = (Pow(base, cnt)*(int(v[i]-'a')+10 ) );

				ret_OctVal += (Pow(base, cnt)*(int(v[i]-'a')+10 ) );
			}
		}

		if( minus )
			return ret_OctVal*(-1);

		return ret_OctVal;
}

int CYbkMath::GetOct(char* str, int base)
{
	del_delimiter(str);
	return BaseConv(str, base);

}

int CYbkMath::Pow(int val, int cnt=0)
{
	int ret_val = 1;
	if( cnt ==0 ) 
		return 1;
	 
	for( int i=1; i<=cnt; ++i)
	{
		ret_val *= val;
	}

	return ret_val;
}

int CYbkMath::IntToKoreanWord(int value, char* OutputNumString)
{
	if(NULL ==OutputNumString)
		return 1;

	char* num_string[]={"ÀÏ","ÀÌ","»ï","»ç","¿À","À°","Ä¥","ÆÈ","±¸"};
	char* unit_string[]={"½Ê","¹é","Ãµ","¸¸","½Ê","¹é","Ãµ","¾ï","½Ê","¹é","Ãµ"};

	// check value
//	char* str_num_temp[100]={0};
//	char* str_num[100]={0};
//	static string str="";
	string str="";

	for(int num_loc=1; ; ++num_loc )
	{
		int unit_num = 0;

		unit_num = value%Pow(10,num_loc);
		unit_num = unit_num/Pow(10,num_loc-1);
		if( unit_num == 0) 
			break;

		if( num_loc>1 )
		{
			str += unit_string[num_loc-2];
			if(unit_num-1>0)
				str += num_string[unit_num-1];
		}
		else
		{
			str += num_string[unit_num-1];
		}
	}

	// swap, 1/2 <-> 2/2
	int len = str.length();
	for(int first_loc=0, second_loc=len-1; first_loc<len/2; first_loc+=2)
	{
		char c = 0;
		c = str[first_loc];
		str[first_loc] = str[second_loc-first_loc-1];
		str[second_loc-first_loc-1] = c;
		c = str[first_loc+1];
		str[first_loc+1] = str[second_loc-first_loc];
		str[second_loc-first_loc] = c;
	}

//	return str.c_str();
//	OutputNumString = str.c_str();
	strcpy_s(OutputNumString, str.length(), str.c_str() );

	return 0;

}