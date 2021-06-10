#ifndef VEHICLE_H
#define VEHICLE_H

//#include "..\person\person.hpp"
class Person;
#include "..\registration\registration.hpp"
#include <string>

class Vehicle
{
private:
    Registration *registration;
    std::string description;
    Person *owner = nullptr;

public:
    Vehicle(Registration *registration, std::string description, Person *owner);
    Vehicle(Registration *registration, std::string description);

    //getters
    std::string getDescription();
    Registration* getRegistration();
    Person *getOwner();

    //setters
    void setOwner(Person *owner);

    void printWithoutOwner();
    void print();
};

#endif