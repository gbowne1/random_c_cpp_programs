// File:   winsize.cpp
// Author: Gregory K. Bowne
// Date:   06 Aug 2021
// Time:   13:46:22
// Brief:  This program calculates the console size

#include <iostream>
#include <limits>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <sys/ioctl.h>
#endif

void clearScreen()
{
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD screenPos = {0, 0};
    DWORD writtenChars;
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    FillConsoleOutputCharacter(hConsole, ' ', consoleInfo.dwSize.X * consoleInfo.dwSize.Y, screenPos, &writtenChars);
    SetConsoleCursorPosition(hConsole, screenPos);
#else
    std::cout << "\033[2J\033[1;1H"; // ANSI escape code to clear screen on Unix-like systems
#endif
}

int getConsoleWidth()
{
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
    return consoleInfo.dwSize.X;
#else
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return size.ws_col;
#endif
}

void setConsoleSize(int &width, int &height)
{
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
    width = consoleInfo.dwSize.X;
    height = consoleInfo.dwSize.Y;
#else

struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    width = size.ws_col;
    height = size.ws_row;
#endif
}

void printLineOfChars(const char character, const int length)
{
    for (int i = 0; i < length; i++)
    {
        std::cout << character;
    }
}

int main()
{
    int consoleWidth, consoleHeight;
    setConsoleSize(consoleWidth, consoleHeight);

    clearScreen();
    printLineOfChars('X', consoleWidth);  // Prints a line of 'X' characters with the console width

    std::cout << "\nWidth: " << consoleWidth << std::endl;
    std::cout << "Height: " << consoleHeight << std::endl;

    return 0;
}
