#ifndef REGISTRATIONFACTORY_H
#define REGISTRATIONFACTORY_H

#include "..\..\registration\registration.hpp"
#include <vector>

class RegistrationFactory
{
private:
    std::vector<Registration> registrations;
    bool isRegistrationValid(const char *registration);
    bool isRegistrationUnique(const Registration& registration);

public:
    Registration *createRegistration( char *registration);
};

#endif