#include "Parser.h"

#include <iostream>
#include <fstream> 

#include "../Helpers/FileHelper.hpp"
#include "../ParsingData/NamespaceDescriptor.h"

namespace AP
{
	std::ostream& operator<<(std::ostream& stream, const CXString& str)
	{
		stream << clang_getCString(str);
		clang_disposeString(str);
		return stream;
	}

	std::string AsString(const CXString& str)
	{
		auto result = clang_getCString(str);
		clang_disposeString(str);
		return result;
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
		ParserClientData clientData(this, fileDescriptor);

		CXCursor cursor = clang_getTranslationUnitCursor(unit);
		clang_visitChildren(
			cursor,
			[](CXCursor c, CXCursor parent, CXClientData client_data)
			{
				auto clientData = static_cast<ParserClientData*>(client_data);
				auto parser = clientData->parser;
				auto& fileDescriptor = clientData->fileDescriptor;

				std::cout << "parent '" << clang_getCursorSpelling(parent) << "' of kind '"
					<< clang_getCursorKindSpelling(clang_getCursorKind(parent)) << " "
					<< clang_getTypeSpelling(clang_getCursorType(parent)) << " "
					<< clang_getCXXAccessSpecifier(parent) << " ""'\n";

				std::cout << "Cursor '" << clang_getCursorSpelling(c) << "' of kind '"
					<< clang_getCursorKindSpelling(clang_getCursorKind(c)) << " "
					<< clang_getTypeSpelling(clang_getCursorType(c)) << " "
					<< clang_getCXXAccessSpecifier(c) << " ""'\n\n\n";

				auto kind = AsString(clang_getCursorKindSpelling(clang_getCursorKind(c)));

				auto& parsers = parser->_parsers;
				auto it = parsers.find(kind);
				if (it != parsers.end())
				{
					it->second(fileDescriptor, c, parent);
				}

				return CXChildVisit_Recurse;
			},
			&clientData);

		clang_disposeTranslationUnit(unit);
		clang_disposeIndex(index);

		return fileDescriptor;
	}

	Parser::ParserClientData::ParserClientData(Parser* parser, FileDescriptor& fileDescriptor)
		: parser(parser), fileDescriptor(fileDescriptor)
	{
	}

	void Parser::Emplace(const std::string& kind, void (Parser::* parser)(FileDescriptor& fileDescriptor, CXCursor cursor, CXCursor parent))
	{
		using std::placeholders::_1;
		using std::placeholders::_2;
		using std::placeholders::_3;
		_parsers.emplace(kind, std::bind(parser, this, _1, _2, _3));
	}

	void Parser::NamespaceParser(FileDescriptor& fileDescriptor, CXCursor cursor, CXCursor parent)
	{
		auto ns = AsString(clang_getCursorSpelling(cursor));
		NamespaceDescriptor descriptor;
		descriptor.name = ns;
		fileDescriptor.namespaces.push_back(descriptor);
	}
}