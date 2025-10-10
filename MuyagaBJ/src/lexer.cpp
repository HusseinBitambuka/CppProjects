#include <vector>
#include <unordered_map>
#include "../include/token.hpp"
#include "../include/lexer.hpp"

Lexer::Lexer(std::ifstream &source_file) : sourceCode(source_file) {}

void Lexer::tokenizeLine(const std::string &lineText)
{
}

void Lexer::scanToken(const std::string &lineText, size_t &pos)
{
}

std::vector<Token> Lexer::tokenize()
{
}
void Lexer::addToken(TokenType type, const std::string &lexeme)
{
}
