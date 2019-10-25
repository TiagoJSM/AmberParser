#pragma once

#include <vector>

#include "FieldDescriptor.h"

namespace AP
{
	struct ClassDescriptor
	{
		std::vector<FieldDescriptor> fields;
		std::vector<FieldDescriptor> methods;
	};
}