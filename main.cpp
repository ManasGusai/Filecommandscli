#include <iostream>
#include "lexer.hpp"
#include "parser.hpp"
#include "token.hpp"
#include "executor.hpp"
#include "debug.h"

int main(int argc, char *argv[])
{
    Lexer lexer;
    Executor executor;

    std::string input;

    if(argc > 1)
    {
        for(int i = 1; i < argc; i++)
        {
            input += argv[i];
            if(i < argc - 1){
                input += " ";
            }
        }

        Parser parser;

        try
        {
            auto tokens = lexer.tokenize(input);
            Command command = parser.parse(std::move(tokens));
            if(debug){
                std::cout << "Command name: " << command.name << '\n';

                for (const auto& arg : command.args)
                {
                std::cout << "Arg: " << arg << '\n';
                }
            }
            
            executor.execute(command);           
        }
        catch (const std::runtime_error& e)
        {
            std::cerr << "Error: " << e.what() << '\n';
        }     
    }else{
        print_help();
    }

    return 0;
}

