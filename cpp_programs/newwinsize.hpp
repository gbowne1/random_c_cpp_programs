#ifndef _NEWWINSIZE_HPP_
#define _NEWWINSIZE_HPP_

#include <iostream>
#include <string>
#include <cstdlib>

// Platform-specific includes
#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#elif defined(__APPLE__) || defined(__FreeBSD__) || defined(__NetBSD__) || \
      defined(__OpenBSD__) || defined(__linux__) || defined(__sun) || defined(__sun__)
    #include <sys/ioctl.h>
    #include <unistd.h>
    #include <termios.h>
#endif

struct WindowSize {
    int width;
    int height;
    WindowSize(int w = 0, int h = 0) : width(w), height(h) {}
};

void clearScreen();
WindowSize getWindowSize();
void printLineOfX(int length);
void printBorder(const WindowSize& size);
void printCentered(const std::string& text, int width);
std::string getSystemInfo();

#endif // _NEWWINSIZE_HPP_