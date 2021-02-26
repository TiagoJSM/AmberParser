#include <iostream>
#include <clang-c/Index.h>
#include <filesystem>
#include <sstream>

#include "Parser/Parser.h"
#include "BuildGeneration/RegistrationFile.hpp"

using namespace std;

#define INTERESTING __attribute__((annotate("interesting")))

const std::string CMakeFile = "CMakeLists.txt";

int main()
{
	std::filesystem::create_directory("auto-generated");
	std::stringstream output;

	AP::Parser parser;
	auto translationUnitDesc = parser.Parse("TestFiles/TemplateBase.hpp");
	AP::RegistrationFile file;
	file.Write(output, translationUnitDesc);
	auto s = output.str();
}