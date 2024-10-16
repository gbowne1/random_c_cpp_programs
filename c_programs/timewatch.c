// File:   timewatch.c
// Author: Gregory K. Bowne
// Date:   14 SEPT 2024
// Time:   11:18:54
// Brief:  This is a program that will do a time thingy. 
// You'll need Windows or Linux for this, possibly even FreeBSD. Though if you use Windows
// You're on your own here. I tried to make this C90 ~ C99 at best.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#include <fcntl.h>
#endif

#define TIMER_DURATION 60 /* Timer duration in seconds */
#define MIN_GMT_OFFSET -12
#define MAX_GMT_OFFSET 14
#define MAX_FORMAT 3

static int gmt_offset = 0;
static int dst_active = 0;
static int time_format = 0;
static int hour_format = 24;

typedef enum {
    TIMER,
    STOPWATCH,
    CLOCK,
    EXIT
} Mode;

/* Function prototypes */
void clearScreen(void);
int kbhit(void);
void disableBuffering(void);
void enableBuffering(void);
void displayTime(int seconds);
void runTimer(void);
void runStopwatch(void);
void runClock(void);
#ifdef _WIN32
LARGE_INTEGER getFILETIMEoffset(void);
double getElapsedTime(LARGE_INTEGER *start, LARGE_INTEGER *end);
#endif

int main(void) {
    int choice;

    do {
        printf("1. Timer\n");
        printf("2. Stopwatch\n");
        printf("3. Clock\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            runTimer();
            break;
        case 2:
            runStopwatch();
            break;
        case 3:
            runClock();
            break;
        case 4:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break; // Add this line
    }
    } while (choice != 3);

    return 0;
}

void clearScreen(void) {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

int kbhit(void) {
    #ifdef _WIN32
    return _kbhit();
    #else
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv) > 0;
    #endif
}

void disableBuffering(void) {
    #ifndef _WIN32
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~ICANON;
    term.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &term);
    #endif
}

void enableBuffering(void) {
    #ifndef _WIN32
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    #endif
}

void displayTime(int seconds) {
   int hours = seconds / 3600;
    int remainder = seconds % 3600;
    int minutes = remainder / 60;
    int remaining_seconds = remainder % 60;

    printf("%02d:%02d:%02d", hours, minutes, remaining_seconds);
}

#ifdef _WIN32
LARGE_INTEGER getFILETIMEoffset(void) {
    SYSTEMTIME s;
    FILETIME f;
    LARGE_INTEGER t;

    s.wYear = 1970;
    s.wMonth = 1;
    s.wDay = 1;
    s.wHour = 0;
    s.wMinute = 0;
    s.wSecond = 0;
    s.wMilliseconds = 0;
    SystemTimeToFileTime(&s, &f);
    t.QuadPart = f.dwHighDateTime;
    t.QuadPart <<= 32;
    t.QuadPart |= f.dwLowDateTime;
    return t;
}

double getElapsedTime(LARGE_INTEGER *start, LARGE_INTEGER *end) {
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    return (double)(end->QuadPart - start->QuadPart) / (double)freq.QuadPart;
}
#endif

void runTimer(void) {
    int remainingTime = TIMER_DURATION;
    #ifdef _WIN32
    LARGE_INTEGER start, end, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    #else
    time_t startTime, currentTime;
    startTime = time(NULL);
    #endif

    clearScreen();
    printf("Timer started for %d seconds. Press any key to stop.\n", TIMER_DURATION);

    disableBuffering();

    while (remainingTime > 0 && !kbhit()) {
        clearScreen();
        printf("Time remaining: ");
        displayTime(remainingTime);
        printf("\nPress any key to stop.\n");

        #ifdef _WIN32
        Sleep(1000);
        QueryPerformanceCounter(&end);
        remainingTime = TIMER_DURATION - (int)getElapsedTime(&start, &end);
        #else
        sleep(1);
        currentTime = time(NULL);
        remainingTime = TIMER_DURATION - (int)difftime(currentTime, startTime);
        #endif
    }

    enableBuffering();
    clearScreen();
    printf("Timer finished!\n");
    getchar(); /* Clear the buffer */
    getchar(); /* Wait for user input */
}

void runStopwatch(void) {
    int elapsedTime = 0;
    #ifdef _WIN32
    LARGE_INTEGER start, end, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    #else
    time_t startTime, currentTime;
    startTime = time(NULL);
    #endif

    clearScreen();
    printf("Stopwatch started. Press any key to stop.\n");

    disableBuffering();

    while (!kbhit()) {
        clearScreen();
        printf("Elapsed time: ");
        displayTime(elapsedTime);
        printf("\nPress any key to stop.\n");

        #ifdef _WIN32
        Sleep(1000);
        QueryPerformanceCounter(&end);
        elapsedTime = (int)getElapsedTime(&start, &end);
        #else
        sleep(1);
        currentTime = time(NULL);
        elapsedTime = (int)difftime(currentTime, startTime);
        #endif
    }

    enableBuffering();
    clearScreen();
    printf("Stopwatch stopped!\n");
    printf("Final time: ");
    displayTime(elapsedTime);
    printf("\n");
    getchar(); /* Clear the buffer */
    getchar(); /* Wait for user input */
}

void setGMTOffset(void) {
    int new_offset;
    while (1) {
        printf("Enter GMT offset (-12 to +14): ");
        if (scanf("%d", &new_offset) == 1 && new_offset >= MIN_GMT_OFFSET && new_offset <= MAX_GMT_OFFSET) {
            gmt_offset = new_offset;
            break;
        } else {
            fprintf(stderr, "Invalid input. Please try again.\n");
            // Clear the input buffer
            while (getchar() != '\n');
        }
    }
}

void toggleDST(void) {
    dst_active = !dst_active;
    printf("Daylight Saving Time is now %s\n", dst_active ? "ON" : "OFF");
}

void toggleTimeFormat(void) {
    time_format = (time_format + 1) % (MAX_FORMAT + 1);
    printf("Time format changed.\n");
}

void toggleHourFormat(void) {
    hour_format = (hour_format == 12) ? 24 : 12;
    printf("Switched to %d-hour format.\n", hour_format);
}

void formatTime(char *buffer, size_t bufferSize, const struct tm *time_info) {
    static const char *formats[] = {"%Y-%m-%d ", "%d/%m/%Y ", "%m/%d/%Y ", "%a, %d %b %Y "};
    static const char *hour_formats[] = {"%H", "%I"};

    snprintf(buffer, bufferSize, formats[time_format], hour_format == 12 ? hour_formats[1] : hour_formats[0]);

    if (hour_format == 12) {
        strftime(buffer + strlen(buffer), bufferSize - strlen(buffer), hour_formats[0], time_info);
        snprintf(buffer + strlen(buffer), bufferSize - strlen(buffer), time_info->tm_hour >= 12 ? " PM" : " AM");
    } else {
        strftime(buffer + strlen(buffer), bufferSize - strlen(buffer), hour_formats[0], time_info);
    }
}

void runClock(void) {
    time_t rawtime;
    struct tm *local_time, gmt_time;
    char local_buffer[80];
    char gmt_buffer[80];
    int running = 1;

    clearScreen();
    printf("Clock started. Controls:\n");
    printf("'q': quit, 'o': set GMT offset, 'd': toggle DST\n");
    printf("'f': change time format, 'h': toggle 12/24 hour format\n");

    disableBuffering();

    while (running) {
        time(&rawtime);
        local_time = localtime(&rawtime);
        gmtime_r(&rawtime, &gmt_time);

        // Adjust GMT time based on user's offset and DST
        gmt_time.tm_hour += gmt_offset;
        if (dst_active) {
            gmt_time.tm_hour += 1;
        }
        mktime(&gmt_time); // Normalize the time

        formatTime(local_buffer, sizeof(local_buffer), local_time);
        formatTime(gmt_buffer, sizeof(gmt_buffer), &gmt_time);

        clearScreen();
        printf("Local Time: %s\n", local_buffer);
        printf("User GMT Time (GMT%+d%s): %s\n", gmt_offset, dst_active? " DST" : "", gmt_buffer);
        printf("\nControls: q(uit), o(ffset), d(st), f(ormat), h(our format)\n");

        #ifdef _WIN32
        Sleep(100);
        #else
        usleep(100000);
        #endif

        if (kbhit()) {
            char ch = getchar();
            switch (ch) {
                case 'q':
                    running = 0;
                    enableBuffering();
                    clearScreen();
                    printf("Exiting...\n");
                    return; // Exit the function
                case 'o':
                    setGMTOffset();
                    break;
                case 'd':
                    toggleDST();
                    break;
                case 'f':
                    toggleTimeFormat();
                    break;
                case 'h':
                    toggleHourFormat();
                    break;
            }
        }
    }

    enableBuffering();
    clearScreen();
    printf("Clock stopped!\n");
}

