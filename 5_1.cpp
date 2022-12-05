#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<vector<char>> buildStacks(string s[]) {
    for (int i = 0; i < 7; i++)
        while (s[i].length() != 36) s[i] += ' ';

    vector<vector<char>> stacks(9);
    int index = 0;
    for (int i = 1; i < 36; i += 4) {
        for (int j = 7; j >= 0; j--) {
            char c = s[j].at(i);
            if (c != ' ') stacks[index].push_back(c);
        }
        ++index;
    }
    return stacks;
}

vector<vector<int>> buildCommands(string s[]) {
    for (int i = 0; i < 501; i++)
        s[i] += '-';

    vector<vector<int>> result(501, vector<int>(3));
    for (int i = 0; i < 501; i++) {
        int k{};
        for (int j = 0; j < s[i].length(); j++) {
            if (s[i].at(j) <= 57 && s[i].at(j) >= 48) {
                if (s[i].at(j + 1) <= 57 && s[i].at(j + 1) >= 48)
                    result[i][k] = stoi(s[i].substr(j++, 2));
                else
                    result[i][k] = stoi(s[i].substr(j, 1));
                ++k;
            }
        }
    }
    return result;
}

void executeCommands(vector<vector<int>> commands, vector<vector<char>> &stacks) {
    for (int i = 0; i < 501; i++) {
        int from = commands[i][1] - 1;
        int to = commands[i][2] - 1;
        for (int j = 0; j < commands[i][0]; j++) {
            //if (stacks[from].empty()) continue;
            stacks[to].push_back(stacks[from].back());
            stacks[from].pop_back();
        }
    }
}

int main() {
    ifstream input("Day5/input.txt");
    string rawStacks[10];
    string rawCommands[501];
    for (int i = 0; i < 8; i++)
        getline(input, rawStacks[i]);

    for (int i = 0; i < 2; i++)
        input.ignore(35, '\n');

    for (auto &command: rawCommands)
        getline(input, command);
    input.close();

    vector<vector<char>> stacks = buildStacks(rawStacks);
    vector<vector<int>> commands = buildCommands(rawCommands);
    executeCommands(commands, stacks);

    for (int i = 0; i < 9; i++)
        cout << stacks[i].back();
    return 0;
}