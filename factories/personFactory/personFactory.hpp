#ifndef PERSONFACTORY_H
#define PERSONFACTORY_H

#include"..\..\person\person.hpp"

class PersonFactory
{
private:
    std::vector<unsigned int> identities;
    bool isIdUnique(const unsigned int id);

public:
    Person *createPerson(const unsigned int id, std::string name);
};

#endif