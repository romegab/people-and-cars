#include "vehicle.hpp"
#include "..\person\person.hpp"

Vehicle::Vehicle(Registration *registration, std::string description, Person *owner)
{
    this->owner = owner;
    this->registration = registration;
    this->description = description;
}
Vehicle::Vehicle(Registration *registration, std::string description)
{
    this->registration = registration;
    this->description = description;
}
std::string Vehicle::getDescription()
{
    return description;
}

Registration* Vehicle::getRegistration()
{
    return registration;
}

Person* Vehicle::getOwner()
{
    return owner;
}

void Vehicle::setOwner(Person* owner)
{
    this->owner = owner;
}

void Vehicle::printWithoutOwner()
{
    std::cout << "description: " << description << std::endl;
    std::cout << "registration: " << std::endl;
    registration->print();
}

void Vehicle::print()
{
    printWithoutOwner();

    std::cout << "owner: " << std::endl;
    if(owner != nullptr)
    {
        this->owner->printWitnoutVehicles();
    }
    else
    {
        std::cout << "the car is not a property of anyone" << std::endl;
    }
}