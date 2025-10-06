#include "../include/regex/dfa.hpp"
#include <iostream>
#include <queue>
#include <map>

void freeDFA(DFA &dfa)
{
    for (DFAState *dfaState : dfa.states)
    {
        delete dfaState;
    }
    dfa.states.clear();
    dfa.states.shrink_to_fit();
}

bool containsAcceptState(const std::set<State *> &states, State *accept)
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
    std::set<State *> epselonStates;
    std::queue<State *> q;
    for (State *s : states)
    {
        q.push(s);
    }
    while (!q.empty())
    {
        State *currState = q.front();
        epselonStates.insert(currState);
        q.pop();

        for (State *child : currState->epsilonTransitions)
        {
            if (!epselonStates.count(child))
            {
                q.push(child);
            }
        }
    }
    return epselonStates;
}

std::set<State *> move(const std::set<State *> &states, char symbol)
{
    std::set<State *> nextStates;

    for (State *s : states)
    {
        for (const Transition &trans : s->transitions)
        {
            if (trans.symbol == symbol)
            {
                nextStates.insert(trans.target);
            }
        }
    }
    return nextStates;
}

DFA convertNFAtoDFA(const NFA &nfa, const std::set<char> &alphabet)
{
    std::map<std::set<State *>, DFAState *> subsetToDFA;
    std::queue<std::set<State *>> unmarked;

    int nextId = 0;
    std::set<State *> startClosure = epsilonClosure({nfa.start});
    DFAState *start = new DFAState{nextId++, containsAcceptState(startClosure, nfa.accept), {}, startClosure};
    DFA dfa;
    dfa.start = start;
    dfa.states.push_back(start);
    unmarked.push(startClosure);
    subsetToDFA[startClosure] = start;

    while (!unmarked.empty())
    {
        std::set<State *> currentState = unmarked.front();
        unmarked.pop();
        for (char token : alphabet)
        {
            std::set<State *> nextState = move(currentState, token);
            std::set<State *> nextStateEps = epsilonClosure(nextState);
            DFAState *target;
            if (!subsetToDFA.count(nextStateEps))
            {
                target = new DFAState{nextId++, containsAcceptState(nextStateEps, nfa.accept), {}, nextStateEps};
                subsetToDFA[nextStateEps] = target;
                dfa.states.push_back(target);
                unmarked.push(nextStateEps);
            }
            else
            {
                target = subsetToDFA[nextStateEps];
            }

            subsetToDFA[currentState]->transitions[token] = target;
        }
    }
    return dfa;
}
