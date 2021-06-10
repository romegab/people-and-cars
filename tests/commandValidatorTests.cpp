#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "..\commandsValidator\commandValidator.hpp"

TEST_CASE("commandValidator")
{
    std::string command = "";
    CommandValidator commandValidator;

    SECTION("testing valid save command")
    {
        command = "save";

        REQUIRE(commandValidator.isCommandValid(command));
    }

    SECTION("testing valid save command with spacec to trim")
    {
        command = "   save      ";

        REQUIRE(commandValidator.isCommandValid(command));
        REQUIRE(command == "save");
    }

    SECTION("testing invalid save command")
    {
        command = "s ave";

        REQUIRE_THROWS_AS(commandValidator.isCommandValid(command), std::invalid_argument);
    }

    SECTION("testing valid vehicle command")
    {
        command = "vehicle X0853KP car";

        REQUIRE(commandValidator.isCommandValid(command));
    }

    SECTION("testing valid vehicle command with spaces")
    {
        command = "     vehicle     X0853KP    car    ";

        REQUIRE(commandValidator.isCommandValid(command));
        REQUIRE(command == "vehicle X0853KP car");
    }

    SECTION("testing valid vehicle command with longer description")
    {
        command = "vehicle X0853KP \"grey  bmw     330  xd\" ";

        REQUIRE(commandValidator.isCommandValid(command));
        REQUIRE(command == "vehicle X0853KP \"grey  bmw     330  xd\"");
    }

    SECTION("testing invalid vehicle command")
    {
        command = "vehicle X0853KP ";

        REQUIRE_THROWS_AS(commandValidator.isCommandValid(command), std::invalid_argument);
    }

    SECTION("testing valid person command")
    {
        command = "Person     \"Ivan Stoilov\" 15";

        REQUIRE(commandValidator.isCommandValid(command));
        REQUIRE(command == "person \"Ivan Stoilov\" 15");
    }
}