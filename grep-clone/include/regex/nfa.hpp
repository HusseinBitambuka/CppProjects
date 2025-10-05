#pragma once
#include <vector>
#include <set>
#include <queue>

// Forward declaration
struct State;

struct Transition
{
    char symbol;
    State *target;
};

struct State
{
    int id;
    std::vector<Transition> transitions;
    std::vector<State *> epsilonTransitions;
};

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
