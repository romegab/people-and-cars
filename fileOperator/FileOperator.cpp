#include "FileOperator.hpp"

void FileOperator::openFile(std::string path)
{
    if (readFile.is_open())
    {
        readFile.close();
    }

    readFile.open(path, std::ifstream::in);
    std::cout << readFile.is_open();

    if (readFile.is_open() == 0)
    {
        throw FileException();
    }

    filePath = path;
    std::cout << filePath;
}

std::vector<std::string> FileOperator::getAllCommands()
{
    std::vector<std::string> commands;
    std::string line;
    std::cout << filePath;
    std::cout << readFile.is_open();

    if (readFile.is_open())
    {
        while ( getline (readFile,line) )
        {
            commands.push_back(line);
        }

        readFile.close();
    }
    else
    {
        throw FileException();
    }

    return commands;
}

bool FileOperator::isFileEmpty()
{
    if(readFile.peek() == std::ifstream::traits_type::eof())
    {
        return true;
    }
    else
    {
        writeFile.open(filePath);
        return false;
    }
}

void FileOperator::addToFile(std::string command)
{
    writeFile << command;
}