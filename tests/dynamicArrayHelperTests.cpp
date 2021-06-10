#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "../dynamicArrayHelper/dynamicArrayHelper.hpp"

TEST_CASE("dynamicArrayHelper")
{
    SECTION("test allocating array with size equal to 0")
    {
        char *array = nullptr;
        size_t size = 0;

        array = DynamicArrayHelper::allocateDynamicCharArray(size);

        REQUIRE(array == nullptr);
    }

    SECTION("test allocating array")
    {
        char *array = nullptr;
        size_t size = 5;

        array = DynamicArrayHelper::allocateDynamicCharArray(size);

        REQUIRE(array != nullptr);
    }

    SECTION("test getArrayLenght")
    {
        char string[5] = "mate";

        REQUIRE(DynamicArrayHelper::getArrayLenght(string) == 4);
    }

    SECTION("test copyArray with empty destination")
    {
        char string[5] = "mate";
        char *destination = DynamicArrayHelper::allocateDynamicCharArray(5);

        DynamicArrayHelper::stringCopy(destination, string);

        for (int counter = 0; counter < 5; ++counter)
        {
            REQUIRE(destination[counter] == string[counter]);
        }
    }
    
    SECTION("test copyArray with contentful destination")
    {
        char originalString[5] = "mate";
        char secondaryString[7] = "friend";
        char *destination = DynamicArrayHelper::allocateDynamicCharArray(7);

        DynamicArrayHelper::stringCopy(destination, secondaryString);
        DynamicArrayHelper::stringCopy(destination, originalString);

        for (int counter = 0; counter < 5; ++counter)
        {
            REQUIRE(destination[counter] == originalString[counter]);
        }
    }
}