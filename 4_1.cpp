#include <iostream>
#include <fstream>
#include <string>
#include <utility>

using namespace std;

pair<int,int> splitToInt(const string& s) {
    int x{}, y{}, j{};
    for (int i = 0; i < s.length(); i++) {
        if (s.at(i) == '-') {
            x = stoi(s.substr(0, i));
            j = i+1;
            break;
        }
    }
    y = stoi(s.substr(j));
    return {x,y};
}

string split(string &pair) {
    bool isLeft = true;
    string left{}, right{};
    for (char c : pair) {
        if (c == ',') isLeft = false;
        else if (isLeft) left += c;
        else right += c;
    }
    pair = left;
    return right;
}

bool contains(const string& left, const string& right) {
    pair leftRange = splitToInt(left);
    pair rightRange = splitToInt(right);
    int l1 = leftRange.first, l2 = leftRange.second;
    int r1 = rightRange.first, r2 = rightRange.second;

    if ((l1 <= r1 && l2 >= r2) || (l1 >= r1 && l2 <= r2))
        return true;
    else return false;
}

int main() {
    string pairs[1000][2];
    ifstream input("Day4/input.txt");
    int count{};
    for (auto &pair: pairs) {
        getline(input, pair[0]);
        pair[1] = split(pair[0]);
        count += contains(pair[0],pair[1]);
    }
    input.close();

    cout << count;
    return 0;
}