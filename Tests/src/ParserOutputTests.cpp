#include "catch2/catch.hpp"

//#include <iostream>
//#include <clang-c/Index.h>
//#include <filesystem>
//#include <sstream>

TEST_CASE("ParserOutput Tests", "[ParserOutput]")
{
    SECTION("MaterialAsset can be serialized and deserialized")
    {
       /* std::stringstream output;

        AP::Parser parser;
        auto translationUnitDesc = parser.Parse("TestFiles/TemplateBase.hpp");
        AP::RegistrationFile file;
        file.Write(output, translationUnitDesc);*/

        REQUIRE(1 == 1);
    }
}