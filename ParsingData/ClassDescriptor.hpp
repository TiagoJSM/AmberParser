#pragma once

#include <vector>

#include "BaseDescriptor.hpp"
#include "FieldDescriptor.hpp"

namespace AP
{
	class ClassDescriptor : public BaseDescriptor
	{
	public:
		ClassDescriptor(BaseDescriptor* parent);

		std::vector<FieldDescriptor> fields;
		std::vector<FieldDescriptor> methods;
	};
}