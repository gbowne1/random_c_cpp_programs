#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <omp.h>
#include <math.h>

#define WIDTH 80
#define HEIGHT 40
#define MAX_ITER 1000
#define USE_COLOR 1

const char charset[] = " .:-=+*#%@";

/* Calculate Mandelbrot iteration count */
int mandelbrot(double real, double imag) {
    double r = 0.0, i = 0.0;
    int n;
    for (n = 0; n < MAX_ITER; n++) {
        double r2 = r * r;
        double i2 = i * i;
        if (r2 + i2 > 4.0) break;
        i = 2 * r * i + imag;
        r = r2 - i2 + real;
    }
    return n;
}

/* Draw Mandelbrot set with optional color and multithreading */
void draw_mandelbrot(double center_real, double center_imag, double scale, int use_color) {
    #pragma omp parallel for schedule(dynamic)
    for (int y = 0; y < HEIGHT; y++) {
        char line[WIDTH * 20] = "";  // Each line may include ANSI color codes
        int offset = 0;

        for (int x = 0; x < WIDTH; x++) {
            double real = center_real + (x - WIDTH / 2.0) * (scale * 2.0 / WIDTH);
            double imag = center_imag + (y - HEIGHT / 2.0) * (scale * 2.0 / HEIGHT);

            int n = mandelbrot(real, imag);
            int len = sizeof(charset) - 2;
            char c = (n == MAX_ITER) ? '#' : charset[n * len / MAX_ITER];

            if (use_color) {
                int color = 16 + (n * 215 / MAX_ITER);  // Map iteration count to 256-color palette
                offset += sprintf(&line[offset], "\033[38;5;%dm%c\033[0m", color, c);
            } else {
                offset += sprintf(&line[offset], "%c", c);
            }
        }

        printf("%s\n", line);
        fflush(stdout); // ensure line is printed right away
    }
}

/* Print usage instructions */
void print_usage(const char *progname) {
    fprintf(stderr, "Usage: %s [scale] [center_real] [center_imag] [animate]\n", progname);
    fprintf(stderr, "  scale         - Zoom scale (e.g., 2.0, 1.0, 0.5)\n");
    fprintf(stderr, "  center_real   - Real part of center (default: -0.5)\n");
    fprintf(stderr, "  center_imag   - Imaginary part of center (default: 0.0)\n");
    fprintf(stderr, "  animate       - 'yes' to zoom continuously (optional)\n");
}

/* Check if the output supports color */
int supports_color() {
    return isatty(fileno(stdout));
}

int main(int argc, char *argv[]) {
    double center_real = -0.5;
    double center_imag = 0.0;
    double scale = 2.0;
    int animate = 0;

    if (argc >= 2) scale = atof(argv[1]);
    if (argc >= 4) {
        center_real = atof(argv[2]);
        center_imag = atof(argv[3]);
    }
    if (argc == 5 && strcmp(argv[4], "yes") == 0) {
        animate = 1;
    }

    int use_color = USE_COLOR && supports_color();

    if (animate) {
        // Hide cursor and clear screen
        printf("\033[?25l\033[2J");
        for (double s = scale; s > 0.001; s *= 0.90) {
            printf("\033[H"); // Move cursor to top-left
            draw_mandelbrot(center_real, center_imag, s, use_color);
            usleep(100000); // 100ms between frames
        }
        printf("\033[?25h"); // Show cursor again
    } else {
        draw_mandelbrot(center_real, center_imag, scale, use_color);
    }

    return 0;
}
