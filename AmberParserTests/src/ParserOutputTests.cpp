#include "catch2/catch.hpp"

#include <iostream>
#include <filesystem>
#include <sstream>

#include "../../AmberParser/Parser/Parser.h"
#include "../../AmberParser/BuildGeneration/RegistrationFile.hpp"

static std::string ReadFile(std::string&& path)
{
    std::ifstream stream(path);
    return std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
}

TEST_CASE("ParserOutput Tests", "[ParserOutput]")
{
    SECTION("Parse different compound types in single file")
    {
       std::stringstream output;

        AP::Parser parser;
        auto translationUnitDesc = parser.Parse("TestFiles/DifferentCompounds.hpp");
        AP::RegistrationFile file;
        file.Write(output, translationUnitDesc);
        auto s = output.str();
        auto result = ReadFile("ResultFiles/DifferentCompounds");

        REQUIRE(s == result);
    }

    SECTION("Parse different compound types in single file with base classes")
    {
        std::stringstream output;

        AP::Parser parser;
        auto translationUnitDesc = parser.Parse("TestFiles/BaseClass.hpp");
        AP::RegistrationFile file;
        file.Write(output, translationUnitDesc);
        auto s = output.str();
        auto result = ReadFile("ResultFiles/BaseClass");

        REQUIRE(s == result);
    }

    SECTION("Parse different compound types in single file with base template classes")
    {
        std::stringstream output;

        AP::Parser parser;
        auto translationUnitDesc = parser.Parse("TestFiles/TemplateBase.hpp");
        AP::RegistrationFile file;
        file.Write(output, translationUnitDesc);
        auto s = output.str();
        auto result = ReadFile("ResultFiles/BaseClass");

        REQUIRE(s == result);
    }
}
