#include <iostream>
#include <clang-c/Index.h>

#include "Parser/Parser.h"

using namespace std;

#define INTERESTING __attribute__((annotate("interesting")))

int main()
{
	AP::Parser::Parse("header.hpp");
}