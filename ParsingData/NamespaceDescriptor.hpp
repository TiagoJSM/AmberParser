#pragma once

#include <vector>
#include <string>

#include "BaseDescriptor.hpp"
//#include "ClassDescriptor.hpp"

namespace AP
{
	class NamespaceDescriptor : public BaseDescriptor
	{
	public:
		NamespaceDescriptor(BaseDescriptor* parent);

		std::string name;
		//std::vector<ClassDescriptor> classes;
	};
}