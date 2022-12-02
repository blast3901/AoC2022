#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int winState(const string &round) {
    char x = round.at(2);
    return x == 'X' ? -1 : (x == 'Y' ? 0 : 1);
}

char toPick(const string &round) {
    char x = round.at(0);
    if (winState(round) > 0) return x == 'A' ? 'Y' : (x == 'B' ? 'Z' : 'X');
    else if (winState(round) == 0) return x == 'A' ? 'X' : (x == 'B' ? 'Y' : 'Z');
    else return x == 'A' ? 'Z' : (x == 'B' ? 'X' : 'Y');
}

int main() {
    ifstream input(R"(C:\Users\dbdan\Desktop\Coding\AoC\Day2\input.txt)");
    string rounds[2500];
    for (string &round: rounds) {
        getline(input, round);
    }
    input.close();

    int plScore{}, plAdd;
    for (string &round: rounds) {
        char player = toPick(round);

        if (player == 'X') plAdd = 1;
        else if (player == 'Y') plAdd = 2;
        else plAdd = 3;

        if (winState(round) > 0) plScore += plAdd + 6;
        else if (winState(round) == 0) plScore += plAdd + 3;
        else plScore += plAdd;
    }
    cout << plScore;
    return 0;
}