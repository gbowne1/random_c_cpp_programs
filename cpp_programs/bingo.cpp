#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <thread>
#include <random>

#define SIZE 5

class Bingo {
public:
    Bingo() {
        generateCard();
    }

    void generateCard() {
        for (int col = 0; col < SIZE; ++col) {
            std::vector<int> columnNumbers;
            int start = col * 15 + 1;
            for (int i = 0; i < 15; ++i) {
                columnNumbers.push_back(start + i);
            }
            std::random_shuffle(columnNumbers.begin(), columnNumbers.end());

            for (int row = 0; row < SIZE; ++row) {
                if (row == 2 && col == 2) {
                    card[row][col] = 0; // Free space
                } else {
                    card[row][col] = columnNumbers.back();
                    columnNumbers.pop_back();
                }
            }
        }
    }

    void printCard() {
        std::cout << "\n B   I   N   G   O\n";
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (card[i][j] == 0 && !(i == SIZE / 2 && j == SIZE / 2)) {
                    std::cout << " X  ";
                } else if (i == SIZE / 2 && j == SIZE / 2) {
                    std::cout << " *  ";
                } else {
                    std::cout << std::setw(2) << card[i][j] << " ";
                }
            }
            std::cout << "\n";
        }
    }

    void markNumber(int num) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (card[i][j] == num) {
                    card[i][j] = 0; // Mark the number
                }
            }
        }
    }

    bool checkBingo() {
        // Check rows and columns
        for (int i = 0; i < SIZE; ++i) {
            if ((card[i][0] == 0 && card[i][1] == 0 && card[i][2] == 0 && card[i][3] == 0 && card[i][4] == 0) ||
                (card[0][i] == 0 && card[1][i] == 0 && card[2][i] == 0 && card[3][i] == 0 && card[4][i] == 0)) {
                return true;
            }
        }

        // Check diagonals
        if ((card[0][0] == 0 && card[1][1] == 0 && card[2][2] == 0 && card[3][3] == 0 && card[4][4] == 0) ||
            (card[0][4] == 0 && card[1][3] == 0 && card[2][2] == 0 && card[3][1] == 0 && card[4][0] == 0)) {
            return true;
        }

        return false;
    }

private:
    int card[SIZE][SIZE] = {0};
};

char getBingoPrefix(int num) {
    if (num >= 1 && num <= 15) return 'B';
    else if (num <= 30) return 'I';
    else if (num <= 45) return 'N';
    else if (num <= 60) return 'G';
    else return 'O';
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    while (true) {
        Bingo bingo;
        std::vector<bool> calledNumbers(75, false);
        bingo.printCard();

        while (true) {
            int num = rand() % 75 + 1;
            if (!calledNumbers[num - 1]) {
                calledNumbers[num - 1] = true;
                std::cout << "\nNumber called: " << getBingoPrefix(num) << "-" << num << "\n";
                bingo.markNumber(num);
                bingo.printCard();

                if (bingo.checkBingo()) {
                    std::cout << "Bingo!\n";
                    break;
                }

                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }

        char again;
        std::cout << "Play again? (y/n): ";
        std::cin >> again;
        if (again != 'y' && again != 'Y') break;
    }

    return 0;
}
