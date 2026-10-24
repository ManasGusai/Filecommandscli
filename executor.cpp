#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include "executor.hpp"
#include "debug.h"

namespace fs = std::filesystem;

void Executor::execute(const Command& command)
{
    if (command.name.empty())
    {
        throw std::runtime_error("No command specified");
    }

    if (command.name == "make")
    {
        execute_make(command.args);
    }
    else if (command.name == "remove")
    {
        execute_remove(command.args);
    }
    else if (command.name == "copy")
    {
        execute_copy(command.args);
    }
    else if (command.name == "rename")
    {
        execute_rename(command.args);
    }
}

void Executor::execute_make(const std::vector<std::string>& args)
{
    fs::path base = fs::current_path();

    if (debug)
    {
        for (const auto& arg : args)
            std::cout << "[" << arg << "]\n";
    }

    if (args.empty())
        return;

    // make file ...
    if (args[0] == "file")
    {
        for (size_t i = 1; i < args.size(); ++i)
        {
            fs::path p = base / args[i];

            fs::create_directories(p.parent_path());

            std::ofstream file(p);

            if (!file)
            {
                std::cerr << "Failed to create file: "
                          << p << '\n';
            }
        }

        return;
    }

    // make folder ...
    if (args[0] == "folder")
    {
        fs::path p = base;

        for (size_t i = 1; i < args.size(); ++i)
        {
            if (args[i] == "/")
                continue;

            p /= args[i];

            // No "/" after this means a new independent folder
            if (i + 1 >= args.size() || args[i + 1] != "/")
            {
                fs::create_directories(p);
                p = base;
            }
        }

        return;
    }

    std::cerr << "Unknown make type: " << args[0] << '\n';
}

void Executor::execute_remove(const std::vector<std::string>& args) {
    fs::path base = fs::current_path();

    if (debug)
    {
        for (const auto& arg : args)
            std::cout << "[" << arg << "]\n";
    }

    if(args[0] == "file") {
        fs::path p = base / args[1];
        if(fs::exists(p)) {
            fs::remove(p);
            std::cout << p.filename() << " file deleted" << std::endl;
        }
    }

    if(args[0] == "folder") {
        fs::path p = base / args[1];
        if(fs::exists(p)) {
            fs::remove_all(p);
            std::cout << p.stem() << " folder deleted" << std::endl;
        }
    }

}

void Executor::execute_copy(const std::vector<std::string>& args) {
    fs::path base = fs::current_path();

    if (debug)
    {
        for (const auto& arg : args)
            std::cout << "[" << arg << "]\n";
    }

    fs::path src = base / args[1];
    fs::path dst = base / args[2];

    dst /= src.filename();

    if(debug)
    {
        std::cout << "SRC: " << src << std::endl;
        std::cout << "DST: " << dst << std::endl;
    }

    if(args[0] == "file") {
        if (fs::copy_file(src, dst))
        {
            std::cout << "File " << src << "successfully copied to destination " << dst << std::endl;
        }else{
            throw std::runtime_error("File was not copied");
        }
    }

    if(args[0] == "folder") {
        fs::copy(src,dst);
        std::cout << "Folder " << src << "successfully copied to " << dst << std::endl;
    }
}

void Executor::execute_rename(const std::vector<std::string>& args) {
    fs::path base = fs::current_path();

    if (debug)
    {
        for (const auto& arg : args)
            std::cout << "[" << arg << "]\n";
    }

    fs::path src = base/args[0];
    fs::path dst = base / args[1];

    fs::rename(src, dst);
}