#include "vehicleFactory.hpp"

Vehicle& VehicleFactory::createVehicleWithoutOwner(Registration *registration, std::string description)
{
    if(description.empty())
    {
        throw std::invalid_argument("car cannot be created without description");
    }

    Vehicle *vehicle = new Vehicle(registration, description);

    return *vehicle;
}
