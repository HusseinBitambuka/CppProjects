#include "../include/regex/matcher.hpp"

#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: grep_clone <pattern> <file_path>\n";
        return 1;
    }

    const std::string pattern = argv[1];
    const std::string filePath = argv[2];

    std::ifstream file(filePath);
    if (!file)
    {
        std::cerr << "Error: cannot open file: " << filePath << "\n";
        return 1;
    }

    std::string line;
    int lineNumber = 1;

    while (std::getline(file, line))
    {
        if (matchRegex(pattern, line))
        {
            std::cout << lineNumber << ": " << line << "\n";
        }
        ++lineNumber;
    }

    return 0;
}
