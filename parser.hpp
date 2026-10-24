#pragma once

#include <vector>
#include "commands.hpp"
#include "token.hpp"

void print_help();

class Parser
{
public:
    Command parse(const std::vector<Token>& tokens);

private:
    Command parseMake(const std::vector<Token>& tokens);
    Command parseRemove(const std::vector<Token>& tokens);
    Command parseCopy(const std::vector<Token>& tokens);
    Command parseRename(const std::vector<Token>& tokens);
};
