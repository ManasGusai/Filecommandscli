#include "token.hpp"
#include <iostream>

const char* tokenTypeName(TokenType type)
{
    switch (type)
    {
        case TokenType::Identifier:
            return "Identifier";

        case TokenType::Keyword:
            return "Keyword";

        case TokenType::Slash:
            return "Slash";

        case TokenType::Dot:
            return "Dot";
    }

    return "Unknown";
}

void token_info(std::vector<Token>& tokens)
{
    for (const Token& token : tokens)
    {
        std::cout
        << tokenTypeName(token.type)
        << " : "
        << token.text
        << '\n';
    }
}
