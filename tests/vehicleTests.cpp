#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "../registration/registration.hpp"
#include "../vehicle/vehicle.hpp"
#include "../person/person.hpp"


TEST_CASE("Vehicle")
{
    Registration registration("X0853KP");

    const unsigned int identity = 1;
    std::string name = "Ivan";
    Person owner(identity, name);

    SECTION("testing creating vehicle")
    {
        std::string description = "bmw";
        Vehicle vehicle(&registration,description, &owner);

        Person person = *(vehicle.getOwner());
        REQUIRE(vehicle.getDescription() == description);
        REQUIRE(person.getName() == name);
    }
}