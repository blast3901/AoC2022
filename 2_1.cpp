#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int winState(const string &round) {
    char opponent = round.at(0);
    char player = round.at(2);
    if (opponent == 'A' && player != 'X'
        || opponent == 'B' && player != 'Y'
        || opponent == 'C' && player != 'Z')
        if ((opponent == 'A' && player == 'Y')
            || (opponent == 'B' && player == 'Z')
            || (opponent == 'C' && player == 'X'))
            return 1;
    if ((opponent == 'A' && player == 'Z')
        || (opponent == 'B' && player == 'X')
        || (opponent == 'C' && player == 'Y'))
        return -1;
    else return 0;
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
        char player = round.at(2);

        if (player == 'X') plAdd = 1;
        else if (player == 'Y') plAdd = 2;
        else if (player == 'Z') plAdd = 3;

        if (winState(round) > 0) plScore += plAdd + 6;
        else if (winState(round) == 0) plScore += plAdd + 3;
        else if (winState(round) < 0) plScore += plAdd;
    }
    cout << plScore;
    return 0;
}