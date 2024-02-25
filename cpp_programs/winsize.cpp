#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

void getConsoleSize(int &width, int &height)
{
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	width = size.ws_col;
	height = size.ws_row;
}

void printLineOfChars(char character, int length)
{
	for (int i = 0; i < length; i++)
	{
		std::cout << character;
	}
}

int main()
{
	int consoleWidth, consoleHeight;
	getConsoleSize(consoleWidth, consoleHeight);

	// Clear screen code here

	printLineOfChars('X', consoleWidth);

	std::cout << "\nWidth: " << consoleWidth << std::endl;
	std::cout << "Height: " << consoleHeight << std::endl;

	return 0;
}