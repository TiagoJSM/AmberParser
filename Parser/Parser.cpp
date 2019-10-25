#include "Parser.h"

#include <iostream>
#include <fstream> 

#include "../Helpers/FileHelper.hpp"

namespace AP
{
	std::ostream& operator<<(std::ostream& stream, const CXString& str)
	{
		stream << clang_getCString(str);
		clang_disposeString(str);
		return stream;
	}

	std::string GenerateMetaPath(std::string filePath)
	{
		auto extension = GetExtension(filePath);
		auto path = RemoveExtension(filePath);
		return path + "_meta." + extension;
	}

	Parser::Parser()
	{
		Emplace("Namespace", &Parser::NamespaceParser);
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

		std::ofstream outfile(GenerateMetaPath(filePath));

		FileDescriptor fileDescriptor;

		CXCursor cursor = clang_getTranslationUnitCursor(unit);
		clang_visitChildren(
			cursor,
			[](CXCursor c, CXCursor parent, CXClientData client_data)
			{
				//auto p1 = clang_getCursorSemanticParent(parent);
				//auto p2 = clang_getCursorLexicalParent(parent);
				Parser* parser = static_cast<Parser*>(client_data);

				std::cout << "parent '" << clang_getCursorSpelling(parent) << "' of kind '"
					<< clang_getCursorKindSpelling(clang_getCursorKind(parent)) << " "
					<< clang_getTypeSpelling(clang_getCursorType(parent)) << " "
					<< clang_getCXXAccessSpecifier(parent) << " ""'\n";

				std::cout << "Cursor '" << clang_getCursorSpelling(c) << "' of kind '"
					<< clang_getCursorKindSpelling(clang_getCursorKind(c)) << " "
					<< clang_getTypeSpelling(clang_getCursorType(c)) << " "
					<< clang_getCXXAccessSpecifier(c) << " ""'\n\n\n";

				auto cxKind = clang_getCursorKindSpelling(clang_getCursorKind(c));
				auto kind = clang_getCString(cxKind);

				auto& parsers = parser->_parsers;
				auto it = parsers.find(kind);
				if (it != parsers.end())
				{
					it->second(c, parent);
				}

				clang_disposeString(cxKind);

				return CXChildVisit_Recurse;
			},
			this);

		clang_disposeTranslationUnit(unit);
		clang_disposeIndex(index);

		return fileDescriptor;
	}

	void Parser::Emplace(const std::string& kind, void (Parser::* parser)(CXCursor cursor, CXCursor parent))
	{
		using std::placeholders::_1;
		using std::placeholders::_2;
		_parsers.emplace(kind, std::bind(parser, this, _1, _2));
	}

	void Parser::NamespaceParser(CXCursor cursor, CXCursor parent)
	{
		
	}
}