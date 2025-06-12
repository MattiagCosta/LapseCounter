#include "LapseCounter.h"

void LapseCounterStart(LapseCounter* lapseCounter, ULONGLONG lapse){
	FILETIME lft;
	GetSystemTimeAsFileTime(&lft);
	lapseCounter->lt.LowPart = lft.dwLowDateTime;
	lapseCounter->lt.HighPart = lft.dwHighDateTime;

	lapseCounter->lapse = lapse;

	lapseCounter->previousLapseData.count = 0;
	lapseCounter->previousLapseData.timer = 0;

	lapseCounter->thisLapseData.count = 0;
	lapseCounter->thisLapseData.timer = 0;
}

int LapseCounterCall(LapseCounter* lapseCounter){
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);
	lapseCounter->t.LowPart = ft.dwLowDateTime;
	lapseCounter->t.HighPart = ft.dwHighDateTime;
	lapseCounter->thisLapseData.timer = lapseCounter->t.QuadPart-lapseCounter->lt.QuadPart;

	lapseCounter->thisLapseData.count++;

	if(lapseCounter->thisLapseData.timer>lapseCounter->lapse){
		lapseCounter->previousLapseData.timer = lapseCounter->thisLapseData.timer;
		lapseCounter->previousLapseData.count = lapseCounter->thisLapseData.count;
		lapseCounter->thisLapseData.count = 0;
		lapseCounter->lt.QuadPart = lapseCounter->t.QuadPart;
		return 1;
	}

	return 0;
}