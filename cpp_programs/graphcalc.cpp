#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#endif
#else
#include <unistd.h>
#include <sys/ioctl.h>
#endif

#define COLOR_RESET   "\033[0m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_WHITE   "\033[37m"
#define COLOR_GRAY    "\033[90m"

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void enableAnsiOnWindows() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= 0x0004;
    SetConsoleMode(hOut, dwMode);
#endif
}

void getTerminalSize(int &width, int &height) {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    width = w.ws_col;
    height = w.ws_row;
#endif
}

double evaluateFunction(const std::string &expr, double x) {
    if (expr == "sin(x)") return sin(x);
    if (expr == "cos(x)") return cos(x);
    if (expr == "x^2")    return x * x;
    if (expr == "x")      return x;
    return 0.0;
}

void plotGraph(const std::string &expression) {
    int termWidth, termHeight;
    getTerminalSize(termWidth, termHeight);

    int graphWidth = termWidth - 8;  // Leave space for Y-axis labels
    int graphHeight = termHeight - 6;

    double xMin = -10.0, xMax = 10.0;
    double yMin = -10.0, yMax = 10.0;

    int xAxisRow = static_cast<int>((0 - yMin) / (yMax - yMin) * graphHeight);
    int yAxisCol = static_cast<int>((0 - xMin) / (xMax - xMin) * graphWidth);

    std::vector<std::vector<char>> graph(graphHeight, std::vector<char>(graphWidth, ' '));

    // Grid lines every 2 units
    for (int i = 0; i < graphHeight; ++i) {
        double y = yMax - (yMax - yMin) * i / graphHeight;
        if (std::fmod(y, 2.0) < 0.1 || std::fmod(y, 2.0) > 1.9) {
            for (int j = 0; j < graphWidth; ++j) {
                if (graph[i][j] == ' ') graph[i][j] = '.';
            }
        }
    }
    for (int j = 0; j < graphWidth; ++j) {
        double x = xMin + (xMax - xMin) * j / graphWidth;
        if (std::fmod(x, 2.0) < 0.1 || std::fmod(x, 2.0) > 1.9) {
            for (int i = 0; i < graphHeight; ++i) {
                if (graph[i][j] == ' ') graph[i][j] = '.';
            }
        }
    }

    // Plot function
    for (int j = 0; j < graphWidth; ++j) {
        double x = xMin + (xMax - xMin) * j / graphWidth;
        double y = evaluateFunction(expression, x);
        int yPos = static_cast<int>((y - yMin) / (yMax - yMin) * graphHeight);
        if (yPos >= 0 && yPos < graphHeight) {
            graph[graphHeight - yPos - 1][j] = '*';
        }
    }

    // Draw axes
    for (int i = 0; i < graphHeight; ++i) {
        if (yAxisCol >= 0 && yAxisCol < graphWidth) {
            if (graph[i][yAxisCol] != '*') graph[i][yAxisCol] = '|';
        }
    }
    if (xAxisRow >= 0 && xAxisRow < graphHeight) {
        for (int j = 0; j < graphWidth; ++j) {
            if (graph[graphHeight - xAxisRow - 1][j] != '*')
                graph[graphHeight - xAxisRow - 1][j] = '-';
        }
    }

    clearScreen();
    std::cout << "Graphing: " << expression << "\n\n";

    for (int i = 0; i < graphHeight; ++i) {
        double yLabel = yMin + (yMax - yMin) * (graphHeight - i - 1) / graphHeight;
        std::cout << std::setw(6) << std::fixed << std::setprecision(1) << yLabel << " |";

        for (int j = 0; j < graphWidth; ++j) {
            char ch = graph[i][j];
            if (ch == '*') std::cout << COLOR_GREEN << '*' << COLOR_RESET;
            else if (ch == '|' || ch == '-') std::cout << COLOR_WHITE << ch << COLOR_RESET;
            else if (ch == '.') std::cout << COLOR_GRAY << '.' << COLOR_RESET;
            else std::cout << ' ';
        }
        std::cout << std::endl;
    }

    // X-axis labels
    std::cout << "       +";
    for (int j = 0; j < graphWidth; ++j) {
        if ((j - yAxisCol) % 10 == 0)
            std::cout << '|';
        else
            std::cout << '-';
    }
    std::cout << "\n        ";
    for (int j = 0; j < graphWidth; j += 10) {
        double xLabel = xMin + (xMax - xMin) * j / graphWidth;
        std::cout << std::setw(10) << std::fixed << std::setprecision(1) << xLabel;
    }

    std::cout << "\n";
}

int main() {
    enableAnsiOnWindows();
    std::string function;

    while (true) {
        clearScreen();
        std::cout << "Terminal Graphing Calculator (Basic Version)\n";
        std::cout << "Supported: sin(x), cos(x), x^2, x\n";
        std::cout << "Enter function to plot (or 'q' to quit): ";
        std::getline(std::cin, function);

        if (function == "q" || function == "quit") break;

        if (function != "sin(x)" && function != "cos(x)" &&
            function != "x^2" && function != "x") {
            std::cerr << "Unsupported function.\n";
            std::cin.get();
            continue;
        }

        plotGraph(function);
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

    return 0;
}
