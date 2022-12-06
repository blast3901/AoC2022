#include <iostream>
#include <fstream>
#include <string>

class tuning{
private:
    static bool isMarker(const std::string& s, const int& index, const int& n) {
        for (int i = index; i < index+n; i++) {
            for (int j = index; j < index+n; j++) {
                if (i == j) continue;
                if (s[i] == s[j]) return false;
            }
        }
        return true;
    }

public:
    static std::string readFile(const std::string& path) {
        std::string s;
        std::ifstream input(path);
        std::getline(input,s);
        return s;
    }

    static int findMarkerIndex(const std::string& s,const int& prefixLength) {
        for (int i = 0; i < s.length()-prefixLength; i++)
            if (isMarker(s,i,prefixLength)) return i+prefixLength;
        return -1;
    }
};

int main() {
    const int prefixLength = 4;
    std::string input = tuning::readFile("Day6/input.txt");
    std::cout << tuning::findMarkerIndex(input,prefixLength);
    return 0;
}