#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <tuple>

namespace ropeBridge {
    namespace {
        struct pos {
            int x;
            int y;
        };

        bool operator==(const pos &a, const pos &b) {
            return a.x == b.x && a.y == b.y;
        }

        bool operator<(const pos &a, const pos &b) {
            return std::tuple(a.x, a.y) < std::tuple(b.x, b.y);
        }

        pos &operator+=(pos &a, const pos &b) {
            a.x += b.x;
            a.y += b.y;
            return a;
        }
    }

    int execute(const std::vector<std::pair<char, int>> &instructions, int n) {
        std::set<pos> visited;

        std::vector<pos> knots(n, {0, 0});

        pos &h = knots.front();
        pos &t = knots.back();

        for (const std::pair<char, int> &instruction: instructions) {
            for (int i = 0; i < instruction.second; i++) {
                if (instruction.first == 'R') h += {1, 0};
                else if (instruction.first == 'D') h += {0, 1};
                else if (instruction.first == 'L') h += {-1, 0};
                else if (instruction.first == 'U') h += {0, -1};

                for (int j = 1; j < knots.size(); j++) {
                    pos &current = knots[j];
                    pos &last = knots[j - 1];

                    if (pos{current.x + 2, current.y} == last)
                        current += {1, 0};
                    else if (pos{current.x - 2, current.y} == last)
                        current += {-1, 0};
                    else if (pos{current.x, current.y + 2} == last)
                        current += {0, 1};
                    else if (pos{current.x, current.y - 2} == last)
                        current += {0, -1};
                    else if (pos{current.x + 2, current.y - 1} == last ||
                             pos{current.x + 1, current.y - 2} == last ||
                             pos{current.x + 2, current.y - 2} == last)
                        current += {1, -1};
                    else if (pos{current.x - 2, current.y - 1} == last ||
                             pos{current.x - 1, current.y - 2} == last ||
                             pos{current.x - 2, current.y - 2} == last)
                        current += {-1, -1};
                    else if (pos{current.x + 2, current.y + 1} == last ||
                             pos{current.x + 1, current.y + 2} == last ||
                             pos{current.x + 2, current.y + 2} == last)
                        current += {1, 1};
                    else if (pos{current.x - 2, current.y + 1} == last ||
                             pos{current.x - 1, current.y + 2} == last ||
                             pos{current.x - 2, current.y + 2} == last)
                        current += {-1, 1};
                }
                visited.insert(t);
            }
        }
        return visited.size();
    }

    std::vector<std::pair<char, int>> readFile(const std::string &path) {
        std::ifstream input(path);
        std::vector<std::pair<char, int>> instructions;
        std::string buffer;
        while (std::getline(input, buffer))
            instructions.emplace_back(buffer[0], std::stoi(buffer.substr(2)));
        return instructions;
    }
}

int main() {
    const int numberOfKnots = 10;
    std::vector<std::pair<char, int>> input = ropeBridge::readFile("Day9/input.txt");
    std::cout << ropeBridge::execute(input, numberOfKnots);
    return 0;
}