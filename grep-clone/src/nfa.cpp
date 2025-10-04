#include "../include/regex/nfa.hpp"
#include <queue>
#include <stack>

// Global or static counter for debugging
static int GLOBAL_STATE_ID = 0;

State *createState(NFA &nfa)
{
    State *s = new State{GLOBAL_STATE_ID++, {}, {}};
    nfa.pool.push_back(s);
    return s;
}

void freeNFA(NFA &nfa)
{
    for (State *s : nfa.pool)
    {
        delete s;
    }
    nfa.pool.clear();
}

// API for NFA

NFA createNFAfromSymbol(char symbol)
{
    NFA nfa;
    State *start = createState(nfa);
    State *accpet = createState(nfa);
    start->transitions.push_back({symbol, accpet});
    return nfa;
}

NFA &concatenate(NFA &a, NFA &b)
{
    a.accept->epsilonTransitions.push_back(b.start); // link the a accept state with b start state
    a.accept = b.accept;
    a.pool.insert(a.pool.end(), b.pool.begin(), b.pool.end()); // transfer memory ownership to the new NFA
    b.pool.clear();
    return a;
}

NFA &unionize(NFA &a, NFA &b)
{
    // as layed out in the four pages paper attached to the readme, this is how Ken Thompson proposed we do Union

    // create a new state
    NFA res;
    State *start = createState(res);
    State *accept = createState(res);
    res.accept = accept;
    res.start = start;

    // epselon-transition from the start states and the accept states of the a and b NFAs
    start->epsilonTransitions.push_back(a.start);
    start->epsilonTransitions.push_back(b.start);
    a.accept->epsilonTransitions.push_back(accept);
    b.accept->epsilonTransitions.push_back(accept);

    // transfer memory ownership of a and b memory
    res.pool.insert(res.pool.end(), a.pool.begin(), a.pool.end());
    res.pool.insert(res.pool.end(), b.pool.begin(), b.pool.end());

    return res;
}
