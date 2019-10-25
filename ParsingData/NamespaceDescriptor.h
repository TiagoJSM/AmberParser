#pragma once

#include <vector>

#include "ClassDescriptor.h"

namespace AP
{
	struct NamespaceDescriptor
	{
		std::string name;
		std::vector<ClassDescriptor> classes;
	};
}