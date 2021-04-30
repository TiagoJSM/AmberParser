#pragma once

#include <map>
#include <functional>

#include <clang-c/Index.h>

#include "../ParsingData/TranslationUnitDescriptor.hpp"

typedef std::function<void(AP::TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent)> CursorParser;

namespace AP
{
	class Parser 
	{
	public:
		Parser();

		TranslationUnitDescriptor Parse(std::string filePath);

	private:
		struct ParserClientData
		{
		public:
			Parser* parser;
			TranslationUnitDescriptor& translationUnitDescriptor;

			ParserClientData(Parser* parser, TranslationUnitDescriptor& translationUnitDescriptor);
		};

		std::map<std::string, CursorParser> _parsers;

		void Emplace(const std::string& kind, void (Parser::* parser)(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent));
		void NamespaceParser(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent);
		void ClassParser(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent);
		void StructParser(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent);
		void FieldParser(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent);
		void AttributeParser(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent);
		void BaseClassParser(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent);
		void MethodParser(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent);
	};
}