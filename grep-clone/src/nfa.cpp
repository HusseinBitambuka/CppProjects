#include "../include/regex/nfa.hpp"
#include <queue>
#include <stack>
#include <stdexcept>

/*
============================================================
  Thompson NFA Construction Core
  --------------------------------
  This file implements the primitive NFA-building operations
  described in Ken Thompson’s 1968 paper:
  “Regular Expression Search Algorithm” (CACM, Vol. 11, No. 6)

  Each NFA has:
    - start: pointer to the start state
    - accept: pointer to the accept state
    - pool: vector owning all dynamically allocated states

  Memory is managed manually for educational purposes.
============================================================
*/

// Global counter to assign unique state IDs (for debugging/visualization)
static int GLOBAL_STATE_ID = 0;

/*------------------------------------------------------------
  Helper: createState()
  Creates a new State object on the heap, assigns a unique ID,
  and registers ownership in the NFA’s memory pool.
------------------------------------------------------------*/
State *createState(NFA &nfa)
{
  State *s = new State{GLOBAL_STATE_ID++, {}, {}};
  nfa.pool.push_back(s);
  return s;
}

/*------------------------------------------------------------
  Helper: freeNFA()
  Deletes all heap-allocated State objects owned by an NFA.
  This is the only cleanup function you should call once an
  NFA is no longer needed.
------------------------------------------------------------*/
void freeNFA(NFA &nfa)
{
  for (State *s : nfa.pool)
  {
    delete s;
  }
  nfa.pool.clear();
  nfa.pool.shrink_to_fit();
}

/*------------------------------------------------------------
  Base Case: createNFAfromSymbol()
  Creates a simple NFA fragment for a single literal symbol.

        [start] --symbol--> [accept]

------------------------------------------------------------*/
NFA createNFAfromSymbol(char symbol)
{
  NFA nfa{nullptr, nullptr, {}}; // explicit initialization
  State *start = createState(nfa);
  State *accept = createState(nfa);

  start->transitions.push_back({symbol, accept});

  nfa.start = start;
  nfa.accept = accept;
  return nfa;
}

/*------------------------------------------------------------
  Concatenation: concatenate(A, B)
  Implements Thompson’s concatenation rule:

        A.accept --ε--> B.start

  The resulting NFA starts at A.start and accepts at B.accept.
  Memory ownership of B’s states is transferred to A.
------------------------------------------------------------*/
NFA &concatenate(NFA &a, NFA &b)
{
  // Link A’s accept to B’s start using ε-transition
  a.accept->epsilonTransitions.push_back(b.start);

  // Update accept pointer and merge memory pools
  a.accept = b.accept;
  a.pool.insert(a.pool.end(), b.pool.begin(), b.pool.end());

  // Clear B’s pool since ownership is transferred
  b.pool.clear();
  b.pool.shrink_to_fit();

  return a;
}

/*------------------------------------------------------------
  Union: unionize(A, B)
  Implements Thompson’s alternation rule (A|B):

            ε         ε
        -->[A.start]   [B.start]
          ↙              ↘
        [newStart]     [newAccept]
          ↖              ↙
            ε         ε

  Creates a new start and accept state, and connects them to
  both sub-NFAs using ε-transitions.
------------------------------------------------------------*/
NFA unionize(NFA &a, NFA &b)
{
  NFA res{nullptr, nullptr, {}}; // explicit initialization

  State *start = createState(res);
  State *accept = createState(res);
  res.start = start;
  res.accept = accept;

  // Epsilon transitions connecting sub-NFAs
  start->epsilonTransitions.push_back(a.start);
  start->epsilonTransitions.push_back(b.start);
  a.accept->epsilonTransitions.push_back(accept);
  b.accept->epsilonTransitions.push_back(accept);

  // Transfer ownership of all states into the result
  res.pool.insert(res.pool.end(), a.pool.begin(), a.pool.end());
  res.pool.insert(res.pool.end(), b.pool.begin(), b.pool.end());

  // Clear the old pools
  a.pool.clear();
  b.pool.clear();
  a.pool.shrink_to_fit();
  b.pool.shrink_to_fit();

  return res;
}

/*------------------------------------------------------------
  Kleene Star: compileKleenStar(B)
  Implements Thompson’s closure rule (B*):

             ε
        +----------+
        |          |
        v          |
      [newStart] --ε--> [newAccept]
        |          ^
        |          |
        +--> B.start --ε--> B.accept
             ^               |
             |_______________|

  This allows zero or more repetitions of the sub-NFA B.
------------------------------------------------------------*/
NFA compileKleenStar(NFA &b)
{
  NFA res{nullptr, nullptr, {}}; // explicit initialization

  State *start = createState(res);
  State *accept = createState(res);
  res.start = start;
  res.accept = accept;

  // Epsilon transitions per Thompson’s closure construction
  start->epsilonTransitions.push_back(b.start);    // newStart → oldStart
  start->epsilonTransitions.push_back(accept);     // newStart → newAccept
  b.accept->epsilonTransitions.push_back(b.start); // oldAccept → oldStart
  b.accept->epsilonTransitions.push_back(accept);  // oldAccept → newAccept

  // Merge memory ownership
  res.pool.insert(res.pool.end(), b.pool.begin(), b.pool.end());
  b.pool.clear();
  b.pool.shrink_to_fit();

  return res;
}

NFA buildNFA(std::queue<char> &postfix)
{
  std::stack<NFA> stack;

  while (!postfix.empty())
  {
    char token = postfix.front();
    postfix.pop();

    if (token == '*')
    {
      if (stack.empty())
        throw std::runtime_error("Invalid postfix: '*' with empty stack");

      NFA top = std::move(stack.top());
      stack.pop();
      stack.push(compileKleenStar(top));
    }
    else if (token == '.')
    {
      if (stack.size() < 2)
        throw std::runtime_error("Invalid postfix: '.' requires two operands");

      NFA right = std::move(stack.top());
      stack.pop();
      NFA left = std::move(stack.top());
      stack.pop();

      stack.push(concatenate(left, right));
    }
    else if (token == '|')
    {
      if (stack.size() < 2)
        throw std::runtime_error("Invalid postfix: '|' requires two operands");

      NFA right = std::move(stack.top());
      stack.pop();
      NFA left = std::move(stack.top());
      stack.pop();

      stack.push(unionize(left, right));
    }
    else
    {
      stack.push(createNFAfromSymbol(token));
    }
  }

  if (stack.size() != 1)
    throw std::runtime_error("Invalid postfix: leftover NFAs on stack");

  return std::move(stack.top());
}
