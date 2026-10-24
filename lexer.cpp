#include "lexer.hpp"
#include "commands.hpp"
#include "debug.h"
#include <iostream>

std::vector<Token> Lexer::tokenize(const std::string& source)
{
    if(debug){
        std::cout << "LEXING DATA" << std::endl;
    }

    std::vector<Token> tokens;

    std::string current;

    for (char c : source)
    {
        if (c == ' ')
        {
            if (!current.empty())
            {
                tokens.push_back({
                    classify(current),
                    current
                });

                current.clear();
            }
        }
        // else if (c == '/')
        // {
        //     if (!current.empty())
        //     {
        //         tokens.push_back({
        //             classify(current),
        //             current
        //         });

        //         current.clear();
        //     }

        //     tokens.push_back({
        //         TokenType::Slash,
        //         "/"
        //     });
        // }
        else
        {
            current += c;
        }
    }

    if (!current.empty())
    {
        tokens.push_back({
            classify(current),
            current
        });
    }

    return tokens;
}

TokenType Lexer::classify(const std::string& text)
{
    for(const auto& c : available_commands) {
        if(text == c) {
            return TokenType::Keyword;
        }
    }

    for(const auto& o : options) {
        if(text == o) {
            return TokenType::Keyword;
        }
    }

    return TokenType::Identifier;
}
