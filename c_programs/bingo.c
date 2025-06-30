#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

#define SIZE 5

class Bingo {
public:
    Bingo() {
        generateCard();
    }

    void generateCard() {
        std::vector<int> numbers;
        for (int i = 1; i <= 75; ++i) {
            numbers.push_back(i);
        }
        std::random_shuffle(numbers.begin(), numbers.end());

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (i == SIZE / 2 && j == SIZE / 2) {
                    card[i][j] = 0; // Free space
                } else {
                    card[i][j] = numbers.back();
                    numbers.pop_back();
                }
            }
        }
    }

    void printCard() {
        std::cout << " B   I   N   G   O\n";
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (card[i][j] == 0) {
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
                return true; // Bingo found
            }
        }
        // Check diagonals
        if ((card[0][0] == 0 && card[1][1] == 0 && card[2][2] == 0 && card[3][3] == 0 && card[4][4] == 0) ||
            (card[0][4] == 0 && card[1][3] == 0 && card[2][2] == 0 && card[3][1] == 0 && card[4][0] == 0)) {
            return true; // Bingo found
        }
        return false; // No Bingo
    }

private:
    int card[SIZE][SIZE] = {0};
};

int main() {
    srand(static_cast<unsigned int>(time(0)));
    Bingo bingo;
    bingo.printCard();

    std::vector<bool> calledNumbers(75, false);
    while (true) {
        int num = rand() % 75 + 1;
        if (!calledNumbers[num - 1]) {
            calledNumbers[num - 1] = true;
            std::cout << "Number called: " << num << "\n";
            bingo.markNumber(num);
            bingo.printCard();
            if (bingo.checkBingo()) {
                std::cout << "Bingo!\n";
                break;
            }
        }
    }
    return 0;
}
