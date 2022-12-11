#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <sstream>

namespace monkey_play {
    struct monkey {
        std::vector<int> items;
        char operation;
        int x;
        int test;
        int is_true;
        int is_false;
        size_t inspected{};
    };

    int get_modulo(const std::array<monkey, 8> &monkeys) {
        int x = 1;
        for (const monkey &monki : monkeys)
            x *= monki.test;
        return x;
    }

    size_t execute(const int rounds, std::array<monkey, 8> &monkeys) {
        int modulo = get_modulo(monkeys);
        for (int i = 0; i < rounds; i++) {
            for (monkey &monki: monkeys) {
                for (int item : monki.items) {
                    ++monki.inspected;
                    int y = monki.x;
                    if (monki.x == -1) y = item;
                    if (monki.operation == '+') item += y;
                    else if (monki.operation == '*') item *= y;

                    item %= modulo;

                    if (item % monki.test == 0)
                        monkeys[monki.is_true].items.push_back(item);
                    else
                        monkeys[monki.is_false].items.push_back(item);
                }
                monki.items.erase(monki.items.begin(), monki.items.end());
            }
        }
        size_t max1{}, max2{}, temp;
        for (const monkey &monki: monkeys) {
            if (monki.inspected != 0) std::cout << monki.inspected << std::endl;
            temp = max1;
            max1 = max1 < monki.inspected ? monki.inspected : max1;
            max2 = max2 < temp && temp != max1 ? temp : max2;
        }
        std::cout << std::endl << max1 << " " << max2 << std::endl;
        return max1 * max2;
    }

    std::vector<int> get_items(const std::string &raw_buffer) {
        std::vector<int> items;
        std::istringstream token_stream(raw_buffer.substr(17));
        std::string token;
        while (std::getline(token_stream, token, ','))
            items.push_back(std::stoi(token));
        return items;
    }

    std::array<monkey, 8> read_file(const std::string &path) {
        std::ifstream input(path);
        std::array<monkey, 8> monkeys;
        std::string buffer;
        int i = -1;
        while (std::getline(input, buffer)) {
            switch (buffer[8]) {
                case ':':
                    ++i;
                    break;
                case 'n':
                    monkeys[i].items = get_items(buffer);
                    break;
                case 'i':
                    monkeys[i].operation = buffer[23];
                    if (buffer[25] == 'o') monkeys[i].x = -1;
                    else monkeys[i].x = std::stoi(buffer.substr(25));
                    break;
                case 'd':
                    monkeys[i].test = std::stoi(buffer.substr(21));
                    break;
                case 'r':
                    monkeys[i].is_true = std::stoi(buffer.substr(28));
                    break;
                case 'a':
                    monkeys[i].is_false = std::stoi(buffer.substr(29));
                    input.ignore(100, '\n');
                    break;
            }
        }
        return monkeys;
    }
}

int main() {
    std::array<monkey_play::monkey, 8> monkeys = monkey_play::read_file("Day11/input.txt");
    std::cout << monkey_play::execute(1000, monkeys) << std::endl;

    return 0;
}