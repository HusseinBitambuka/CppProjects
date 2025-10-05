#pragma once
#include "utils.hpp"

struct NFA
{
    State *start;
    State *accept;
    std::vector<State *> pool;
};

// Function declarations
NFA createNFAfromSymbol(char symbol);
NFA &concatenate(NFA &a, NFA &b);
NFA unionize(NFA &a, NFA &b);
NFA compileKleenStar(NFA &b);
NFA buildNFA(std::queue<char> &postfix);
void freeNFA(NFA &nfa);
void printNFA(const NFA &nfa);
