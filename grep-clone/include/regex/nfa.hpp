#pragma once
#include <vector>
#include <memory>
#include <set>

struct Transition
{
    char symbol; // e.g., 'a', 'b'
    State *target;
};

struct State
{
    int id;
    std::vector<Transition> transitions;     // labeled edges
    std::vector<State *> epsilonTransitions; // ε edges
};

struct NFA
{
    State *start;
    State *accept;
};

// Public NFA API
NFA buildNFA(const std::queue<char> &postfix);
