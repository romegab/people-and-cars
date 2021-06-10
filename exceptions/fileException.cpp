#ifndef FILEEXCEPTION_H
#define FILEEXCEPTION_H
#include<exception>

class FileException: public std::exception
{
public:
    const char *what() const throw()
    {
        return "the file cannot opened";
    }
};

#endif