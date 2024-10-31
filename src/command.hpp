#pragma once

// File is responsable for parsing commands
//
// Similar to that of goldsrc, "bind 'a' jump"
// Command will parse config files or runtime commands 
// issues via a command line
//
//
// Command index:
// bind [key] [action]
// Key = string based key which maps to an SDL key
// action = game based action (forwards, jump, interact)

#include <SDL2/SDL.h>

#include <algorithm>
#include <filesystem>
#include <vector>
#include <fstream>

#include "inputHandler.hpp"
#include "log.hpp"

constexpr size_t numberOfBindArguments = 3;


std::string GetLower(const std::string& str)
{
    std::string retStr = "";
    for (char c : str)
    {
        if ((c <= 'Z') && (c >= 'A'))
            retStr += std::tolower(c);
        else
            retStr += c;
    }
    return retStr;
}

// O(n) time + O(1) space, instead of using map O(1) time + O(n) space
unsigned int GetSDLKey(std::string key_in)
{
    // Get character lowercase
    key_in = GetLower(key_in);

    for (auto& [key, sdlKey] : InputHandler::keyMapping)
    {
        if (key == key_in)
        {
            return sdlKey;
        }
    }
    // Cannot find in map
    return 0;
}

KeyboardActions GetInputAction(std::string action_in)
{
    // Get lowercase
    action_in = GetLower(action_in);

    for (auto& [action, keyboardAction] : InputHandler::actionMapping)
    {
        if (action == action_in)
        {
            return keyboardAction;
        }
    }
    // Cannot find in map
    return KeyboardActions::Unknown;
}


class Command
{
public:
    static std::string ExecuteCommand(const std::string& command_in)
    {
        // Takes the operator command (bind)
        // Can deal with multiple sapces and uppercase
        //
        // If command takes 2 arguments, throw if more are supplied.
        // 

        // Parse the command
        std::vector<std::string> arguments;

        size_t pos = 0;
        while (pos != command_in.npos)
        {
            size_t oldPos = pos;
            pos = command_in.find_first_of(" ", pos);

            if (oldPos != pos)
                arguments.push_back(command_in.substr(oldPos, pos-oldPos));
            
            pos = command_in.find_first_not_of(" ", pos);
        }

        // Execute command
        std::string command = arguments[0];
        if (command == "bind")
        {
            // bind space jump
            if (arguments.size() == numberOfBindArguments)
            {
                unsigned int key = GetSDLKey(arguments[1]);
                KeyboardActions action = GetInputAction(arguments[2]);
                if (key == 0) return "Unknown keyboard bind: " + arguments[1];
                if (action == KeyboardActions::Unknown) return "Unknown action bind: " + arguments[2];

                InputPublisher::GetInstance()->AddBinding(key, action);
            }
        }
        // else if {}
        else
        {
            return "unknown command '" + command + "'";
        }
        return "";
    }

    // Parse config file, executing each line
    static void ParseFile(std::filesystem::path filePath)
    {
        // Any lines with comments (//) will be ignored
        std::ifstream fs;
        if (fs.is_open())
            throw std::runtime_error("File handle is already open.");

        fs.open(filePath, std::ifstream::in);

        std::string line;
        while (std::getline(fs, line))
        {
            // Check for "//"
            size_t pos = line.find_first_not_of(" ");

            // not end and not comment
            if (pos != line.npos && "//" != line.substr(pos, 2))
            {
                std::string ret = ExecuteCommand(line);
                Log::Write("FileParser return: ", ret);
            }
        }        
        fs.close();
    }

};
