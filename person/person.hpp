#ifndef PERSON_H
#define PERSON_H
#include "..\vehicle\vehicle.hpp"
#include <string>
#include <vector>

class Person
{
private:
    unsigned int id;
    std::string name;
    std::vector<Vehicle> ownedVehicles;

public:
    Person(const unsigned int identity, std::string name);

    //getters
    const unsigned int getId();
    std::string getName();
    std::vector<Vehicle> getOwnedVehicles();

    void addVehicle(Vehicle *vehicle);
    void removeVehicle(Vehicle *vehicle);

    void print();
    void printWitnoutVehicles();
};

#endif