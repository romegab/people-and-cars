#define CATCH_CONFIG_MAIN
#include "catch2.hpp"

#include "../registration/registration.hpp"
#include "../factories/vehicleFactory/vehicleFactory.hpp"
#include "../vehicle/vehicle.hpp"
#include "../person/person.hpp"


TEST_CASE("Vehicle Factory")
{
    char registrationValue[8] = "X0853KP";
    std::string carDescription = "bmw 330xd";
    const unsigned int id = 1;
    std::string name = "Ivan";

    VehicleFactory vehicleFactory;
    Registration registration(registrationValue);
    Person person(id, name);

    SECTION("testing creating vehicle without owner")
    {
        Vehicle vehicle = vehicleFactory.createVehicleWithoutOwner(&registration, carDescription);
        bool result = (*vehicle.getRegistration()) == registration;
        REQUIRE(result);
    }
}