#include "../include/regex/matcher.hpp"
#include <iostream>

bool simulateDFA(const DFA &dfa, const std::string &input)
{
    if (!dfa.start)
    {
        throw std::invalid_argument("DFA has no start state");
    }

    DFAState *current = dfa.start;

    for (char ch : input)
    {
        auto it = current->transitions.find(ch);
        if (it == current->transitions.end())
        {
            return false; // No transition → reject
        }
        current = it->second;
    }

    return current->isAccepting;
}

bool matchRegex(const std::string &pattern, const std::string &input)
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

        //   Simulate DFA
        bool result = simulateDFA(dfa, input);

        freeNFA(nfa);
        freeDFA(dfa);

        return result;
    }
    catch (const std::exception &e)
    {
        std::cerr << "[Regex Error] " << e.what() << "\n";
        return false;
    }
}
