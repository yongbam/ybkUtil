#include "StdAfx.h"
#include "YbkUtil.hpp"

CMyTimer::CMyTimer(void)
{
	countsPerSecond = 0.0;
	CounterStart = 0;
	frameCount = 0;
	fps = 0;
	frameTimeOld = 0;
	frameTime;

}

CMyTimer::~CMyTimer(void)
{
}

int CMyTimer::CheckStart()
{
	return StartTimer();
}

// ex 5312.53213
int CMyTimer::CheckEnd(int& hour, 
	int& minute, int& second, 
	double& nano_second)
{
	CYbkMath math;
	double sec = GetTime();
	double s1 = math.Round(sec, 0, false);
	int ns_s = math.Pow(10, 4);

	second = (int)(s1/60.0f*100.0f)%100; // 5312.0
	minute = (int)(s1/60.0f)%60;
	hour = (int)(s1/60.0f)/60%60;
	nano_second = ((int)(math.Round(sec, 5, false)*ns_s)%ns_s)
		/(float)(ns_s/100.0f); // 531.2

	return 0;

}

int CMyTimer::StartTimer()
{
	LARGE_INTEGER frequencyCount;
	QueryPerformanceFrequency(&frequencyCount);

	countsPerSecond = double(frequencyCount.QuadPart);

	QueryPerformanceCounter(&frequencyCount);
	CounterStart = frequencyCount.QuadPart;

	return 0;
}

double CMyTimer::GetTime()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	return double(currentTime.QuadPart-CounterStart)/countsPerSecond;
}

double CMyTimer::GetFrameTime()
{
	LARGE_INTEGER currentTime;
	__int64 tickCount;
	QueryPerformanceCounter(&currentTime);

	tickCount = currentTime.QuadPart-frameTimeOld;
	frameTimeOld = currentTime.QuadPart;

	if(tickCount < 0)
		tickCount = 0;

	return float(tickCount)/countsPerSecond;
}

int CMyTimer::AddFrameCounter()
{
	frameCount++;
	return 0;
}

int CMyTimer::SetFrameCounter()
{
	SetFps(); 
	frameCount=0;
	return 0;
}

int CMyTimer::SetFps()
{
	fps = frameCount;
	return 0;
}

int CMyTimer::GetFps()
{
	return fps;
	return 0;
}