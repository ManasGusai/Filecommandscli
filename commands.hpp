#pragma once

#include <vector>
#include <string>

extern const std::vector<std::string> available_commands;
extern const std::vector<std::string> options;

struct Command {
   std::string name;
   std::vector<std::string> args;
};
