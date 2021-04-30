#include "Parser.h"

#include <iostream>
#include <fstream> 

#include "../Helpers/CursorHelpers.hpp"
#include "../Helpers/FileHelper.hpp"
#include "../ParsingData/BaseDescriptor.hpp"
#include "../ParsingData/NamespaceDescriptor.hpp"
#include "../ParsingData/FieldDescriptor.hpp"
#include "../ParsingData/CompoundDescriptor.hpp"
#include "../ParsingData/MethodDescriptor.hpp"

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

	template<typename TDescriptor, class... AdditionalArgs, typename = std::enable_if_t<std::is_base_of_v<BaseDescriptor, TDescriptor>>>
	TDescriptor* BuildDescriptor(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent, AdditionalArgs&&... Args) {
		auto name = AsString(clang_getCursorSpelling(cursor));
		auto accessSpecifier = Convert(clang_getCXXAccessSpecifier(cursor));
		auto parentDesc = translationUnitDescriptor.Find(parent);
		auto descriptor = new TDescriptor(translationUnitDescriptor, parentDesc, name, accessSpecifier, cursor, std::forward<AdditionalArgs>(Args)...);
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
		Emplace("ClassTemplate", &Parser::ClassParser);
		Emplace("StructDecl", &Parser::StructParser);
		Emplace("FieldDecl", &Parser::FieldParser);
		Emplace("attribute(annotate)", &Parser::AttributeParser);
		Emplace("C++ base class specifier", &Parser::BaseClassParser);
		Emplace("CXXMethod", &Parser::MethodParser);
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

		//std::ofstream outfile(GenerateMetaPath(filePath));

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
		auto descriptor = BuildDescriptor<CompoundDescriptor>(translationUnitDescriptor, cursor, parent);
		translationUnitDescriptor.compoundDescriptors.push_back(descriptor);
	}
	
	void Parser::StructParser(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent)
	{
		auto descriptor = BuildDescriptor<CompoundDescriptor>(translationUnitDescriptor, cursor, parent);
		translationUnitDescriptor.compoundDescriptors.push_back(descriptor);
	}

	void Parser::FieldParser(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent)
	{
		auto descriptor = BuildDescriptor<FieldDescriptor>(translationUnitDescriptor, cursor, parent);
		descriptor->type = AsString(clang_getTypeSpelling(clang_getCursorType(cursor)));
	}

	void Parser::AttributeParser(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent)
	{
		auto desc = translationUnitDescriptor.Find(parent);
		if (desc)
		{
			auto annotation = AsString(clang_getCursorSpelling(cursor));
			desc->attribute = annotation;
		}
	}

	void Parser::BaseClassParser(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent)
	{
		auto classDesc = translationUnitDescriptor.Find<CompoundDescriptor>(parent);
		if (classDesc)
		{
			auto descriptor = BuildDescriptor<CompoundDescriptor>(translationUnitDescriptor, cursor, /*parent*/clang_getNullCursor());
			//translationUnitDescriptor.compoundDescriptors.push_back(descriptor);
			classDesc->baseDescriptors.push_back(descriptor);
		}

		/*auto a = clang_getCursorDefinition(cursor);
		auto fullName1 = AsString(clang_getTypeSpelling(clang_getCursorType(a)));
		auto baseDesc1 = translationUnitDescriptor.FindByFullName(fullName1);
		auto fullName = AsString(clang_getTypeSpelling(clang_getCursorType(cursor)));
		auto baseDesc = translationUnitDescriptor.FindByFullName(fullName);
		auto desc = translationUnitDescriptor.Find(parent);
		auto semantic = clang_getCursorSemanticParent(cursor);
		auto semantic1 = clang_getCursorLexicalParent(cursor);

		if (auto compoundDesc = dynamic_cast<CompoundDescriptor*>(desc))
		{
			compoundDesc->baseDescriptors.push_back(baseDesc);

			auto templateArgumentsCount = clang_Type_getNumTemplateArguments(clang_getCursorType(cursor));
			for (auto idx = 0; idx < templateArgumentsCount; idx++)
			{
				auto templateType = clang_Type_getTemplateArgumentAsType(clang_getCursorType(cursor), 0);
				auto templateTypeName = AsString(clang_getTypeSpelling(templateType));
				auto t = templateTypeName;
			}
		}*/
	}

	void Parser::MethodParser(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent)
	{
		auto isStatic = clang_CXXMethod_isStatic(cursor);
		auto descriptor = BuildDescriptor<MethodDescriptor>(translationUnitDescriptor, cursor, parent, isStatic != 0);
	}
}