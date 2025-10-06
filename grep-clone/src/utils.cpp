#include "../include/regex/utils.hpp"

std::set<char> extractSymbolsFromRegex(const std::string &regex)
{
    std::set<char> symbols;

    for (char token : regex)
    {
        // Skip regex operators
        if (token != '*' && token != '|' && token != '(' && token != ')' && token != '.')
        {
            symbols.insert(token);
        }
    }

    return symbols;
}

void printHighlightedLine(const std::string &line, const std::vector<std::pair<size_t, size_t>> &matches)
{
    if (matches.empty())
    {
        std::cout << line << "\n";
        return;
    }

    size_t last = 0;
    for (const auto &[start, end] : matches)
    {
        if (start > last)
            std::cout << line.substr(last, start - last); // print text before match

        std::cout << "\033[1;33m\033[4m" // bold yellow + underline
                  << line.substr(start, end - start + 1)
                  << "\033[0m";

        last = end + 1;
    }

    if (last < line.size())
        std::cout << line.substr(last); // print remainder of line

    std::cout << "\n";
}
