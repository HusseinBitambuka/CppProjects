#include "../include/regex/parser.hpp"
#include <stdexcept>
#include <stack>

// Function definitions
void checkMatchingParens(const std::string &regex)
{
    std::stack<char> parens;
    for (size_t i = 0; i < regex.size(); i++)
    {
        char token = regex[i];
        if (token == '(')
        {
            parens.push(token);
        }
        else if (token == ')')
        {
            if (parens.empty() || parens.top() != '(')
            {
                throw std::invalid_argument("Unmatched parenthesis at position: " + std::to_string(i));
            }
            parens.pop();
        }
    }
    if (!parens.empty())
    {
        throw std::invalid_argument("Too many opening parentheses in your input!");
    }
}

std::vector<char> addConcatenation(const std::string &regex)
{
    if (regex.empty())
        throw std::invalid_argument("Regex string must not be empty");
    checkMatchingParens(regex);

    std::vector<char> processed;
    for (size_t i = 0; i < regex.size(); ++i)
    {
        char curr = regex[i];
        if (i > 0)
        {
            char prev = regex[i - 1];
            bool prev_is_atom = (prev != '|' && prev != '(');
            bool curr_is_atom = (curr != '|' && curr != ')' && curr != '*');
            if (prev_is_atom && curr_is_atom)
            {
                processed.push_back('.');
            }
        }
        processed.push_back(curr);
    }
    return processed;
}

OpInfo getOpInfo(char op)
{
    switch (op)
    {
    case '*':
        return {3, false};
    case '.':
        return {2, true};
    case '|':
        return {1, true};
    default:
        throw std::invalid_argument(
            "Invalid operator: " + std::string(1, op) + " (valid: *, ., |)");
    }
}

std::queue<char> getPostfix(const std::vector<char> &concatRegex)
{
    std::queue<char> output;
    std::stack<char> ops;

    for (char token : concatRegex)
    {
        if (token == '(')
        {
            ops.push(token);
        }
        else if (token == ')')
        {
            while (!ops.empty() && ops.top() != '(')
            {
                output.push(ops.top());
                ops.pop();
            }
            ops.pop();
        }
        else if (token == '|' || token == '*' || token == '.')
        {
            OpInfo currOpInfo = getOpInfo(token);
            while (!ops.empty() && ops.top() != '(')
            {
                OpInfo topOpInfo = getOpInfo(ops.top());
                if (topOpInfo.precedence > currOpInfo.precedence ||
                    (topOpInfo.precedence == currOpInfo.precedence && currOpInfo.isLeftAssociative))
                {
                    output.push(ops.top());
                    ops.pop();
                }
                else
                {
                    break;
                }
            }
            ops.push(token);
        }
        else
        {
            output.push(token);
        }
    }
    while (!ops.empty())
    {
        output.push(ops.top());
        ops.pop();
    }
    return output;
}
