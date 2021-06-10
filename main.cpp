#include <iostream>
#include <vector>
#include <string>
#include ".\\commandExecutor\\commandExecutor.hpp"
#include ".\\fileOperator\\FileOperator.hpp"
#include ".\\exceptions\\fileException.cpp"

std::string charArrayToString(char array[])
{
    std::string result = "";
    int counter = 0;

    while (array[counter])
    {
        result.push_back(array[counter]);
        ++counter;
    }

    return result;
}

int main(int argc, char *argv[])
{
    FileOperator fileOperator;
    CommandExecutor commandExecutor;
    std::string input;

    if (argc >1)
    {
        std::string filePath = charArrayToString(argv[1]);
        try
        {
            fileOperator.openFile(filePath);
            std::vector<std::string> commands = fileOperator.getAllCommands();

            for (std::string currentCommand: commands)
            {
                std::cout << currentCommand<<std::endl;
                commandExecutor.ExecuteCommand(currentCommand);
            }
            
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << e.what() << '\n';
            std::cout << "----------";
            commandExecutor.clearAllObjects();
        }   
    }

    std::getline(std::cin, input);
    while(input != "end")
    {
        try
        {
            commandExecutor.ExecuteCommand(input);
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << e.what() << '\n';
        }    

        std::getline(std::cin, input);    
    }

    commandExecutor.clearAllObjects();

    return 0;
}

