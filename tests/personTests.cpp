#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "..\person\person.hpp"
#include "..\vehicle\vehicle.hpp"
#include "..\registration\registration.hpp"

TEST_CASE("person")
{
    Registration registration("X0853KP");
    Vehicle vehicle(&registration, "bmw 330XD");
    Person person(1, "Ivan");

    SECTION("testing getters")
    {
        REQUIRE(person.getId() == 1);
        REQUIRE(person.getName() == "Ivan");
    }

    SECTION("testing adding vehicle")
    {
        person.addVehicle(&vehicle);

        Vehicle &addedVehiclePointer = person.getOwnedVehicles()[0];
        Vehicle *originalVehiclePointer = &vehicle;

        REQUIRE(originalVehiclePointer == &addedVehiclePointer);
    }
}