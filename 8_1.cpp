#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace forest {
    namespace {
        bool checkUp(const std::vector<std::string> &grid, const int posY, const int posX) {
            const int height = grid[posY][posX] - '0';
            for (int i = 0; i < posY; i++)
                if (height <= (grid[i][posX] - '0')) return false;
            return true;
        }

        bool checkDown(const std::vector<std::string> &grid, const int posY, const int posX) {
            const int height = grid[posY][posX] - '0';
            for (int i = posY + 1; i < grid.size(); i++)
                if (height <= (grid[i][posX] - '0')) return false;
            return true;
        }

        bool checkLeft(const std::vector<std::string> &grid, const int posY, const int posX) {
            const int height = grid[posY][posX] - '0';
            for (int i = 0; i < posX; i++)
                if (height <= (grid[posY][i] - '0')) return false;
            return true;
        }

        bool checkRight(const std::vector<std::string> &grid, const int posY, const int posX) {
            const int height = grid[posY][posX] - '0';
            for (int i = posX + 1; i < grid[posY].length(); i++)
                if (height <= (grid[posY][i] - '0')) return false;
            return true;
        }

        bool checkVisibility(const std::vector<std::string> &g, const int i, const int j) {
            return checkUp(g, i, j) || checkDown(g, i, j)
                   || checkLeft(g, i, j) || checkRight(g, i, j);
        }
    }

    int maxScenicScore(const std::vector<std::string> &grid) {
        const int max_x = grid[0].length();
        const int max_y = grid.size();
        int count{};
        for (int i = 1; i < max_y - 1; i++)
            for (int j = 1; j < max_x - 1; j++)
                if (checkVisibility(grid, i, j)) ++count;
        return count + (2 * max_x) + (2 * max_y) - 4;
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