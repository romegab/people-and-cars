#include "personFactory.hpp"

bool PersonFactory::isIdUnique(const unsigned int id)
{
    for (unsigned int currentRegistration: identities)
    {
        if (currentRegistration == id)
        {
            return false;
        }  
    }

    return true;
}

Person* PersonFactory::createPerson(const unsigned int id, const std::string name)
{
    if (name.empty())
    {
        throw std::invalid_argument("cannot create person without name");
    }
    if (!isIdUnique(id))
    {
        throw std::invalid_argument("every person must have unique id");
    }
    identities.push_back(id);
    Person *person = new Person(id, name);

    return person;
}