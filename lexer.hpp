#pragma once

#pragma once

#include <string>
#include <vector>
#include "token.hpp"

class Lexer
{
public:
    std::vector<Token> tokenize(const std::string& source);

private:
    TokenType classify(const std::string& text);
};
