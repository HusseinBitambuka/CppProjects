#include "../include/regex/parser.hpp"
#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>

std::string addConcatenation(const std::string &regex)
{
    if (regex.empty())
        throw std::invalid_argument("Regex string must not be empty");

    std::string processed;

    for (size_t i = 0; i < regex.size(); ++i)
    {
        char curr = regex[i];

        if (i > 0)
        {
            char prev = regex[i - 1];

            bool prev_is_atom = (prev != '|' && prev != '(');
            bool curr_is_atom = (curr != '|' && curr != ')' && curr != '*');

            if (prev_is_atom && curr_is_atom)
            {
                processed.push_back('.'); // explicit concat
            }
        }

        processed.push_back(curr);
    }

    return processed;
}
int main()
{

    std::vector<std::string> tests = {
        "ab", "abc", "a|b", "(a|b)c", "a*", "(ab)*c", "a*b", "(a(bc))d",
        "((a|b)c)*", "(ab|c)*dc", "ab(b|c*)d", "a(b|c)d*e", "a", "()",
        "a||b", "a*|b", "(a|b)*", "a|(b*)", "(a|b*)(c|d)"};

    for (auto regex : tests)
    {
        std::cout << "the regular expression is: " << regex << " and the full concatenated is: " << addConcatenation(regex) << "\n";
    }
}