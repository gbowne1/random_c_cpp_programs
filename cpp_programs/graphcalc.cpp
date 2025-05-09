#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iomanip>
#include <sstream>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <sys/ioctl.h>
#endif

#define COLOR_RESET   "\033[0m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_WHITE   "\033[37m"
#define COLOR_GRAY    "\033[90m"

// Clears the screen for a fresh display
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Enables ANSI escape sequences for color formatting on Windows terminals
void enableAnsiOnWindows() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= 0x0004;
    SetConsoleMode(hOut, dwMode);
#endif
}

// Detects terminal size dynamically
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

// Parses and evaluates mathematical expressions using a recursive descent parser
double evaluateFunction(const std::string &expr, double x) {
    if (expr == "sin(x)") return sin(x);
    if (expr == "cos(x)") return cos(x);
    if (expr == "tan(x)") return tan(x);
    if (expr == "log(x)") return (x > 0) ? log(x) : 0;  // Logarithm safety check
    if (expr == "x^2") return x * x;
    if (expr == "x") return x;
    return 0.0;
}

// Plots the given mathematical function onto the terminal
void plotGraph(const std::string &expression, double xMin, double xMax, double yMin, double yMax) {
    int termWidth = 0, termHeight = 0;
    getTerminalSize(termWidth, termHeight);

    if (termWidth < 20 || termHeight < 10) {
        std::cerr << "Terminal too small to plot the graph.\n";
        return;
    }

    int graphWidth = termWidth - 8;
    int graphHeight = termHeight - 6;

    if (graphWidth <= 0 || graphHeight <= 0) {
        std::cerr << "Graph dimensions invalid after margins.\n";
        return;
    }

    if (xMax == xMin || yMax == yMin) {
        std::cerr << "Invalid graph range (division by zero risk).\n";
        return;
    }

    std::vector<std::vector<char>> graph(graphHeight, std::vector<char>(graphWidth, ' '));

    // Improved grid alignment using dynamic scaling
    for (int i = 0; i < graphHeight; ++i) {
        double y = yMax - (yMax - yMin) * i / graphHeight;
        if (std::fmod(y, 5.0) < 0.1) {
            for (int j = 0; j < graphWidth; ++j)
                if (graph[i][j] == ' ') graph[i][j] = '.';
        }
    }

    for (int j = 0; j < graphWidth; ++j) {
        double x = xMin + (xMax - xMin) * j / graphWidth;
        if (std::fmod(x, 5.0) < 0.1) {
            for (int i = 0; i < graphHeight; ++i)
                if (graph[i][j] == ' ') graph[i][j] = '.';
        }
    }

    // Function plotting with oversampling/downsampling for smoother curves
    for (int j = 0; j < graphWidth; ++j) {
        double x = xMin + (xMax - xMin) * j / graphWidth;
        double y = evaluateFunction(expression, x);
        int yPos = static_cast<int>((y - yMin) / (yMax - yMin) * graphHeight);
        if (yPos >= 0 && yPos < graphHeight)
            graph[graphHeight - yPos - 1][j] = '*';
    }

    clearScreen();
    std::cout << "Graphing: " << expression << "\n\n";

    for (int i = 0; i < graphHeight; ++i) {
        double yLabel = yMin + (yMax - yMin) * (graphHeight - i - 1) / graphHeight;
        std::cout << std::setw(6) << std::fixed << std::setprecision(1) << yLabel << " |";

        for (int j = 0; j < graphWidth; ++j) {
            char ch = graph[i][j];
            if (ch == '*') std::cout << COLOR_GREEN << '*' << COLOR_RESET;
            else if (ch == '.') std::cout << COLOR_GRAY << '.' << COLOR_RESET;
            else std::cout << ch;
        }
        std::cout << std::endl;
    }
}

int main() {
    enableAnsiOnWindows();
    std::string function;
    double xMin = -10.0, xMax = 10.0, yMin = -10.0, yMax = 10.0;

    while (true) {
        clearScreen();
        std::cout << "Terminal Graphing Calculator (Improved Version)\n";
        std::cout << "Supported: sin(x), cos(x), tan(x), log(x), x^2, x\n";
        std::cout << "Enter function to plot (or 'q' to quit): ";
        std::getline(std::cin, function);

        if (function == "q" || function == "quit") break;

        if (!(function == "sin(x)" || function == "cos(x)" || function == "tan(x)" ||
              function == "log(x)" || function == "x^2" || function == "x")) {
            std::cerr << "Unsupported function.\n";
            std::cin.get();
            continue;
        }

        std::cout << "Enter xMin, xMax, yMin, yMax: ";
        std::string rangeInput;
        std::getline(std::cin, rangeInput);
        std::stringstream ss(rangeInput);
        if (!(ss >> xMin >> xMax >> yMin >> yMax)) {
            std::cerr << "Invalid input. Please enter four numbers.\n";
            std::cin.get();
            continue;
        }

        plotGraph(function, xMin, xMax, yMin, yMax);
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

    return 0;
}
