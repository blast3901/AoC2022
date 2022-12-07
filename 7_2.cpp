#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

namespace filesystem {
    struct file {
        std::string name;
        int size;
    };

    struct directory {
        std::string name;
        directory *parent;
        std::vector<directory> subDirs;
        std::vector<file> files;
    };

    int sumSize(const directory &dir, int &total) {
        int dirSize{};
        for (const file &currentFile: dir.files)
            dirSize += currentFile.size;

        for (const directory &subDir: dir.subDirs)
            dirSize += sumSize(subDir, total);

        if (dirSize < 100000)
            total += dirSize;
        return dirSize;
    }

    int getSize(const std::string &s) {
        int size{};
        for (const char &c: s) {
            size *= 10;
            size += c - '0';
        }
        return size;
    }

    int getDirSize(const directory &dir) {
        int size{};
        for (const file &currentFile: dir.files)
            size += currentFile.size;
        for (const directory &subDir: dir.subDirs)
            size += getDirSize(subDir);
        return size;
    }

    void getDirs(const directory &dir, std::vector<directory> &dirs) {
        dirs.push_back(dir);
        for (const directory &subdirectory: dir.subDirs)
            getDirs(subdirectory, dirs);
    }

    directory parseInput(const std::vector<std::string> &input) {
        directory root{"/", nullptr, {}, {}};
        root.parent = &root;
        directory *currentDir = &root;

        for (const std::string &line: input) {
            std::string temp;
            std::stringstream inputStream(line);
            std::vector<std::string> tokens;
            while (std::getline(inputStream, temp, ' '))
                tokens.push_back(temp);

            if (tokens[0] == "$") {
                if (tokens[1] == "cd") {
                    if (tokens[2] == "..")
                        currentDir = currentDir->parent;
                    else if (tokens[2] == "/")
                        currentDir = &root;
                    else {
                        for (directory &subdirectory: currentDir->subDirs) {
                            if (subdirectory.name == tokens[2]) {
                                currentDir = &subdirectory;
                                break;
                            }
                        }
                    }
                }
            } else if (tokens[0] == "dir") {
                directory newDir{tokens[1], currentDir, {}, {}};
                currentDir->subDirs.push_back(newDir);
            } else {
                int fileSize = getSize(tokens[0]);
                file newFile{tokens[1], fileSize};
                currentDir->files.push_back(newFile);
            }
        }
        return root;
    }

    std::vector<std::string> readFile(const std::string &path) {
        std::ifstream input(path);
        std::vector<std::string> vec;
        std::string temp;
        while (std::getline(input, temp))
            vec.push_back(temp);
        return vec;
    }

    std::pair<std::string, int> execute() {
        std::vector<std::string> input = filesystem::readFile("Day7/input.txt");
        filesystem::directory dir = filesystem::parseInput(input);
        std::vector<directory> dirs;
        getDirs(dir, dirs);

        int min = getDirSize(dir);
        const int TO_FREE = 30000000 - 70000000 - min;
        std::string name{};
        for (const directory &currentDir: dirs) {
            int size = getDirSize(currentDir);
            if (size < min && size >= TO_FREE) {
                name = currentDir.name;
                min = size;
            }
        }
        return {name, min};
    }
}

int main() {
    std::pair<std::string, int> result = filesystem::execute();
    std::cout << result.first << " " << result.second;
}