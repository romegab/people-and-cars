#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "../registration/registration.hpp"
#include "../factories/registrationFactory/registrationFactory.hpp"

TEST_CASE("registration factory")
{
    Registration registration;
    RegistrationFactory registrationFactory;

    SECTION("testing registration with valid 7 elments value")
    {
        char value [8] = "X0853KP";
        
        REQUIRE_NOTHROW(registration = *(registrationFactory.createRegistration(value)));
    }

    SECTION("testing registration with valid 8 elments value")
    {
        char value [9]  = "PB0853KP";

        REQUIRE_NOTHROW(registration = *(registrationFactory.createRegistration(value)));
    }

    SECTION("testing registration with invalid lenght value (less elements) ")
    {
        char value [3]  = "70";

        REQUIRE_THROWS_AS(registration = *(registrationFactory.createRegistration(value)), std::invalid_argument);
    }

    SECTION("testing registration with invalid lenght value (more elements)")
    {
        char value [10]  = "XX0853KPP";

        REQUIRE_THROWS_AS(registration = *(registrationFactory.createRegistration(value)), std::invalid_argument);
    }

    SECTION("testing registration with valid lenght and missing starting letter")
    {
        char value [8]  = "00853KP";

        REQUIRE_THROWS_AS(registration = *(registrationFactory.createRegistration(value)), std::invalid_argument);
    }

    SECTION("testing registration with valid lenght and too much starting letters")
    {
        char value [8]  = "XYZ53KP";

        REQUIRE_THROWS_AS(registration = *(registrationFactory.createRegistration(value)), std::invalid_argument);
    }

    SECTION("testing registration with valid lenght and only one finishing letters")
    {
        char value [8]  = "X08538P";

        REQUIRE_THROWS_AS(registration = *(registrationFactory.createRegistration(value)), std::invalid_argument);
    }

    SECTION("testing registration with valid lenght and without finishing letters")
    {
        char value [8]  = "X085380";

        REQUIRE_THROWS_AS(registration = *(registrationFactory.createRegistration(value)), std::invalid_argument);
    }

    SECTION("testing registration with valid lenght and without four digits")
    {
        char value [8]  = "X08G4KP";

        REQUIRE_THROWS_AS(registration = *(registrationFactory.createRegistration(value)), std::invalid_argument);
    }

    SECTION("testing registration with two same registrations")
    {
        char value [9]  = "PB3454HM";
        registration = *(registrationFactory.createRegistration(value));

        REQUIRE_THROWS_AS(registration = *(registrationFactory.createRegistration(value)), std::invalid_argument);
    }
}