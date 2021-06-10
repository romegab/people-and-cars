#ifndef DYNAMICMEMORYALLOCATOR_H
#define DYNAMICMEMORYALLOCATOR_H
#include<iostream>

class DynamicArrayHelper
{
public:
    static char* allocateDynamicCharArray(std::size_t size);
    static std::size_t getArrayLenght(const char *string);
    static void stringCopy(char *destination, const char *source);
    static void stringCopy(char *destination, std::string source);
    static void stringCopy(std::string& destination,const char *source);
};

#endif