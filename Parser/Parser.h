#pragma once

#include "../ParsingData/FileDescriptor.h"

namespace AP
{
	class Parser 
	{
	public:
		static FileDescriptor Parse(std::string filePath);
	};
}