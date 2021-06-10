#ifndef COMMANDVALIDATOR_H
#define COMMANDVALIDAOR_H

#include<string>

class CommandValidator
{
private:
    void convertCommandToLowerCase(std::string &command);
    std::string findCommandType(const std::string command);
    void trimCommand(std::string &command);
    void removeInsideSpaces(std::string &command);
    bool checkForThreeParameters(std::string command);
    bool checkForTwoParameters(std::string command);

public:
    bool isCommandValid(std::string& command);
};

#endif