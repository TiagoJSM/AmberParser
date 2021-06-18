#pragma once

#include <map>
#include <functional>

#include <clang-c/Index.h>

#include "../ParsingData/TranslationUnitDescriptor.hpp"
#include "../ParsingData/AttributeData.hpp"

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

		struct ParsedAttributeData
		{
			AttributeData attributeData;
			unsigned int line;

			ParsedAttributeData(const AttributeData& attributeData, unsigned int line)
				:attributeData(attributeData), line(line)
			{
			}

			ParsedAttributeData(const ParsedAttributeData& a) = default;
		};

		std::map<std::string, CursorParser> _parsers;
		std::vector<ParsedAttributeData> _attributesParsed;

		void Emplace(const std::string& kind, void (Parser::* parser)(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent));
		void NamespaceParser(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent);
		void ClassParser(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent);
		void StructParser(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent);
		void FieldParser(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent);
		void AttributeParser(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent);
		void BaseClassParser(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent);
		void MethodParser(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent);
		void MacroParser(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent);

		std::vector<AttributeData> RetrieveAttributesForLine(unsigned int line);

		template<typename TDescriptor, class... AdditionalArgs, typename = std::enable_if_t<std::is_base_of_v<BaseDescriptor, TDescriptor>>>
		TDescriptor* BuildDescriptor(TranslationUnitDescriptor& translationUnitDescriptor, CXCursor cursor, CXCursor parent, AdditionalArgs&&... args) {
			auto name = AsString(clang_getCursorSpelling(cursor));
			auto accessSpecifier = Convert(clang_getCXXAccessSpecifier(cursor));
			auto parentDesc = translationUnitDescriptor.Find(parent);
			auto descriptor = new TDescriptor(translationUnitDescriptor, parentDesc, name, accessSpecifier, cursor, std::forward<AdditionalArgs>(args)...);
			if (!parentDesc)
			{
				translationUnitDescriptor.rootDescriptors.push_back(descriptor);
			}
			translationUnitDescriptor.allDescriptors.push_back(descriptor);

			auto cursorLocation = clang_getCursorLocation(cursor);
			CXFile file;
			unsigned int line;
			unsigned int column;
			unsigned int offset;
			clang_getFileLocation(cursorLocation, &file, &line, &column, &offset);
			auto attributes = RetrieveAttributesForLine(line);

			descriptor->attributes.insert(std::end(descriptor->attributes), std::begin(attributes), std::end(attributes));

			return descriptor;
		}
	};
}