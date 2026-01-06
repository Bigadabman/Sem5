#include <stdio.h>
#include <time.h>

int main()
{
    time_t now;
    struct tm tm_local;
    struct tm tm_utc;

    time(&now);

    localtime_r(&now, &tm_local);

    gmtime_r(&now, &tm_utc);

    int dif = tm_local.tm_hour - tm_utc.tm_hour;

    //if (dif > 12)
    //    dif -= 24;
    //else if (dif < -12)
    //    dif += 24;

    printf("%04d-%02d-%02dT%02d:%02d:%02d%c%02d\n",
        tm_local.tm_year + 1900,
        tm_local.tm_mon + 1,
        tm_local.tm_mday,
        tm_local.tm_hour,
        tm_local.tm_min,
        tm_local.tm_sec,
        (dif >= 0) ? '+' : '-',
        (dif >= 0) ? dif : -dif
    );

    return 0;
}
