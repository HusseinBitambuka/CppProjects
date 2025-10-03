#include "../include/regex/parser.hpp"
#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <queue>
#include <stack>

void checkMatchingParan(const std::string &regex)
{
    std::stack<char> parantheses;

    for (size_t i = 0; i < regex.size(); i++)
    {
        char token = regex[i];
        if (token == '(')
            parantheses.push(token);
        else if (token == ')')
        {
            if (parantheses.empty())
            {
                std::string error =
                    "The position in the error message are index zero based \n Missing a closing parenthesis at position: " + std::to_string(i) + "/n";
                throw std::invalid_argument(error);
            }

            if (parantheses.top() != '(')
            {
                std::string error =
                    "The position in the error message are index zero based \n Missing a closing parenthesis at position: " + std::to_string(i) + "/n";
                throw std::invalid_argument(error);
            }

            parantheses.pop();
        }
    }

    if (!parantheses.empty())
    {
        throw std::invalid_argument("Too many opening parantheses in your input!");
    }
}

std::vector<char> addConcatenation(const std::string &regex)
{
    if (regex.empty())
        throw std::invalid_argument("Regex string must not be empty");
    checkMatchingParan(regex);

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
                processed.push_back('.'); // explicit concat
            }
        }

        processed.push_back(curr);
    }

    return processed;
}

struct opInfo
{
    int precedence;
    bool isLeftAssociative;
};

opInfo getOpInfo(char op)
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
        std::string error = "The character (" + std::to_string(op) + ") is not a a valid ops. here are valid ops(*, ., |)";
        throw std::invalid_argument(error);
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
            // Pop until matching '('
            while (!ops.empty() && ops.top() != '(')
            {
                output.push(ops.top());
                ops.pop();
            }
            ops.pop(); // guaranteed to be '(' because CheckMatchingParan  validated already
        }
        else if (token == '|' || token == '*' || token == '.')
        {
            opInfo currOpInfo = getOpInfo(token);
            while (!ops.empty() && ops.top() != '(')
            {
                opInfo topOpInfo = getOpInfo(ops.top());
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
            ops.push(token); // always push current operator
        }
        else
        {
            // Operand (literal symbol)
            output.push(token);
        }
    }

    // Pop any remaining operators
    while (!ops.empty())
    {
        output.push(ops.top());
        ops.pop();
    }

    return output;
}
int main()
{
    std::vector<std::string> tests = {
        "ab", "abc", "a|b", "(a|b)c", "a*", "(ab)*c", "a*b", "(a(bc))d",
        "((a|b)c)*", "(ab|c)*dc", "ab(b|c*)d", "a(b|c)d*e", "a", "()",
        "a||b", "a*|b", "(a|b)*", "a|(b*)", "(a|b*)(c|d)"};

    for (const std::string &regex : tests)
    {
        try
        {
            std::vector<char> withConcat = addConcatenation(regex);
            std::queue<char> postfix = getPostfix(withConcat);

            // Convert queue into string for printing
            std::string postfixStr;
            while (!postfix.empty())
            {
                postfixStr.push_back(postfix.front());
                postfix.pop();
            }

            std::cout << "Regex: " << regex
                      << "\nConcatenated: " << std::string(withConcat.begin(), withConcat.end())
                      << "\nPostfix: " << postfixStr << "\n\n";
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "Error in regex '" << regex << "': " << e.what() << "\n\n";
        }
    }
}
