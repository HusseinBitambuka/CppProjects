#pragma once
#include <string>
#include <unordered_map>

enum class TokenType
{
    // End of file
    EndOfFile,

    // Identifiers and literals
    Identifier,
    Number,
    CharLiteral,
    StringLiteral,

    // Keywords
    Let,
    Func,
    Return,
    While,
    If,
    Else,
    Print,
    Int,
    Char,
    String,
    Alloc,
    Free,

    // Symbols
    Plus,
    Minus,
    Star,
    Slash,
    Equal,
    EqualEqual,
    NotEqual,
    Less,
    LessEqual,
    Greater,
    GreaterEqual,
    Ampersand,
    LParen,
    RParen,
    LBrace,
    RBrace,
    Comma,
    Semicolon,

    // Invalid / error
    Unknown
};

struct Token
{
    std::string lexeme;
    TokenType type;
    int line;
    int column;

    Token(std::string lex, TokenType t, int l, int c)
        : lexeme(std::move(lex)), type(t), line(l), column(c) {}

    std::string toString() const
    {
        return "Token(" + lexeme + ", " + std::to_string(line) + ":" + std::to_string(column) + ")";
    }
};

inline TokenType getKeywordType(const std::string &word)
{
    static const std::unordered_map<std::string, TokenType> keywords = {
        {"let", TokenType::Let},
        {"func", TokenType::Func},
        {"return", TokenType::Return},
        {"while", TokenType::While},
        {"if", TokenType::If},
        {"else", TokenType::Else},
        {"print", TokenType::Print},
        {"int", TokenType::Int},
        {"char", TokenType::Char},
        {"string", TokenType::String},
        {"alloc", TokenType::Alloc},
        {"free", TokenType::Free}};

    auto it = keywords.find(word);
    if (it != keywords.end())
    {
        return it->second;
    }
    return TokenType::Identifier;
}
