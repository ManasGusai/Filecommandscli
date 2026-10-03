#pragma once

#include <vector>
#include <string>
#include "commands.hpp"

class Executor
{
public:
    void execute(const Command& command);

private:
    void execute_make(const std::vector<std::string>& args);
    void execute_remove(const std::vector<std::string>& args);
    void execute_copy(const std::vector<std::string>& args);
    void execute_rename(const std::vector<std::string>& args);

};
