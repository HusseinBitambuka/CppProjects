#include "../include/regex/dfa.hpp"
#include <iostream>
#include <queue>

void freeDFA(DFA &dfa)
{
    for (DFAState *dfaState : dfa.states)
    {
        delete dfaState;
    }
    dfa.states.clear();
    dfa.states.shrink_to_fit();
}

bool containsAccept(const std::set<State *> &states, State *accept)
{

    for (State *s : states)
    {
        if (s == accept)
        {
            return true;
        }
    }
    return false;
}
std::set<State *> epsilonClosure(const std::set<State *> &states)
{
    std::set<State *> res;
    std::queue<State *> q;
    for (State *s : states)
    {
        q.push(s);
    }
    while (!q.empty())
    {
        State *currState = q.front();
        res.insert(currState);
        q.pop();

        for (State *child : currState->epsilonTransitions)
        {
            if (!res.count(child))
            {
                q.push(child);
            }
        }
    }
    return res;
}
