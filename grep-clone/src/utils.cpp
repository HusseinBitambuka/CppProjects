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
