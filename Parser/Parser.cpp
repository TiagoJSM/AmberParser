#include "Parser.h"

#include <iostream>
#include <fstream> 

#include "../Helpers/CursorHelpers.hpp"
#include "../Helpers/FileHelper.hpp"
#include "../ParsingData/BaseDescriptor.hpp"
#include "../ParsingData/NamespaceDescriptor.hpp"
#include "../ParsingData/ClassDescriptor.hpp"
#include "../ParsingData/StructDescriptor.hpp"
#include "../ParsingData/FieldDescriptor.hpp"

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

	template<typename TDescriptor, typename = std::enable_if_t<std::is_base_of_v<BaseDescriptor, TDescriptor>>>
	TDescriptor* BuildDescriptor(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent) {
		auto name = AsString(clang_getCursorSpelling(cursor));
		auto accessSpecifier = Convert(clang_getCXXAccessSpecifier(cursor));
		auto parentDesc = translationUnitDescriptor.Find(parent);
		auto descriptor = new TDescriptor(translationUnitDescriptor, parentDesc, name, accessSpecifier, cursor);
		if (!parentDesc) 
		{
			translationUnitDescriptor.rootDescriptors.push_back(descriptor);
		}
		translationUnitDescriptor.allDescriptors.push_back(descriptor);
		return descriptor;
	}

	Parser::Parser()
	{
		Emplace("Namespace", &Parser::NamespaceParser);
		Emplace("ClassDecl", &Parser::ClassParser);
		Emplace("StructDecl", &Parser::StructParser);
		Emplace("FieldDecl", &Parser::FieldParser);
		Emplace("FieldDecl", &Parser::FieldParser);
		Emplace("attribute(annotate)", &Parser::AttributeParser);
	}

	TranslationUnitDescriptor Parser::Parse(std::string filePath)
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

		TranslationUnitDescriptor translationUnitDescriptor;
		ParserClientData clientData(this, translationUnitDescriptor);

		CXCursor cursor = clang_getTranslationUnitCursor(unit);
		clang_visitChildren(
			cursor,
			[](CXCursor c, CXCursor parent, CXClientData client_data)
			{
				auto clientData = static_cast<ParserClientData*>(client_data);
				auto parser = clientData->parser;
				auto& translationUnitDescriptor = clientData->translationUnitDescriptor;

				std::cout << "parent '" << clang_getCursorSpelling(parent) << "' of kind '"
					<< clang_getCursorKindSpelling(clang_getCursorKind(parent)) << " "
					<< clang_getTypeSpelling(clang_getCursorType(parent)) << " "
					<< clang_getCXXAccessSpecifier(parent) << " ""'\n";

				//clang_getCursorSemanticParent

				std::cout << "Cursor '" << clang_getCursorSpelling(c) << "' of kind '"
					<< clang_getCursorKindSpelling(clang_getCursorKind(c)) << " "
					<< clang_getTypeSpelling(clang_getCursorType(c)) << " "
					<< clang_getCXXAccessSpecifier(c) << " ""'\n\n\n";

				auto kind = AsString(clang_getCursorKindSpelling(clang_getCursorKind(c)));

				auto& parsers = parser->_parsers;
				auto it = parsers.find(kind);
				if (it != parsers.end())
				{
					it->second(translationUnitDescriptor, c, parent);
				}

				return CXChildVisit_Recurse;
			},
			&clientData);

		clang_disposeTranslationUnit(unit);
		clang_disposeIndex(index);

		return translationUnitDescriptor;
	}

	Parser::ParserClientData::ParserClientData(Parser* parser, TranslationUnitDescriptor& translationUnitDescriptor)
		: parser(parser), translationUnitDescriptor(translationUnitDescriptor)
	{
	}

	void Parser::Emplace(const std::string& kind, void (Parser::* parser)(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent))
	{
		using std::placeholders::_1;
		using std::placeholders::_2;
		using std::placeholders::_3;
		_parsers.emplace(kind, std::bind(parser, this, _1, _2, _3));
	}

	void Parser::NamespaceParser(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent)
	{
		auto descriptor = BuildDescriptor<NamespaceDescriptor>(translationUnitDescriptor, cursor, parent);
	}

	void Parser::ClassParser(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent)
	{
		auto descriptor = BuildDescriptor<ClassDescriptor>(translationUnitDescriptor, cursor, parent);
	}

	void Parser::StructParser(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent)
	{
		auto descriptor = BuildDescriptor<StructDescriptor>(translationUnitDescriptor, cursor, parent);
	}

	void Parser::FieldParser(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent)
	{
		auto descriptor = BuildDescriptor<FieldDescriptor>(translationUnitDescriptor, cursor, parent);
		auto parentDesc = translationUnitDescriptor.Find(parent);
		if (auto parentClass = dynamic_cast<ClassDescriptor*>(parentDesc))
		{
			parentClass->fields.push_back(descriptor);
		}
		else if(auto parentStruct = dynamic_cast<StructDescriptor*>(parentDesc))
		{
			parentStruct->fields.push_back(descriptor);
		}
	}

	void Parser::AttributeParser(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent)
	{
		auto field = translationUnitDescriptor.Find<FieldDescriptor>(parent);
		if (field) 
		{
			auto annotation = AsString(clang_getCursorSpelling(cursor));
			field->attribute = annotation;
			field->type = AsString(clang_getTypeSpelling(clang_getCursorType(cursor)));
		}
	}
}