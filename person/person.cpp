#include ".\person.hpp"

Person::Person(const unsigned int identity, std::string name)
{
    id = identity;
    this->name = name;
}

const unsigned int Person::getId()
{
    return id;
}

std::string Person::getName()
{
    return name;
}

std::vector<Vehicle> Person::getOwnedVehicles()
{
    return ownedVehicles;
}

void Person::addVehicle(Vehicle* vehicle)
{
    ownedVehicles.push_back(*vehicle);
}

void Person::removeVehicle(Vehicle *vehicle)
{
    std::size_t vehiclesCount = ownedVehicles.size();
    for (size_t i = 0; i < vehiclesCount; i++)
    {
        if (&ownedVehicles.at(i) == vehicle)
        {
            ownedVehicles.erase(ownedVehicles.begin() + i, ownedVehicles.begin()+i+1);
        }
    }
}
void Person::printWitnoutVehicles()
{
    std::cout << "name: " << name << std::endl;
    std::cout << "id: " << id << std::endl;
}

void Person::print()
{
    printWitnoutVehicles();

    std::cout << "list of owned vehicles: " << std::endl;  

    for (Vehicle& currentVehicle: ownedVehicles)
    {
        currentVehicle.printWithoutOwner();
    }
    
}