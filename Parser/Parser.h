#pragma once

#include <map>
#include <functional>

#include <clang-c/Index.h>

#include "../ParsingData/FileDescriptor.h"

//typedef std::function<void(CXCursor cursor, CXCursor parent)> CursorParser;

namespace AP
{
	class Parser 
	{
	public:
		Parser();

		FileDescriptor Parse(std::string filePath);

	private:
		std::map<std::string, std::function<void(CXCursor cursor, CXCursor parent)>> _parsers;

		void Emplace(const std::string& kind, void (Parser::* parser)(CXCursor cursor, CXCursor parent));
		void NamespaceParser(CXCursor cursor, CXCursor parent);

	};
}