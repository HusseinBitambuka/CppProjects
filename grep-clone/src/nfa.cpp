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
