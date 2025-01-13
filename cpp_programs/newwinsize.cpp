// File: newwinsize.cpp
// Author: Extended from Gregory K. Bowne's original winsize.cpp
// Date: December 23, 2024
// Brief: Implementation of terminal size detection and border drawing

#include "newwinsize.hpp"
#include <stdexcept>

void clearScreen() {
    #if defined(_WIN32) || defined(_WIN64)
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD screenPos = {0, 0};
        DWORD writtenChars;
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        if (GetConsoleScreenBufferInfo(hConsole, &consoleInfo)) {
            FillConsoleOutputCharacter(hConsole, ' ', 
                consoleInfo.dwSize.X * consoleInfo.dwSize.Y, screenPos, &writtenChars);
            SetConsoleCursorPosition(hConsole, screenPos);
        }
    #else
        std::cout << "\033[2J\033[1;1H" << std::flush;
    #endif
}

WindowSize getWindowSize() {
    WindowSize size;

    #if defined(_WIN32) || defined(_WIN64)
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            size.width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            size.height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        }
    #elif defined(__APPLE__) || defined(__FreeBSD__) || defined(__NetBSD__) || \
          defined(__OpenBSD__) || defined(__linux__) || defined(__sun) || defined(__sun__)
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
    #if defined(_WIN32) || defined(_WIN64)
        #ifdef _WIN64
            platform = "Windows 64-bit";
        #else
            platform = "Windows 32-bit";
        #endif
    #elif defined(__APPLE__)
        platform = "Apple/Darwin/OSX";
    #elif defined(__FreeBSD__)
        platform = "FreeBSD";
    #elif defined(__NetBSD__)
        platform = "NetBSD";
    #elif defined(__OpenBSD__)
        platform = "OpenBSD";
    #elif defined(__sun) || defined(__sun__)
        platform = "Solaris/SunOS";
    #elif defined(__linux__)
        platform = "Linux";
    #else
        platform = "Unknown Platform";
    #endif

    #if defined(__x86_64__) || defined(_M_X64)
        platform += " (64-bit x86)";
    #elif defined(__aarch64__)
        platform += " (64-bit ARM)";
    #elif defined(__arm__)
        platform += " (32-bit ARM)";
    #elif defined(__i386) || defined(_M_IX86)
        platform += " (32-bit x86)";
    #endif

    return platform;
}

int main() {
    try {
        clearScreen();
        
        auto size = getWindowSize();
        printBorder(size);
        
        // Calculate center position for text
        int centerY = size.height / 2;
        int currentLine = 1;
        
        // Move to desired position for text
        while (currentLine < centerY - 2) {
            currentLine++;
            std::cout << "X";
            for (int i = 0; i < size.width - 2; i++) std::cout << " ";
            std::cout << "X\n";
        }
        
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
        while (currentLine < size.height - 1) {
            currentLine++;
            std::cout << "X";
            for (int i = 0; i < size.width - 2; i++) std::cout << " ";
            std::cout << "X\n";
        }
        
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}