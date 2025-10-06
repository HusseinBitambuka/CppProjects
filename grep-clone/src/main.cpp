#include "../include/regex/matcher.hpp"
#include <fstream>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: grep_clone <pattern> <file_path>\n";
        return 1;
    }

    std::string pattern = argv[1];
    std::string filePath = argv[2];

    DFA compiled = compileDFA(pattern);

    std::ifstream file(filePath);
    if (!file)
    {
        std::cerr << "Error: cannot open file " << filePath << "\n";
        return 1;
    }

    std::string line;
    int lineNumber = 1;

    while (std::getline(file, line))
    {
        std::cout << lineNumber << ": ";
        matchRegex(compiled, line);
        lineNumber++;
    }

    freeDFA(compiled);
}
