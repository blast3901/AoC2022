#include <iostream>
#include <fstream>
#include <string>

using namespace std;

char sharedChar(const string& left, const string& right) {
    for (char i: left)
        for (char j: right)
            if (i == j) return i;
    return ' ';
}
// a = 97, z = 122; A = 65, Z = 90
int evaluate(const string& s) {
    int sum{};
    for (char c : s) {
        if (islower(c)) sum += (c - 96);
        else sum += (c - 38);
    }
    return sum;
}

int main() {
    string lines[300][2];
    ifstream input("Day3/input.txt");
    for (auto &line: lines) {
        getline(input, line[0]);
        unsigned int lineLen_2 = line[0].length() / 2;
        line[1] = line[0].substr(lineLen_2);
        line[0] = line[0].substr(0, lineLen_2);
    }
    input.close();

    string foundChars{};
    for (auto &line: lines)
        foundChars += sharedChar(line[0], line[1]);
    cout << evaluate(foundChars);
    return 0;
}