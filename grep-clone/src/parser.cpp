#include "../include/regex/parser.hpp"
#include <string>
#include <stdexcept>

using namespace std;

string addConcatenation(const string &regex)
{
    if (regex.empty())
        throw runtime_error("You did not provide a Regular Expression String");

    string processed;

    for (size_t i = 0; i < regex.size(); ++i)
    {
        char curr = regex[i];

        if (i > 0)
        {
            char prev = regex[i - 1];

            bool prev_is_atom = (isalnum(prev) || prev == ')' || prev == '*');
            bool curr_is_atom = (isalnum(curr) || curr == '(');

            if (prev_is_atom && curr_is_atom)
            {
                processed.push_back('.'); // explicit concat
            }
        }

        processed.push_back(curr);
    }

    return processed;
}
