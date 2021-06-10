#ifndef VEHICLEFACTORY_H
#define VEHICLEFACTORY_H

#include "..\..\vehicle\vehicle.hpp"
#include"..\..\registration\registration.hpp"

class VehicleFactory
{
public:
    Vehicle &createVehicleWithoutOwner(Registration *registration, std::string description);
};

#endif