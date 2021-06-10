#include "registration.hpp"
#include <exception>
#include "..\dynamicArrayHelper\dynamicArrayHelper.hpp"

void Registration::setRegistration(const char *registration)
{
    if (registration != nullptr)
    {
        std::size_t registrationLenght = DynamicArrayHelper::getArrayLenght(registration) + 1;

        this->registration = DynamicArrayHelper::allocateDynamicCharArray(registrationLenght);
        DynamicArrayHelper::stringCopy(this->registration, registration);
    }
    else
    {
        this->registration = nullptr;
    }
}

const char* Registration::getRegistration()
{
    return registration;
}

Registration::Registration()
{
    registration = nullptr;
}

Registration::Registration(const char *registration)
{
    setRegistration(registration);
}

Registration::Registration(const Registration& source)
{
    if (source.registration == nullptr)
    {
        this->registration = nullptr;
    }
    else
    {
        std::size_t registrationLenght = DynamicArrayHelper::getArrayLenght(source.registration) + 1;

        this->registration = DynamicArrayHelper::allocateDynamicCharArray(registrationLenght);
    
        DynamicArrayHelper::stringCopy(this->registration, source.registration);

    } 
}

Registration::~Registration()
{
    delete[] registration;
    registration = nullptr;
}

bool Registration::operator==(const Registration& registration)
{
    const char *originalRegistration = registration.registration;
    const char *currentRegistration = this->registration;

    if(originalRegistration == nullptr || currentRegistration == nullptr)
    {
        if (originalRegistration == nullptr && currentRegistration == nullptr)
        {
            return true;
        }

        return false;
    }

    std::size_t lenght= DynamicArrayHelper::getArrayLenght(this->registration);
    std::size_t originalLenght= DynamicArrayHelper::getArrayLenght(registration.registration);

    if (lenght != originalLenght)
    {
        return false;
    }
    
    for (size_t counter = 0; counter < lenght; ++counter)
    {
        if (this->registration[counter] != originalRegistration[counter])
        {
            return false;
        }
        
    }

    return true;
}

void Registration::operator=(Registration &registration)
{
    if (this->registration != nullptr)
    {
        delete[] this->registration;
    }

    if(registration.registration == nullptr)
    {
        this->registration = nullptr;
    }
    else
    {
        std::size_t registrationLenght = DynamicArrayHelper::getArrayLenght(registration.registration) + 1;

        this->registration = DynamicArrayHelper::allocateDynamicCharArray(registrationLenght);
    
        DynamicArrayHelper::stringCopy(this->registration, registration.registration);
    }
}

void Registration::print()
{
    std::size_t size = DynamicArrayHelper::getArrayLenght(registration);
    for (size_t i = 0; i < size; i++)
    {
        std::cout << registration[i];
    }

    std::cout << std::endl;
}