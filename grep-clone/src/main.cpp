#include "../include/regex/parser.hpp"
#include "../include/regex/nfa.hpp"
#include <iostream>
#include <queue>
#include <vector>

int main()
{
    std::vector<std::string> tests = {
        "a",
        "ab",
        "a|b",
        "(ab|c)*",
        "(a|b)*c"};

    for (const std::string &regex : tests)
    {
        try
        {
            // Step 1: Add explicit concatenation
            std::vector<char> concatenated = addConcatenation(regex);

            // Step 2: Convert to postfix
            std::queue<char> postfix = getPostfix(concatenated);

            // Step 3: Build NFA
            NFA nfa = buildNFA(postfix);

            // Step 4: Print NFA transitions
            std::cout << "\nRegex: " << regex
                      << "\nConcatenated: " << std::string(concatenated.begin(), concatenated.end())
                      << "\nPostfix: ";
            std::queue<char> temp = postfix;
            while (!temp.empty())
            {
                std::cout << temp.front();
                temp.pop();
            }
            std::cout << "\n";

            printNFA(nfa);
            freeNFA(nfa);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error processing regex '" << regex << "': " << e.what() << "\n";
        }
    }
}
