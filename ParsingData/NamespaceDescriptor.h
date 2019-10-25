#pragma once

#include <vector>

#include "ClassDescriptor.h"

namespace AP
{
	struct NamespaceDescriptor
	{
		std::vector<ClassDescriptor> classes;
	};
}