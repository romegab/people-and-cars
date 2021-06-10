#include "dynamicArrayHelper.hpp"

char* DynamicArrayHelper::allocateDynamicCharArray(size_t size)
{
    if (size == 0)
    {
        return nullptr;
    }
    
    char *array = nullptr;

    try
    {
        array = new char[size];
    }
    catch (const std::bad_alloc& exc) 
    {
        throw exc;
    }
    
    return array;
}

std::size_t DynamicArrayHelper::getArrayLenght(const char *string)
{
    if (string == nullptr)
    {
        return 0;
    }

    size_t lenght = 0;
    while (string[lenght])
    {
        ++lenght;
    }  
    
    return lenght;
}

void DynamicArrayHelper::stringCopy(char *destination, const char *source)
{
    int possition = 0;
    while(source[possition]) 
    {
        destination[possition] = source[possition];
        ++possition;
    }
    destination[possition] = '\0';
}

void DynamicArrayHelper::stringCopy(char *destination, std::string source)
{
    std::size_t sourceLenght = source.size();

    for (size_t i = 0; i < sourceLenght; ++i)
    {
        destination[i] = source.at(i);
    }

    destination[sourceLenght] = '\0';
}

void DynamicArrayHelper::stringCopy(std::string& destination,const char *source)
{
    int possition = 0;
    while(source[possition]) 
    {
        destination = destination + source[possition];
        ++possition;
    }    
}