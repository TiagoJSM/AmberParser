#include "catch2/catch.hpp"

#include <iostream>
#include <filesystem>
#include <sstream>

#include "Parser/Parser.h"
#include "BuildGeneration/RegistrationFile.hpp"

static std::string ReadFile(std::string&& path)
{
    std::ifstream stream(path);
    return std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
}

static void ParseAndCompare(std::string&& cppFile, std::string&& resultFile)
{
    std::stringstream output;

    AP::Parser parser;
    auto translationUnitDesc = parser.Parse(cppFile);
    AP::RegistrationFile file;
    file.Write(output, translationUnitDesc);
    auto outputStr = output.str();
    auto result = ReadFile(std::move(resultFile));

    REQUIRE(outputStr == result);
}

TEST_CASE("ParserOutput Tests", "[ParserOutput]")
{
    SECTION("Parse different compound types in single file")
    {
        ParseAndCompare("TestFiles/DifferentCompounds.hpp", "ResultFiles/DifferentCompounds");
    }

    SECTION("Parse different compound types in single file with base classes")
    {
        ParseAndCompare("TestFiles/BaseClass.hpp", "ResultFiles/BaseClass");
    }

    SECTION("Parse different compound types in single file with base template classes")
    {
        ParseAndCompare("TestFiles/TemplateBase.hpp", "ResultFiles/TemplateBase");
    }
}
