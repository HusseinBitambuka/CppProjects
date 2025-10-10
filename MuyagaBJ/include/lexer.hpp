#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "token.hpp"

class Lexer
{
public:
    explicit Lexer(std::ifstream &sourceCode);
    std::vector<Token> tokenize();

private:
    std::ifstream &sourceCode;
    std::vector<Token> tokens;
    int line = 1;
    int column = 0;

    void tokenizeLine(const std::string &lineText);
    void scanToken(const std::string &lineText, size_t &pos);
    void addToken(TokenType type, const std::string &lexeme);
};
