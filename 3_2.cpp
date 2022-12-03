#include <iostream>
#include <fstream>
#include <string>

using namespace std;

char sharedChar(const string& elf1, const string& elf2, const string& elf3) {
    for (char i: elf1)
        for (char j: elf2)
            for (char k: elf3)
                if (i == j && i == k) return i;
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
    string lines[300];
    ifstream input("Day3/input.txt");
    for (auto &line: lines)
        getline(input, line);
    input.close();

    string foundChars{};
    for (int i = 2; i < 300; i+=3)
        foundChars += sharedChar(lines[i-2],lines[i-1],lines[i]);
    cout << evaluate(foundChars);
    return 0;
}