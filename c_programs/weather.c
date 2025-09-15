/*
 * weather.c - Terminal Weather Station Simulator (C99)
 *
 * Compile:
 * gcc -std=c99 -Wall -Wextra -Werror -pedantic -O2 -o weather weather.c
 *
 * Usage:
 * ./weather
 *
 * Logs go to ./logs/weather_YYYY-MM-DD.csv
 */

#include <assert.h>
#include <complex.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#endif

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

/* Constants */
#define HISTORY_SIZE 60 /* minutes */
#define LOG_DIR "logs"

/* Weather reading struct */
typedef struct {
    double temperature;    /* °C */
    int humidity;          /* % */
    double wind_speed;     /* km/h */
    double wind_dir_deg;   /* degrees 0-359 */
    double complex wind_vec; /* complex wind vector */
    time_t timestamp;      /* epoch time */
} WeatherReading;

/* Circular buffer for storing weather readings */
typedef struct {
    WeatherReading readings[HISTORY_SIZE];
    size_t start;  /* index of oldest */
    size_t count;  /* how many stored (max HISTORY_SIZE) */
} WeatherHistory;

/* Function Prototypes */
static void init_history(WeatherHistory *hist);
static void add_reading(WeatherHistory *hist, WeatherReading reading);
static void compute_stats(const WeatherHistory *hist, double *min_temp, double *max_temp, double *avg_temp);
static WeatherReading generate_reading(void);
static void print_reading(const WeatherReading *r);
static void print_stats(const WeatherHistory *hist);
static void log_reading_csv(const WeatherReading *r);
static void create_log_dir_if_needed(void);
static void sleep_seconds(unsigned int seconds);

/* --- Implementation --- */

/* Initialize empty history */
static void init_history(WeatherHistory *hist) {
    assert(hist != NULL);
    hist->start = 0;
    hist->count = 0;
    memset(hist->readings, 0, sizeof(hist->readings));
}

/* Add reading to circular buffer */
static void add_reading(WeatherHistory *hist, WeatherReading reading) {
    assert(hist != NULL);
    size_t idx = (hist->start + hist->count) % HISTORY_SIZE;
    if (hist->count < HISTORY_SIZE) {
        hist->readings[idx] = reading;
        hist->count++;
    } else {
        /* Buffer full, overwrite oldest */
        hist->readings[hist->start] = reading;
        hist->start = (hist->start + 1) % HISTORY_SIZE;
    }
}

/* Compute min, max, avg temperature over history */
static void compute_stats(const WeatherHistory *hist, double *min_temp, double *max_temp, double *avg_temp) {
    assert(hist != NULL && min_temp != NULL && max_temp != NULL && avg_temp != NULL);
    if (hist->count == 0) {
        *min_temp = NAN;
        *max_temp = NAN;
        *avg_temp = NAN;
        return;
    }

    double minv = DBL_MAX;
    double maxv = -DBL_MAX;
    double sum = 0.0;
    size_t i;

    for (i = 0; i < hist->count; i++) {
        size_t idx = (hist->start + i) % HISTORY_SIZE;
        double t = hist->readings[idx].temperature;
        if (t < minv) minv = t;
        if (t > maxv) maxv = t;
        sum += t;
    }

    *min_temp = minv;
    *max_temp = maxv;
    *avg_temp = sum / (double)hist->count;
}

/* Generate a new random weather reading */
static WeatherReading generate_reading(void) {
    WeatherReading r;

    /* Generate temperature between 15.0 and 30.0 °C with some noise */
    r.temperature = 15.0 + (rand() / (double)RAND_MAX) * 15.0;

    /* Humidity between 30% and 70% */
    r.humidity = 30 + rand() % 41;

    /* Wind speed between 0 and 20 km/h */
    r.wind_speed = (rand() / (double)RAND_MAX) * 20.0;

    /* Wind direction degrees 0-359 */
    r.wind_dir_deg = (double)(rand() % 360);

    /* Wind vector as complex number */
    double rad = r.wind_dir_deg * (M_PI / 180.0);
    r.wind_vec = r.wind_speed * (cos(rad) + sin(rad) * I);

    r.timestamp = time(NULL);

    return r;
}

/* Print one reading to stdout */
static void print_reading(const WeatherReading *r) {
    assert(r != NULL);

    struct tm tm_local;
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&tm_local, &r->timestamp);
#else
    localtime_r(&r->timestamp, &tm_local);
#endif

    printf("[%02d:%02d:%02d] Temp: %.1f°C | Humidity: %d%% | Wind: %.1f km/h %s\n",
           tm_local.tm_hour, tm_local.tm_min, tm_local.tm_sec,
           r->temperature, r->humidity, r->wind_speed,
           (r->wind_dir_deg >= 0 && r->wind_dir_deg < 45) ? "N" :
           (r->wind_dir_deg < 90) ? "NE" :
           (r->wind_dir_deg < 135) ? "E" :
           (r->wind_dir_deg < 180) ? "SE" :
           (r->wind_dir_deg < 225) ? "S" :
           (r->wind_dir_deg < 270) ? "SW" :
           (r->wind_dir_deg < 315) ? "W" : "NW");

    printf("           Wind Vector: %.1f ∠ %.0f° → (%.2f %c %.2fi)\n",
           r->wind_speed, r->wind_dir_deg,
           creal(r->wind_vec),
           (cimag(r->wind_vec) < 0.0) ? '-' : '+',
           fabs(cimag(r->wind_vec)));
}

/* Print stats summary */
static void print_stats(const WeatherHistory *hist) {
    assert(hist != NULL);

    double min_temp, max_temp, avg_temp;
    compute_stats(hist, &min_temp, &max_temp, &avg_temp);

    if (hist->count == 0) {
        printf("Stats (Last 60 min): No data\n");
    } else {
        printf("Stats (Last 60 min): Temp Min: %.1f | Max: %.1f | Avg: %.1f\n",
               min_temp, max_temp, avg_temp);
    }
}

/* Create logs directory if missing */
static void create_log_dir_if_needed(void) {
#if defined(_WIN32) || defined(_WIN64)
    int ret = _mkdir(LOG_DIR);
#else
    int ret = mkdir(LOG_DIR, 0755);
#endif
    if (ret != 0 && errno != EEXIST) {
        fprintf(stderr, "Error: Cannot create log directory '%s': %s\n", LOG_DIR, strerror(errno));
        exit(EXIT_FAILURE);
    }
}

/* Log one reading to CSV file named by current date */
static void log_reading_csv(const WeatherReading *r) {
    assert(r != NULL);

    /* Get local date */
    struct tm tm_local;
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&tm_local, &r->timestamp);
#else
    localtime_r(&r->timestamp, &tm_local);
#endif

    char filename[256];
    snprintf(filename, sizeof(filename), LOG_DIR"/weather_%04d-%02d-%02d.csv",
             tm_local.tm_year + 1900, tm_local.tm_mon + 1, tm_local.tm_mday);

    bool file_exists = false;

    FILE *f = fopen(filename, "r");
    if (f != NULL) {
        file_exists = true;
        fclose(f);
    }

    f = fopen(filename, "a");
    if (f == NULL) {
        fprintf(stderr, "Error: Cannot open log file '%s' for append: %s\n", filename, strerror(errno));
        return;
    }

    if (!file_exists) {
        /* Write CSV header */
        fprintf(f, "Timestamp,Temperature_C,Humidity_pct,WindSpeed_kmh,WindDir_deg,WindVec_real,WindVec_imag\n");
    }

    /* Format timestamp as ISO8601 */
    char timestamp_str[32];
    strftime(timestamp_str, sizeof(timestamp_str), "%Y-%m-%dT%H:%M:%S", &tm_local);

    fprintf(f, "%s,%.2f,%d,%.2f,%.0f,%.2f,%.2f\n",
            timestamp_str, r->temperature, r->humidity, r->wind_speed,
            r->wind_dir_deg, creal(r->wind_vec), cimag(r->wind_vec));

    fclose(f);
}

/* Portable sleep for seconds */
static void sleep_seconds(unsigned int seconds) {
#if defined(_WIN32) || defined(_WIN64)
    Sleep(seconds * 1000);
#else
    sleep(seconds);
#endif
}

/* Main simulation loop */
int main(void) {
    srand((unsigned int)time(NULL));

    WeatherHistory history;
    init_history(&history);
    create_log_dir_if_needed();

    printf("Terminal Weather Station Simulator\n");
    printf("Press Ctrl+C to quit.\n\n");

    for (;;) {
        WeatherReading r = generate_reading();
        add_reading(&history, r);

        print_reading(&r);
        print_stats(&history);
        printf("Alerts: None\n");
        printf("Logged to: %s/weather_%04d-%02d-%02d.csv\n\n",
               LOG_DIR,
               localtime(&r.timestamp)->tm_year + 1900,
               localtime(&r.timestamp)->tm_mon + 1,
               localtime(&r.timestamp)->tm_mday);

        log_reading_csv(&r);

        sleep_seconds(1); /* 1 second per simulated minute */
    }

    return 0;
}
