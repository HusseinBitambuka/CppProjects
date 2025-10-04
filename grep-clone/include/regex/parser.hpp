#pragma once
#include <string>
#include <vector>
#include <queue>

// Operator info
struct OpInfo
{
    int precedence;
    bool isLeftAssociative;
};

// Public parser API
void checkMatchingParens(const std::string &regex);

std::vector<char> addConcatenation(const std::string &regex);

OpInfo getOpInfo(char op);

std::queue<char> getPostfix(const std::vector<char> &concatRegex);
