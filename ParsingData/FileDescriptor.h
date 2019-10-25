#pragma once

#include <vector>

#include "NamespaceDescriptor.h"

namespace AP 
{
	struct FileDescriptor
	{
	public:
		std::vector<NamespaceDescriptor> namespaces;
	};
}