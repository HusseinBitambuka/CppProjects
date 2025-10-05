#pragma once
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <set>
#include <iostream>

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

// Utility helpers
std::set<char> extractSymbolsFromRegex(const std::string &regex);
inline bool isEpsilon(char symbol) { return symbol == '\0' || symbol == 'ε'; }
void printState(const State *s);
