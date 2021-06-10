#include "commandValidator.hpp"
#include <iostream>

void CommandValidator::trimCommand(std::string &command)
{
    //trim left side
    while (command[0] == ' ')
    {
        command.erase(0, 1);
    }

    //trim right side
    std::size_t lastIndex = command.size() - 1;
    
    while (command[lastIndex] == ' ')
    {
        command.erase(lastIndex, 1);
        --lastIndex;
    }
}

void CommandValidator::removeInsideSpaces(std::string &command)
{
    std::size_t commandLenght = command.size();

    for (std::size_t counter = 0; counter < commandLenght - 1; ++counter)
    {      
        if (command[counter] == ' ' && command[counter + 1] == ' ')
        {
            command.erase(counter, 1);
            --counter;
            --commandLenght;
        }
        
        if (command[counter] == '"')
        {
            ++counter;
            while(command[counter] != '"' && counter < commandLenght - 1)
            {                
                ++counter;
            }
        }
    }
    
}

void CommandValidator::convertCommandToLowerCase(std::string &command)
{
    std::size_t commandLenght = command.size();

    for(int i = 0; i < commandLenght; i++) 
    {
        command.at(i) = tolower(command.at(i));
    }
}

bool CommandValidator::checkForThreeParameters(std::string command)
{
    std::size_t commandLenght = command.size();

    std::string firstParameter = "";
    std::string secondParameter = "";
    std::string thirdParameter = "";

    int currentParameter = 1;

    for (std::size_t i = 0; i < commandLenght; ++i)
    {
        if (currentParameter == 1)
        {
            firstParameter.push_back(command[i]);
        }
        else if (currentParameter == 2)
        {
            secondParameter.push_back(command[i]);
        }
        else if (currentParameter == 3)
        {
            thirdParameter.push_back(command[i]);
        }

        if (command[i] == ' ')
        {
            ++currentParameter;
        }            
    }
            
    if (firstParameter != "" && secondParameter != "" && thirdParameter != "")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CommandValidator::checkForTwoParameters(std::string command)
{
    std::size_t commandLenght = command.size();

    std::string firstParameter = "";
    std::string secondParameter = "";

    int currentParameter = 1;

    for (std::size_t i = 0; i < commandLenght; ++i)
    {
        if (currentParameter == 1)
        {
            firstParameter.push_back(command[i]);
        }
        else if (currentParameter == 2)
        {
            secondParameter.push_back(command[i]);
        }

        if (command[i] == ' ')
        {
            ++currentParameter;
        }            
    }
            
    if (firstParameter != "" && secondParameter != "")
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string CommandValidator::findCommandType(const std::string command)
{
    std::string commandType = command.substr(0, command.find(' '));

    return commandType;
}

bool CommandValidator::isCommandValid(std::string& command)
{
    //validating command
    trimCommand(command);
    removeInsideSpaces(command);

    std::string commandType = findCommandType(command);
    convertCommandToLowerCase(commandType);
    
    if (commandType == "save")
    {
        if (command.size() == 4)
        {
            return true;
            command.replace(0,4,commandType);
        }
        else
        {
            if(checkForTwoParameters(command))
            {
                return true;
            }

            throw std::invalid_argument("the command is invalid! peobably it is missing an argument!");
        }
        
    }
    else if(commandType == "vehicle")
    {
        if (checkForThreeParameters(command))
        {
            command.replace(0,7,commandType);
            return true;
        }
        
        throw std::invalid_argument("the command is invalid! peobably it is missing an argument!");
    }
    else if(commandType == "person")
    {
        if (checkForThreeParameters(command))
        {
            command.replace(0,6,commandType);
            return true;
        }
        
        throw std::invalid_argument("the command is invalid! peobably it is missing an argument!");
    }
    else if(commandType == "acquire")
    {
        if (checkForThreeParameters(command))
        {
            command.replace(0,7,commandType);
            return true;
        }
        
        throw std::invalid_argument("the command is invalid! peobably it is missing an argument!");
    }
    else if (commandType == "release")
    {
        if (checkForThreeParameters(command))
        {
            command.replace(0,7,commandType);
            return true;
        }
        
        throw std::invalid_argument("the command is invalid! peobably it is missing an argument!");
    }
    else if (commandType == "show")
    {
        if (checkForTwoParameters(command))
        {
            command.replace(0,4,commandType);
            return true;
        }
        
        throw std::invalid_argument("the command is invalid! probably it is missing an argument!");
    }
    else if (commandType == "remove")
    {
        if (checkForTwoParameters(command))
        {
            command.replace(0,6,commandType);
            return true;
        }
        
        throw std::invalid_argument("the command is invalid! probably it is missing an argument!");
    }
    else
    {
        throw std::invalid_argument("the command is invalid");
    }

    return false;
}