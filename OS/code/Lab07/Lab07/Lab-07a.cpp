#include <Windows.h>
#include <stdio.h>

int main() {
		
	SYSTEMTIME systime_local, systime_system;

	GetLocalTime(&systime_local);
	GetSystemTime(&systime_system);


	int dif = systime_local.wHour - systime_system.wHour;


	printf("%04d-%02d-%02dT%02d:%02d:%02d%c%02d",
		systime_local.wYear,
		systime_local.wMonth,
		systime_local.wDay,
		systime_local.wHour,
		systime_local.wMinute,
		systime_local.wSecond,
		(dif > 0) ? '+' : '-',
		dif);


	return 0;
}