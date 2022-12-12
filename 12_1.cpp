#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <queue>

namespace hill_climb {
    namespace {
        bool isPossible(const int row, const int col, const int n, const int m) {
            return !(row >= n || col >= m || row < 0 || col < 0);
        }

        std::pair<int, int> find_end(std::vector<std::string> &grid) {
            for (int i = 0; i < grid.size(); i++)
                for (int j = 0; j < grid[i].size(); j++)
                    if (grid[i][j] == 'E') {
                        grid[i][j] = 'z';
                        return {i, j};
                    }
            return {-1, -1};
        }
    }

    int execute(std::vector<std::string> &grid) {
        int n = grid.size();
        int m = grid[0].size();
        std::pair<int, int> end = find_end(grid);
        std::queue<std::pair<int, std::pair<int, int>>> q;
        std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
        visited[end.first][end.second] = true;

        q.emplace(0, end);

        while (!q.empty()) {
            int dist = q.front().first;
            int row = q.front().second.first;
            int col = q.front().second.second;
            q.pop();

            if (grid[row][col] == 'S') return dist;

            std::array<int, 4> dx = {1, -1, 0, 0};
            std::array<int, 4> dy = {0, 0, 1, -1};

            for (int i = 0; i < 4; i++) {
                int newRow = row + dx[i];
                int newCol = col + dy[i];
                if (isPossible(newRow, newCol, n, m) && !visited[newRow][newCol]) {
                    char previous = grid[newRow][newCol] == 'S' ? 'a' : grid[newRow][newCol];
                    if (grid[row][col] - previous <= 1) {
                        visited[newRow][newCol] = true;
                        q.emplace(dist + 1, std::make_pair(newRow, newCol));
                    }
                }
            }
        }
        return -1;
    }

    std::vector<std::string> read_file(const std::string &path) {
        std::ifstream input(path);
        std::vector<std::string> grid;
        std::string buffer;
        while (std::getline(input, buffer))
            grid.push_back(buffer);
        return grid;
    }
}

int main() {
    std::vector<std::string> grid = hill_climb::read_file("Day12/input.txt");
    std::cout << hill_climb::execute(grid) << std::endl;
    return 0;
}