// File:   time.c
// Author: Gregory K. Bowne
// Date:   22 NOV 2023
// Time:   11:53:21
// Brief:  This program just displays the current system time and date.

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    time_t t = time(NULL);
    struct tm* lt = localtime (&t);

    printf("System's current date\n");
    printf("%d/%d/%d\n",
           lt->tm_mday,
           lt->tm_mon + 1,
           lt->tm_year + 1900);
    printf ("The time is %s\n", asctime (lt));
    return 0;

}