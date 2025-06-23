// File: combined_winsize.cpp
// Author: Gregory K. Bowne (extended)
// Date: June 22, 2025
// Brief: This program calculates the console size, clears the screen, and displays a border with system information.

#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>

// Platform-specific includes
#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

struct WindowSize {
    int width;
    int height;
    WindowSize(int w = 0, int h = 0) : width(w), height(h) {}
};

void clearScreen() {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD screenPos = {0, 0};
    DWORD writtenChars;
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    if (GetConsoleScreenBufferInfo(hConsole, &consoleInfo)) {
        FillConsoleOutputCharacter(hConsole, ' ', consoleInfo.dwSize.X * consoleInfo.dwSize.Y, screenPos, &writtenChars);
        SetConsoleCursorPosition(hConsole, screenPos);
    }
#else
    std::cout << "\033[2J\033[1;1H" << std::flush; // ANSI escape code to clear screen on Unix-like systems
#endif
}

WindowSize getWindowSize() {
    WindowSize size;

#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        size.width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        size.height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
#else
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        size.width = w.ws_col;
        size.height = w.ws_row;
    }
#endif

    if (size.width <= 0) size.width = 80;
    if (size.height <= 0) size.height = 24;

    return size;
}

void printLineOfX(int length) {
    if (length <= 0) return;
    std::string line(static_cast<std::string::size_type>(length), 'X');
    std::cout << line;
}

void printBorder(const WindowSize& size) {
    // Top border
    printLineOfX(size.width);
    std::cout << '\n';
    
    // Middle section with side borders
    for (int i = 0; i < size.height - 2; i++) {
        std::cout << "X";
        for (int j = 0; j < size.width - 2; j++) {
            std::cout << " ";
        }
        std::cout << "X\n";
    }
    
    // Bottom border
    printLineOfX(size.width);
    std::cout << '\n';
}

void printCentered(const std::string& text, int width) {
    std::cout << "X";
    int padding = (width - 2 - static_cast<int>(text.length())) / 2;
    for (int i = 0; i < padding; i++) std::cout << " ";
    std::cout << text;
    int remaining = width - 2 - padding - static_cast<int>(text.length());
    for (int i = 0; i < remaining; i++) std::cout << " ";
    std::cout << "X\n";
}

std::string getSystemInfo() {
    std::string platform;
#ifdef _WIN32
    #ifdef _WIN64
        platform = "Windows 64-bit";
    #else
        platform = "Windows 32-bit";
    #endif
#elif defined(__APPLE__)
    platform = "Apple/Darwin/OSX";
#elif defined(__linux__)
    platform = "Linux";
#else
    platform = "Unknown Platform";
#endif

    return platform;
}

int main() {
    try {
        clearScreen();
        
        auto size = getWindowSize();
        printBorder(size);
        
        // Print information
        std::string info = "Window Information:";
        std::string width = "Width: " + std::to_string(size.width);
        std::string height = "Height: " + std::to_string(size.height);
        std::string system = "System: " + getSystemInfo();
        
        printCentered(info, size.width);
        printCentered(width, size.width);
        printCentered(height, size.width);
        printCentered(system, size.width);
        
        // Fill remaining space
        for (int i = 0; i < size.height - 4; i++) { // -4 to account for the borders and info lines
            std::cout << "X";
            for (int j = 0; j < size.width - 2; j++) {
                std::cout << " ";
            }
            std::cout << "X\n";
        }
        
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
