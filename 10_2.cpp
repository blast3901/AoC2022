#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

namespace tube {
    namespace {
        void printScreen(const std::array<char, 240> &screen) {
            for (int i = 0; i < screen.size(); i++) {
                std::cout << screen[i];
                if ((i + 1) % 40 == 0)
                    std::cout << "\n";
            }
        }

        std::array<int, 6> getFactors() {
            std::array<int, 6> factors{};
            for (int i = 0, j = 20; i < factors.size(); i++, j += 40)
                factors[i] = j;
            return factors;
        }

        std::array<char, 240> initializeScreen() {
            std::array<char, 240> screen{};
            for (int i = 0; i < screen.size(); i++)
                screen[i] = '.';
            return screen;
        }

        void checkCycle(const int X, const int i, std::array<char, 240> &screen) {
            if ((i % 40 >= X - 1) && (i % 40 <= X + 1))
                screen[i] = '#';
        }

        void cycle(const int X, int &i, std::array<int, 6> &values, const std::array<int, 6> &factors) {
            for (int j = 0; j < factors.size(); j++)
                if (i == factors[j]) values[j] = X;
            ++i;
        }

        int getSignalStrength(const std::array<int, 6> &values, const std::array<int, 6> &factors) {
            int result{};
            for (int i = 0; i < factors.size(); i++)
                result += values[i] * factors[i];
            return result;
        }
    }

    void execute(const std::vector<std::string> &instructions) {
        int X = 1;
        int i = 0;
        std::array<int, 6> values{};
        std::array<int, 6> factors = getFactors();
        std::array<char, 240> screen = initializeScreen();
        for (const std::string &instruction: instructions) {
            if (instruction[0] == 'n') {
                checkCycle(X, i, screen);
                cycle(X, i, values, factors);
            } else {
                int V = std::stoi(instruction.substr(5));
                for (int j = 0; j < 2; j++) {
                    checkCycle(X, i, screen);
                    cycle(X, i, values, factors);
                }
                X += V;
            }
        }
        printScreen(screen);
    }

    std::vector<std::string> readFile(const std::string &path) {
        std::ifstream input(path);
        std::vector<std::string> instructions;
        std::string buffer;
        while (std::getline(input, buffer))
            instructions.push_back(buffer);
        return instructions;
    }
}

int main() {
    std::vector<std::string> input = tube::readFile("Day10/input.txt");
    tube::execute(input);
    return 0;
}