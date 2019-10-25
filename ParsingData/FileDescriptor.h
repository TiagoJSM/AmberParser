#pragma once

#include <vector>

#include "NamespaceDescriptor.h"

namespace AP 
{
	struct FileDescriptor
	{
		std::vector<NamespaceDescriptor> namespaces;
	};
}