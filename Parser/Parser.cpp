#include "Parser.h"

#include <iostream>
#include <clang-c/Index.h>

namespace AP
{
	std::ostream& operator<<(std::ostream& stream, const CXString& str)
	{
		stream << clang_getCString(str);
		clang_disposeString(str);
		return stream;
	}

	FileDescriptor Parser::Parse(std::string filePath)
	{
		CXIndex index = clang_createIndex(0, 0);
		CXTranslationUnit unit = clang_parseTranslationUnit(
			index,
			filePath.c_str(), 
			nullptr, 0,
			nullptr, 0,
			CXTranslationUnit_None);
		if (unit == nullptr)
		{
			std::cerr << "Unable to parse translation unit. Quitting." << std::endl;
			exit(-1);
		}

		CXCursor cursor = clang_getTranslationUnitCursor(unit);
		clang_visitChildren(
			cursor,
			[](CXCursor c, CXCursor parent, CXClientData client_data)
			{
				auto p1 = clang_getCursorSemanticParent(parent);
				auto p2 = clang_getCursorLexicalParent(parent);

				std::cout << "parent '" << clang_getCursorSpelling(parent) << "' of kind '"
					<< clang_getCursorKindSpelling(clang_getCursorKind(parent)) << " "
					<< clang_getTypeSpelling(clang_getCursorType(parent)) << " "
					<< clang_getCXXAccessSpecifier(parent) << " ""'\n";

				std::cout << "Cursor '" << clang_getCursorSpelling(c) << "' of kind '"
					<< clang_getCursorKindSpelling(clang_getCursorKind(c)) << " "
					<< clang_getTypeSpelling(clang_getCursorType(c)) << " "
					<< clang_getCXXAccessSpecifier(c) << " ""'\n\n\n";
				return CXChildVisit_Recurse;
			},
			nullptr);

		clang_disposeTranslationUnit(unit);
		clang_disposeIndex(index);
		return FileDescriptor();
	}
}