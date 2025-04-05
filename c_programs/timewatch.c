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

const int SECONDS_IN_A_MINUTE = 60;
const int SECONDS_IN_AN_HOUR = 3600;
const int DAYS_IN_A_YEAR = 365;
const int DAYS_IN_A_MONTH = 30; // Approximation
const int DAYS_IN_A_WEEK = 7;

static int time_format = 0;
static int hour_format = 24; 

// Global settings
typedef struct {
    int gmt_offset;
    int dst_active;
    int time_format;
    int hour_format;
} TimeSettings;

static TimeSettings settings = {0, 0, 0, 24};

// Function prototypes
void clearScreen(void);
int kbhit(void);
void disableBuffering(void);
void enableBuffering(void);
void displayTime(int seconds);
void runTimer(void);
void runStopwatch(void);
void runClock(void);
void decipherUnixTimestamp(void);
void convertSeconds(void);
void setGMTOffset(void);
void toggleDST(void);
void toggleTimeFormat(void);
void toggleHourFormat(void);
void formatTime(char *buffer, size_t bufferSize, const struct tm *time_info);

#ifdef _WIN32
LARGE_INTEGER getFILETIMEoffset(void);
double getElapsedTime(LARGE_INTEGER *start, LARGE_INTEGER *end);
#endif

int main(void) {
    int choice;

    while (1) {
        printf("1. Timer\n2. Stopwatch\n3. Clock\n4. Decipher Unix Timestamp\n5. Convert Seconds\n6. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        switch (choice) {
            case 1: runTimer(); break;
            case 2: runStopwatch(); break;
            case 3: runClock(); break;
            case 4: decipherUnixTimestamp(); break;
            case 5: convertSeconds(); break;
            case 6: 
                printf("Exiting...\n"); 
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
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
    FD_SET(STDIN_FILENO, &fds);
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int result = select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return result > 0;
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
    int hours = seconds / SECONDS_IN_AN_HOUR;
    int remainder = seconds % SECONDS_IN_AN_HOUR;
    int minutes = remainder / SECONDS_IN_A_MINUTE;
    int remaining_seconds = remainder % SECONDS_IN_A_MINUTE;

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
            settings.gmt_offset = new_offset;
            break;
        } else {
            fprintf(stderr, "Invalid input. Please try again.\n");
            while (getchar() != '\n'); // Clear the input buffer
        }
    }
}

void toggleDST(void) {
    settings.dst_active = !settings.dst_active;
    printf("Daylight Saving Time is now %s\n", settings.dst_active ? "ON" : "OFF");
}

void toggleTimeFormat(void) {
    settings.time_format = (settings.time_format + 1) % (MAX_FORMAT + 1);
    printf("Time format changed.\n");
}

void toggleHourFormat(void) {
    settings.hour_format = (settings.hour_format == 12) ? 24 : 12;
    printf("Switched to %d-hour format.\n", settings.hour_format);
}

void formatTime(char *buffer, size_t bufferSize, const struct tm *time_info) {
    static const char *formats[] = {"%Y-%m-%d ", "%d/%m/%Y ", "%m/%d/%Y ", "%a, %d %b %Y "};
    static const char *hour_formats[] = {"%H:%M:%S", "%I:%M:%S"};

    // Format the date
    strftime(buffer, bufferSize, formats[time_format], time_info);
    
    // Append the time
    strftime(buffer + strlen(buffer), bufferSize - strlen(buffer), hour_formats[hour_format == 12 ? 1 : 0], time_info);

    // Append AM/PM if using 12-hour format
    if (hour_format == 12) {
        snprintf(buffer + strlen(buffer), bufferSize - strlen(buffer), time_info->tm_hour >= 12 ? " PM" : " AM");
    }
}

void decipherUnixTimestamp(void) {
    time_t timestamp;
    struct tm *tm_info;
    char buffer[80];

    printf("Enter a Unix timestamp: ");
    if (scanf("%ld", &timestamp) != 1) {
        fprintf(stderr, "Invalid input. Please enter a valid timestamp.\n");
        while (getchar() != '\n'); // Clear the input buffer
        return;
    }

    // Check for reasonable range of timestamps
    if (timestamp < 0 || timestamp > 253402300799) { // 253402300799 is the max for 32-bit time_t
        fprintf(stderr, "Timestamp out of valid range.\n");
        return;
    }

    tm_info = gmtime(&timestamp);
    if (tm_info == NULL) {
        fprintf(stderr, "Error converting timestamp.\n");
        return;
    }

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("The corresponding date and time is: %s UTC\n", buffer);
}

void convertSeconds(void) {
    long total_seconds;
    printf("Enter the number of seconds: ");
    if (scanf("%ld", &total_seconds) != 1) {
        fprintf(stderr, "Invalid input. Please enter a valid number of seconds.\n");
        while (getchar() != '\n'); // Clear the input buffer
        return;
    }

    int years = total_seconds / (DAYS_IN_A_YEAR * SECONDS_IN_AN_HOUR * 24);
    total_seconds %= (DAYS_IN_A_YEAR * SECONDS_IN_AN_HOUR * 24);
    int months = total_seconds / (DAYS_IN_A_MONTH * SECONDS_IN_AN_HOUR * 24); // Approximation
    total_seconds %= (DAYS_IN_A_MONTH * SECONDS_IN_AN_HOUR * 24);
    int weeks = total_seconds / (DAYS_IN_A_WEEK * SECONDS_IN_AN_HOUR * 24);
    total_seconds %= (DAYS_IN_A_WEEK * SECONDS_IN_AN_HOUR * 24);
    int days = total_seconds / (SECONDS_IN_AN_HOUR * 24);
    total_seconds %= (SECONDS_IN_AN_HOUR * 24);
    int hours = total_seconds / SECONDS_IN_AN_HOUR;
    total_seconds %= SECONDS_IN_AN_HOUR;
    int minutes = total_seconds / SECONDS_IN_A_MINUTE;
    int seconds = total_seconds % SECONDS_IN_A_MINUTE;

    printf("The time corresponds to: %d years, %d months, %d weeks, %d days, %d hours, %d minutes, %d seconds\n",
           years, months, weeks, days, hours, minutes, seconds);
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
        gmt_time = *gmtime(&rawtime);

        // Adjust GMT time based on user's offset and DST
        gmt_time.tm_hour += settings.gmt_offset;
        if (settings.dst_active) {
            gmt_time.tm_hour += 1;
        }
        mktime(&gmt_time); // Normalize the time

        formatTime(local_buffer, sizeof(local_buffer), local_time);
        formatTime(gmt_buffer, sizeof(gmt_buffer), &gmt_time);

        clearScreen();
        printf("Local Time: %s\n", local_buffer);
        printf("User GMT Time (GMT%+d%s): %s\n", settings.gmt_offset, settings.dst_active ? " DST" : "", gmt_buffer);
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
                default:
                    printf("Invalid input. Try again.\n");
            }
        }
    }

    enableBuffering();
    clearScreen();
    printf("Clock stopped!\n");
}
