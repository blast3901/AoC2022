#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string lines[2254];
    ifstream input ("input.txt");
    int elfCount = 1;
    for (string& line : lines) {
        getline(input,line);
        if (line.empty()) ++elfCount;
    }
    input.close();
   
    int *elfCals = new int[elfCount];
    for (int i = 0; i < elfCount; i++) {
        elfCals[i] = 0;
    }
    
    int j = 0;
    for (string& line : lines) {
        if(line.empty()) {
            ++j;
            continue;
        }
        elfCals[j] = elfCals[j] + stoi(line);
    }

    int max1{}, max2{}, max3{};
    for (int i = 0; i < elfCount; i++){
       if (elfCals[i] > max1) max1 = elfCals[i];
       if (elfCals[i] > max2 && elfCals[i] < max1) max2 = elfCals[i];
       if (elfCals[i] > max3 && elfCals[i] < max2) max3 = elfCals[i];
    }
    cout << max1 << " " << max1 + max2 + max3 << endl;
    return 0;
}
