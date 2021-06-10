#include "registrationFactory.hpp"
#include "..\..\dynamicArrayHelper\dynamicArrayHelper.hpp"
#include<iostream>

bool isCurrentElementALetter(const char element)
{
    if (element >= 65 && element <= 90)
    {
        return true;
    }

    return false;
}

bool isCurrentElementADigit(const char element)
{
    if (element >=45 && element <= 57)
    {
        return true;
    }

    return false;
}

bool RegistrationFactory::isRegistrationValid(const char *registration)
{
    std::size_t registrationLenght = DynamicArrayHelper::getArrayLenght(registration);
    bool isRegistrationValid = true;

    if (registrationLenght == 7 )
    {
        if (!isCurrentElementALetter(registration[0]))
        {
            isRegistrationValid = false;
        }
        else if(!isCurrentElementADigit(registration[1]))
        {
            isRegistrationValid = false;
        }
        else if(!isCurrentElementADigit(registration[2]))
        {
            isRegistrationValid = false;
        }
        else if(!isCurrentElementADigit(registration[3]))
        {
            isRegistrationValid = false;
        }
        else if(!isCurrentElementADigit(registration[4]))
        {
            isRegistrationValid = false;
        }
        else if (!isCurrentElementALetter(registration[5]))
        {
            isRegistrationValid = false;
        }
        else if (!isCurrentElementALetter(registration[6]))
        {
            isRegistrationValid = false;
        }

        return isRegistrationValid;
    }
    else if (registrationLenght == 8)
    {
        if (!isCurrentElementALetter(registration[0]))
        {
            isRegistrationValid = false;
        }
        else if (!isCurrentElementALetter(registration[1]))
        {
            isRegistrationValid = false;
        }
        else if(!isCurrentElementADigit(registration[2]))
        {
            isRegistrationValid = false;
        }
        else if(!isCurrentElementADigit(registration[3]))
        {
            isRegistrationValid = false;
        }
        else if(!isCurrentElementADigit(registration[4]))
        {
            isRegistrationValid = false;
        }
        else if(!isCurrentElementADigit(registration[5]))
        {
            isRegistrationValid = false;
        }
        else if (!isCurrentElementALetter(registration[6]))
        {
            isRegistrationValid = false;
        }
        else if (!isCurrentElementALetter(registration[7]))
        {
            isRegistrationValid = false;
        }

        return isRegistrationValid;
    }
    
    else
    {
        isRegistrationValid = false;
        return isRegistrationValid;
    }
}

bool RegistrationFactory::isRegistrationUnique(const Registration& registration)
{
    bool isUnique = true;

    for (size_t i = 0; i < registrations.size(); i++)
    {
        if (registrations.at(i) == registration)
        {
            isUnique = false;
            break;
        } 
    }
    return isUnique;
}

Registration* RegistrationFactory::createRegistration(char *registration)
{
    bool isValid = isRegistrationValid(registration);

    if (!isValid)
    {
        throw std::invalid_argument("the registration is invalid! Try again.");
    }

    Registration* currentRegistration = new Registration(registration);
 
    if (isRegistrationUnique(*currentRegistration))
    {
        registrations.push_back(*currentRegistration);
        return currentRegistration;
    }
    else
    {
        (*currentRegistration).~Registration();
        throw std::invalid_argument("this registration is existing already. Every registration must be unique!");
    }    
}
