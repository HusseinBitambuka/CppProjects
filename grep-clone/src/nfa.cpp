#include "../include/regex/nfa.hpp"
#include <queue>
#include <stack>

NFA doConcatenation(const NFA &first, const NFA &second)
{
    first.accept->epsilonTransitions.push_back(second.start);
    return {first.start, second.accept};
}

NFA buildNFA(const std::queue<char> &postfix)
{
    std::stack<NFA> nfaStack;
    std::queue<char> temp = postfix; // copy, because queue is mutable

    while (!temp.empty())
    {
        char token = temp.front();
        temp.pop();

        if (isalpha(token))
        {
            nfaStack.push(createBasicNFA(token));
        }
        else if (token == '.')
        {
            auto b = nfaStack.top();
            nfaStack.pop();
            auto a = nfaStack.top();
            nfaStack.pop();
            nfaStack.push(doConcatenation(a, b));
        }
        else if (token == '|')
        {
            auto b = nfaStack.top();
            nfaStack.pop();
            auto a = nfaStack.top();
            nfaStack.pop();
            nfaStack.push(doUnion(a, b));
        }
        else if (token == '*')
        {
            auto a = nfaStack.top();
            nfaStack.pop();
            nfaStack.push(doKleeneStar(a));
        }
    }

    return nfaStack.top();
}
