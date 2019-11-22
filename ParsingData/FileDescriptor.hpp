#pragma once

#include <vector>

#include "NamespaceDescriptor.hpp"

namespace AP 
{
	struct FileDescriptor
	{
	public:
		std::vector<BaseDescriptor*> descriptors;
	};
}