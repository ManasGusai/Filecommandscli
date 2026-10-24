#pragma once

#include <string>
#include <vector>

enum class TokenType {
    Identifier,
    Keyword,
    Dot
};

struct Token {
    TokenType type;
    std::string text;
};

const char* tokenTypeName(TokenType type);
void token_info(std::vector<Token>& tokens);
