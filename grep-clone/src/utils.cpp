#include "../include/regex/utils.hpp"

std::vector<char> extractSymbolsFromRegex(const std::string &regex)
{
    std::vector<char> symbols;

    for (char token : regex)
    {
        if (token != '*' || token != '|' || token != '(' || token != ')')
        {
            symbols.push_back(token);
        }
    }
    return symbols;
}