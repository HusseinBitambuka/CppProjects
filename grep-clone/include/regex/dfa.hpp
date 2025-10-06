#pragma once
#include "../regex/utils.hpp" // for State, Transition, etc.
#include "../include/regex/nfa.hpp"
#include <map>
#include <set>

// -----------------------------
// DFA Core Structures
// -----------------------------

struct DFAState
{
    int id;
    bool isAccepting;
    std::map<char, DFAState *> transitions; // deterministic transitions
    std::set<State *> nfaStates;            // NFA states this DFA state represents
};

struct DFA
{
    DFAState *start;
    std::vector<DFAState *> states; // for memory management
};

// -----------------------------
// DFA Construction API
// -----------------------------

/**
 * Convert an NFA to its equivalent DFA using subset construction.
 * @param nfa - input NFA.
 * @param alphabet - set of valid input symbols (non-operators).
 * @return A fully constructed DFA.
 */
DFA convertNFAtoDFA(const NFA &nfa, const std::set<char> &alphabet);

/**
 * Compute the epsilon-closure of a set of NFA states.
 */
std::set<State *> epsilonClosure(const std::set<State *> &states);

/**
 * Move operation: given a set of NFA states and a symbol, find all reachable states.
 */
std::set<State *> move(const std::set<State *> &states, char symbol);

/**
 * Helper to check if any state in a set is an accepting NFA state.
 */
bool containsAcceptState(const std::set<State *> &states, State *accept);

/**
 * Clean up all allocated DFA states.
 */
void freeDFA(DFA &dfa);

/**
 * Print the DFA transitions (for debugging and visualization).
 */
void printDFA(const DFA &dfa);
