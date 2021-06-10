#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "..\factories\personFactory\personFactory.hpp"
#include "..\person\person.hpp"

TEST_CASE("personFactory")
{
    PersonFactory personFactory;
    std::string name = "Ivan";
    std::string emptyString = "";
   
    SECTION("testng creatingPerson function")
    {
        Person* person = personFactory.createPerson(1, name);

        REQUIRE(person->getName() == name);
        REQUIRE(person->getId() == 1);
    }

    SECTION("testng setting unique id functionality")
    {
        Person* person = personFactory.createPerson(2, name);

        REQUIRE(person->getId() == 2);
    }

    SECTION("testing setting person name to empty string")
    {
        REQUIRE_THROWS_AS(personFactory.createPerson(3, emptyString), std::invalid_argument);
    }

}