#include <iostream>
#include <limits>
#include <sys/ioctl.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD screenPos = {0, 0};
    DWORD writtenChars;
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    FillConsoleOutputCharacter(hConsole, ' ', consoleInfo.dwSize.X * consoleInfo.dwSize.Y, screenPos, &writtenChars);
    SetConsoleCursorPosition(hConsole, screenPos);
}

#else
#include <unistd.h> // for POSIX systems

void clearScreen()
{
    std::cout << "\033[2J\033[1;1H";
}
#endif

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
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    width = size.ws_col;
    height = size.ws_row;
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
    printLineOfChars('X', consoleWidth);

    std::cout << "\nWidth: " << consoleWidth << std::endl;
    std::cout << "Height: " << consoleHeight << std::endl;

    return 0;
}
