#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "../registration/registration.hpp"
#include "../dynamicArrayHelper/dynamicArrayHelper.hpp"


TEST_CASE("registration")
{
    Registration registration;

    SECTION("testing the deafult constructor")
    {
        REQUIRE(registration.getRegistration() == nullptr);
    }

    SECTION("testing registration lenght with valid 7 elements value")
    {
        char value[8] = "X0853KP";
        registration.setRegistration(value);

        REQUIRE(DynamicArrayHelper::getArrayLenght(registration.getRegistration()) == 7);
    }

    SECTION("testing registration lenght with valid 8 elements value")
    {
        char value[9] = "PB0853KP";
        registration.setRegistration(value);

        REQUIRE(DynamicArrayHelper::getArrayLenght(registration.getRegistration()) == 8);
    }

    SECTION("testing oeprator == with same values")
    {
        char value[8] = "X0853KP";

        registration.setRegistration(value);
        Registration secondRegistration(value);

        REQUIRE((registration == secondRegistration) == true);
    }

    SECTION("testing oeprator == with values with same lenght but different content")
    {
        char value[8] = "X0853KP";
        char secondValue[8] = "A0853KP";

        registration.setRegistration(value);
        Registration secondRegistration(secondValue);

        REQUIRE((registration == secondRegistration) == false);
    }

    SECTION("testing oeprator == with values with different lenght and different content")
    {
        char value[8] = "X0853KP";
        char secondValue[9] = "PB0853KP";

        registration.setRegistration(value);
        Registration secondRegistration(secondValue);

        REQUIRE((registration == secondRegistration) == false);
    }

    SECTION("testing oeprator == with nullptr values")
    {

        registration.setRegistration(nullptr);
        Registration secondRegistration(nullptr);

        REQUIRE((registration == secondRegistration) == true);
    }
    
    SECTION("testing destructor")
    {
        char value[8] = "X0853KP";

        registration.setRegistration(value);
        registration.~Registration();

        REQUIRE(registration.getRegistration() == nullptr);
    }

    SECTION("testing registration getter")
    {
        char value[8] = "X0853KP";

        registration.setRegistration(value);

        const char *registrationValue = registration.getRegistration();

        for (int counter = 0; counter < 7; ++counter)
        {
            REQUIRE(value[counter] == registrationValue[counter]);
        }
    }

    SECTION("testing = operator with empty destination an contentful source")
    {
        char value[8] = "X0853KP";

        registration.setRegistration(value);

        Registration secondaryRegistration;

        secondaryRegistration = registration;

        bool result = secondaryRegistration == registration;

        REQUIRE(result);
    }

    SECTION("testing = operator with contentful destination an contentful source")
    {
        char originalValue[8] = "X0853KP";
        char secondaryValue[8] = "A0853KP";

        registration.setRegistration(originalValue);
        Registration secondaryRegistration(secondaryValue);

        registration = secondaryRegistration;

        bool result = secondaryRegistration == registration;

        REQUIRE(result);
    }

    SECTION("testing = operator with contentfull destination an empty source")
    {
        char value[8] = "X0853KP";

        registration.setRegistration(value);

        Registration secondaryRegistration;

        registration = secondaryRegistration;

        bool result = secondaryRegistration == registration;

        REQUIRE(result);
    }

    SECTION("testing = operator with empty destination and empty source")
    {
        Registration secondaryRegistration;

        secondaryRegistration = registration;

        bool result = secondaryRegistration == registration;

        REQUIRE(result);
    }

    SECTION("testing copy constructor with contentless source")
    {
        Registration secondaryRegistration(registration);

        bool result = secondaryRegistration == registration;

        REQUIRE(result);
    }

    SECTION("testing copy constructor with contentfull source")
    {
        char value[8] = "X0853KP";

        registration.setRegistration(value);
        Registration secondaryRegistration(registration);

        bool result = secondaryRegistration == registration;

        REQUIRE(result);
    }

    SECTION("testing == operator with diferent values")
    {
        char value[8] = "X0853KP";

        registration.setRegistration(value);
        Registration secondaryRegistration;

        bool result = secondaryRegistration == registration;

        REQUIRE(!result);
    }
}