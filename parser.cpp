#include "parser.hpp"
#include "commands.hpp"
#include "debug.h"
#include "token.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

#include "version.hpp"

static void print_version()
{
    std::cout << "fs VERSION: " << app::VERSION << '\n';
}

static void print_help()
{
    std::ifstream file("help.txt");

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
    }

    std::cout << file.rdbuf();

    file.close();    
}

static bool is_available_command(const std::string& text)
{
    for (const auto& command : available_commands)
    {   
        if (text == command)
            return true;
    }

    return false;
}

static bool is_available_option(const std::string& text)
{
    for (const auto& option : options)
    {
        if (text == option)
            return true;
    }

    return false;
}

static void print_available_commands() {
    for(const auto& c : available_commands) {
        std::cout << c << "\n";
    }
}

static void print_available_options() {
    for(const auto& o : options) {
        std::cout << o << "\n";
    }
}

static void print_ls() {
    for(const auto& entry : fs::recursive_directory_iterator(".")) {
        std::cout << entry.path() << "\n";
    }
}

Command Parser::parse(const std::vector<Token>& tokens)
{
    bool option_flag = false;

    if(debug) {
        std::cout << "PARSING DATA" << std::endl;
        if(debug) {
            std::cout << "Available Commands:\n";
            print_available_commands();
            std::cout << "Available Options:\n";
            print_available_options();
        }
        
        for(const auto& token : tokens){
            std::cout << "Parsing " << token.text
            << " of type " << tokenTypeName(token.type)
             << std::endl;
        }
    }
    
    if (tokens.empty())
    {
        throw std::runtime_error("Tokens empty");
    }

    if (!is_available_command(tokens[0].text) &&
    !is_available_option(tokens[0].text))
    {
        std::cout << tokens[0].text << "\n";
        throw std::runtime_error(
            "Unknown command or option: " + tokens[0].text
        );
    }

    if (tokens[0].type != TokenType::Keyword)
    {
        throw std::runtime_error("expected an identifier");
    }

    if (tokens[0].text == "make")
    {
        return parseMake(tokens);
    }
    
    else if (tokens[0].text == "remove")
    {
        return parseRemove(tokens);
    }
    
    else if (tokens[0].text == "copy")
    {
        return parseCopy(tokens);
    }
    
    else if (tokens[0].text == "rename")
    {
        return parseRename(tokens);
    }
    else if (tokens[0].text == "--help")
    {
        option_flag = true;
        print_help();
    }

    else if (tokens[0].text == "--version")
    {
        option_flag = true;
        print_version();
    }

    else if (tokens[0].text == "-ls")
    {
        option_flag = true;
        print_ls();
    }

    if (is_available_option(tokens[0].text)){
        Command c;
        c.name = "options";
        c.args = {};
        return c;
    }

    if(!option_flag){
        if (tokens.size() < 2)
        {
            throw std::runtime_error("expected an identifier");
        }

        if (tokens[1].type != TokenType::Identifier)
        {
            throw std::runtime_error("expected an identifier");
        }
    }

    std::cout << "Valid command!\n";
    return {};
}

Command Parser::parseMake(const std::vector<Token>& tokens)
{
    if (tokens.size() < 3)
    {
        throw std::runtime_error("Invalid make command");
    }

    if (tokens[1].text != "folder" &&
        tokens[1].text != "file")
    {
        throw std::runtime_error(
            "Expected 'folder' or 'file'");
    }

    Command command;

    command.name = "make";

    command.args.push_back(tokens[1].text);

    for (size_t i = 2; i < tokens.size(); ++i)
    {
        if(tokens[i].type == TokenType::Identifier){           
            command.args.push_back(tokens[i].text);
        }
    }

    return command;
}

Command Parser::parseRemove(const std::vector<Token>& tokens)
{
    if (tokens.size() < 3)
    {
        throw std::runtime_error("Invalid remove command");
    }

    if (tokens[1].text != "folder" &&
        tokens[1].text != "file")
    {
        throw std::runtime_error(
            "Expected 'folder' or 'file'");
    }

    Command command;

    command.name = "remove";

    command.args.push_back(tokens[1].text);

    for (size_t i = 2; i < tokens.size(); ++i)
    {
        if(tokens[i].type == TokenType::Identifier){           
            command.args.push_back(tokens[i].text);
        }
    }

    return command;
}

Command Parser::parseCopy(const std::vector<Token>& tokens)
{
    if (tokens.size() < 3)
    {
        throw std::runtime_error("Invalid copy command");
    }

    // if (tokens[1].text != "folder" &&
    //     tokens[1].text != "file")
    // {
    //     throw std::runtime_error(
    //         "Expected 'folder' or 'file'");
    // }

    Command command;

    command.name = "copy";

    command.args.push_back(tokens[1].text);

    for (size_t i = 2; i < tokens.size(); ++i)
    {
        if(tokens[i].type == TokenType::Identifier){           
            command.args.push_back(tokens[i].text);
        }
    }

    return command;
}

Command Parser::parseRename(const std::vector<Token>& tokens)
{
    if (tokens.size() < 2)
    {
        throw std::runtime_error("Invalid rename command");
    }

    Command command;

    command.name = "rename";

    command.args.push_back(tokens[1].text);

    for (size_t i = 2; i < tokens.size(); ++i)
    {
        if(tokens[i].type == TokenType::Identifier){           
            command.args.push_back(tokens[i].text);
        }
    }

    return command;
}
