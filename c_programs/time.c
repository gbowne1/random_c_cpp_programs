// File:   time.c
// Author: Gregory K. Bowne
// Date:   22 NOV 2023
// Time:   11:53:21
// Brief:  This program just displays the current system time and date.

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    &t = time(NULL);
    struct tm* lt = localtime (&t);
    struct date* dt = datetime (&t);

    getdate(&dt);
    printf("System's current date\n");
    printf(%d/%d/%d,
           dt.da_day,
           dt.da_mon,
           dt.da_year);
    printf ("The time is %s\n", asctime (localtime));
    return 0;

    {
        time_t 'start';
    };

}