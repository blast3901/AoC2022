#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

namespace tube {
    namespace {
        std::array<int, 6> getFactors() {
            std::array<int, 6> factors{};
            for (int i = 0, j = 20; i < factors.size(); i++, j += 40)
                factors[i] = j;
            return factors;
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

    int execute(const std::vector<std::string> &instructions) {
        int X = 1;
        int i = 1;
        std::array<int, 6> values{};
        std::array<int, 6> factors = getFactors();
        for (const std::string &instruction: instructions) {
            if (instruction[0] == 'n') cycle(X, i, values, factors);
            else {
                int V = std::stoi(instruction.substr(5));
                cycle(X, i, values, factors);
                cycle(X, i, values, factors);
                X += V;
            }
        }
        return getSignalStrength(values, factors);
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
    std::cout << tube::execute(input) << std::endl;
    return 0;
}