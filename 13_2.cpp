#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

namespace distressSignal {
    bool isNum(const char c) {
        return c >= '0' && c <= '9';
    }

    void test(const std::string &r, const std::array<std::string, 2> &signals, std::array<int, 2> &count, int &index) {
        ++index;
        std::string l;
        for (int k = 0; k < 2; k++) {
            l = signals[k];
            int i = 0, j = 0;
            while (i < l.length() && j < r.length()) {
                if (isNum(l[i]) && isNum(r[j])) {
                    std::string leftNum, rightNum;
                    while (i < l.length() && isNum(l[i])) {
                        leftNum += l[i];
                        ++i;
                    }
                    while (j < r.length() && isNum(r[j])) {
                        rightNum += r[j];
                        ++j;
                    }
                    if (stoi(leftNum) == stoi(rightNum)) continue;
                    if (stoi(leftNum) < stoi(rightNum)) ++count[k];
                    break;
                }
                if (l[i] == r[j]) {
                    ++i;
                    ++j;
                    continue;
                } else {
                    if (l[i] == ']') {
                        ++count[k];
                        break;
                    } else if (r[j] == ']') {
                        break;
                    } else if (l[i] == '[' || l[i] == ',') {
                        ++i;
                        continue;
                    } else if (r[j] == '[' || r[j] == ',') {
                        ++j;
                        continue;
                    }
                }
            }
            if (i == l.length()) ++count[k];
        }
    }

    int execute(std::vector<std::string> &lines) {
        std::array<std::string, 2> signals{"[[2]]", "[[6]]"};
        std::array<int, 2> count{};
        int index{};
        for (const auto &line: lines)
            test(line, signals, count, index);
        return (index - count[0] + 1) * (index - count[1] + 2);
    }

    std::vector<std::string> readFile(const std::string &path) {
        std::ifstream input(path);
        std::vector<std::string> lines;
        std::string buffer;
        while (std::getline(input, buffer)) {
            if (buffer.length() == 0) continue;
            lines.push_back(buffer);
        }
        return lines;
    }
}

int main() {
    std::vector<std::string> input = distressSignal::readFile("Day13/input.txt");
    std::cout << distressSignal::execute(input) << "\n";
    return 0;
}