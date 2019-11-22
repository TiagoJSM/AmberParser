#pragma once

#include <string>

#include "BaseDescriptor.hpp"

namespace AP
{
	class FieldDescriptor : public BaseDescriptor
	{
	public:
		FieldDescriptor(BaseDescriptor* parent);

		std::string attribute;
		std::string name;
	};
}