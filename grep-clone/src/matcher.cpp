#include "../include/regex/matcher.hpp"
#include <iostream>

std::vector<std::pair<size_t, size_t>> findAllMatches(const DFA &dfa, const std::string &input)
{
    std::vector<std::pair<size_t, size_t>> matches;

    if (!dfa.start)
        throw std::invalid_argument("DFA has no start state");

    for (size_t i = 0; i < input.size(); ++i)
    {
        DFAState *current = dfa.start;

        for (size_t j = i; j < input.size(); ++j)
        {
            auto it = current->transitions.find(input[j]);
            if (it == current->transitions.end())
                break;

            current = it->second;
            if (current->isAccepting)
            {
                matches.push_back({i, j});
                break; // start new search after this match
            }
        }
    }
    return matches;
}

DFA compileDFA(const std::string &pattern)
{
    try
    {
        //   Parse regex into concatenated form
        std::vector<char> concatRegex = addConcatenation(pattern);

        //   Convert to postfix (Shunting Yard)
        std::queue<char> postfix = getPostfix(concatRegex);

        //   Build NFA (Thompson construction)
        NFA nfa = buildNFA(postfix);

        //   Extract alphabet from pattern
        std::set<char> alphabet = extractSymbolsFromRegex(pattern);

        //   Convert NFA → DFA (Subset construction)

        DFA dfa = convertNFAtoDFA(nfa, alphabet);

        freeNFA(nfa);
        return dfa;
    }
    catch (const std::exception &e)
    {
        std::cerr << "[Regex Error] " << e.what() << "\n";
        return DFA{};
    }
}

void matchRegex(const DFA &compiledDFA, const std::string &line)
{
    std::vector<std::pair<size_t, size_t>> matches = findAllMatches(compiledDFA, line);
    printHighlightedLine(line, matches);
}
