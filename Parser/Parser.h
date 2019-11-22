#pragma once

#include <map>
#include <functional>

#include <clang-c/Index.h>

#include "../ParsingData/FileDescriptor.hpp"

typedef std::function<void(AP::FileDescriptor& fileDescriptor, CXCursor cursor, CXCursor parent)> CursorParser;

namespace AP
{
	class Parser 
	{
	public:
		Parser();

		FileDescriptor Parse(std::string filePath);

	private:
		struct ParserClientData
		{
		public:
			Parser* parser;
			FileDescriptor& fileDescriptor;

			ParserClientData(Parser* parser, FileDescriptor& fileDescriptor);
		};

		std::map<std::string, CursorParser> _parsers;

		void Emplace(const std::string& kind, void (Parser::* parser)(FileDescriptor& fileDescriptor, CXCursor cursor, CXCursor parent));
		void NamespaceParser(FileDescriptor& fileDescriptor, CXCursor cursor, CXCursor parent);
		void ClassParser(FileDescriptor& fileDescriptor, CXCursor cursor, CXCursor parent);
		void FieldParser(FileDescriptor& fileDescriptor, CXCursor cursor, CXCursor parent);
	};
}