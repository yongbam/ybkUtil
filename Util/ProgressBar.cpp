#include "StdAfx.h"
#include "YbkUtil.hpp"

void CProgressBar::Start(char* header, int cnt)
{
	p_count = 1;
	before_count = 0;
	base_count = (float)cnt;

	printf("\t%s", header);
}
void CProgressBar::PrintBar()
{
	if( int(p_count/base_count*10.0f)%10 == before_count)
	{
		printf(".");
		before_count++;
	}
	p_count++;
}
void CProgressBar::End()
{
	printf(".ok\n");
}