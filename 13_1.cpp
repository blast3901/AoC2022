#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

namespace distressSignal {
    bool isNum(const char c) {
        return c >= '0' && c <= '9';
    }

    void test(const std::string &l, const std::string &r, int &index, std::vector<int> &rightOrder) {
        ++index;
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
                if (stoi(leftNum) < stoi(rightNum)) rightOrder.push_back(index);
                break;
            }
            if (l[i] == r[j]) {
                ++i;
                ++j;
                continue;
            } else {
                if (l[i] == ']') {
                    rightOrder.push_back(index);
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
    }

    int execute(const std::vector<std::string> &lines) {
        int index{};
        std::vector<int> rightOrder;
        for (int i = 0; i < lines.size(); i += 2)
            test(lines[i], lines[i + 1], index, rightOrder);
        return accumulate(rightOrder.begin(), rightOrder.end(), -2);
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