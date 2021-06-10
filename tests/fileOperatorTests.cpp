#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "..\fileOperator\FileOperator.hpp"

TEST_CASE("file operator")
{
    FileOperator fileOperator;
    std::string filePath ;

    SECTION("testing to open file with invalid path")
    {
        filePath = "D:\\FMI_OOP_CS\\gfdhgnfhm.txt";
        REQUIRE_THROWS_AS(fileOperator.openFile(filePath), std::invalid_argument);
    }

    SECTION("testing to open file with valid path")
    {
        filePath = "D:\\FMI_OOP_CS\\testFile.txt";
        REQUIRE_NOTHROW(fileOperator.openFile(filePath));
    }

    SECTION("testing get command")
    {
        filePath = "D:\\FMI_OOP_CS\\testFile.txt";
        fileOperator.openFile(filePath);
        std::vector<std::string> commands = fileOperator.getAllCommands();

        REQUIRE(commands.at(0) == "PERSON \"IVAN STOILOV\" 12345");
        REQUIRE(commands.at(1) == "VEHICLE X0853KP \"grey bmw\"");
    }
}
