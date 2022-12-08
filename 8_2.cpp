#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace forest {
    namespace {
        int countUp(const std::vector<std::string> &grid, const int posY, const int posX) {
            const int height = grid[posY][posX] - '0';
            int count{};
            for (int i = posY - 1; i >= 0; i--) {
                ++count;
                if (height <= (grid[i][posX] - '0')) break;
            }
            return count;
        }

        int countDown(const std::vector<std::string> &grid, const int posY, const int posX) {
            const int height = grid[posY][posX] - '0';
            int count{};
            for (int i = posY + 1; i < grid.size(); i++) {
                ++count;
                if (height <= (grid[i][posX] - '0')) break;
            }
            return count;
        }

        int countLeft(const std::vector<std::string> &grid, const int posY, const int posX) {
            const int height = grid[posY][posX] - '0';
            int count{};
            for (int i = posX - 1; i >= 0; i--) {
                ++count;
                if (height <= (grid[posY][i] - '0')) break;
            }
            return count;
        }

        int countRight(const std::vector<std::string> &grid, const int posY, const int posX) {
            const int height = grid[posY][posX] - '0';
            int count{};
            for (int i = posX + 1; i < grid[posY].length(); i++) {
                ++count;
                if (height <= (grid[posY][i] - '0')) break;
            }
            return count;
        }

        int calcScenicScore(const std::vector<std::string> &g, const int i, const int j) {
            return countUp(g, i, j) * countDown(g, i, j)
                   * countLeft(g, i, j) * countRight(g, i, j);
        }
    }

    int maxScenicScore(const std::vector<std::string> &grid) {
        const int max_x = grid[0].length();
        const int max_y = grid.size();
        int max{};
        int temp;
        for (int i = 1; i < max_y - 1; i++) {
            for (int j = 1; j < max_x - 1; j++) {
                temp = calcScenicScore(grid, i, j);
                if (max < temp) max = temp;
            }
        }
        return max;
    }

    std::vector<std::string> readFile(const std::string &path) {
        std::ifstream input(path);
        std::vector<std::string> vec;
        std::string temp;
        while (std::getline(input, temp))
            vec.push_back(temp);
        return vec;
    }
}

int main() {
    std::vector<std::string> input = forest::readFile("Day8/input.txt");
    std::cout << forest::maxScenicScore(input);
    return 0;
}