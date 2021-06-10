#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include"..\commandExecutor\commandExecutor.hpp"

TEST_CASE("commandExecutor")
{
    CommandExecutor commandExecutor;
    std::string command = "";
    std::string createCarCommand = "";
    std::string createPersonCommand = "";
    std::string aquireCommand = "";
    std::string releaseCommand = "";
    std::string showCommand = "";

    SECTION("testing vehicle command")
    {
        command = "vehicle X0853KP \"best bmw ever\"";

        REQUIRE_NOTHROW(commandExecutor.ExecuteCommand(command));
    }

    SECTION("testing create person")
    {
        command = "person \"Ivan Stoilov\" 1345";

        REQUIRE_NOTHROW(commandExecutor.ExecuteCommand(command));
    }

    SECTION("testing create person with invalid id")
    {
        command = "person \"Ivan Stoilov\" 13b5";

        REQUIRE_THROWS_AS(commandExecutor.ExecuteCommand(command), std::invalid_argument);
    }

    SECTION("testing aquire vehicle and person")
    {
        createCarCommand = "vehicle A0853KP \"bmw e91\"";
        createPersonCommand = "person \"Ivan Stoilov\" 853";
        aquireCommand = "acquire 853 A0853KP";
        showCommand = "show VEHICLES";

        commandExecutor.ExecuteCommand(createCarCommand);
        commandExecutor.ExecuteCommand(createPersonCommand);
        commandExecutor.ExecuteCommand(showCommand);

        REQUIRE_NOTHROW(commandExecutor.ExecuteCommand(aquireCommand));
    }

    SECTION("testing release command")
    {
        createCarCommand = "vehicle A0853KP \"bmw e91\"";
        createPersonCommand = "person \"Ivan Stoilov\" 853";
        aquireCommand = "acquire 853 A0853KP";
        releaseCommand = "release 853 A0853KP";
        showCommand = "show VEHICLES";

        commandExecutor.ExecuteCommand(createCarCommand);
        commandExecutor.ExecuteCommand(createPersonCommand);
        commandExecutor.ExecuteCommand(aquireCommand);
        commandExecutor.ExecuteCommand(showCommand);

        REQUIRE_NOTHROW(commandExecutor.ExecuteCommand(releaseCommand));
    }

    SECTION("testing show command")
    {
        createCarCommand = "vehicle X1353BP \"bmw \"";
        createPersonCommand = "person \"Ivan Stoilov\" 1234";
        aquireCommand = "acquire 1234 X1353BP";
        showCommand = "show VEHICLES";

        commandExecutor.ExecuteCommand(createCarCommand);
        commandExecutor.ExecuteCommand(createPersonCommand);
        commandExecutor.ExecuteCommand(aquireCommand);
        commandExecutor.ExecuteCommand(showCommand);

    }
}