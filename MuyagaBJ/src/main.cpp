#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include "../include/token.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <source_file>\n";
        return 1;
    }

    std::ifstream source(argv[1]);
    if (!source.is_open())
    {
        throw std::runtime_error("Error: could not open file '" + std::string(argv[1]) + "'");
    }

    std::string line;
    size_t count = 0;

    while (std::getline(source, line))
    {
        std::cout << count << ". " << line << "\n";
        count++;
    }

    return 0;
}
