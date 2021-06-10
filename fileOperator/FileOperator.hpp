#ifndef FILEOPERATOR_H
#define FILEOPERATOR_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "..\exceptions\fileException.cpp"

class FileOperator
{
private:
    std::string filePath;
    std::ofstream writeFile;
    std::ifstream readFile;

public:
    void openFile(std::string path);
    std::vector<std::string> getAllCommands();
    void addToFile(std::string command);
    bool isFileEmpty();
};

#endif