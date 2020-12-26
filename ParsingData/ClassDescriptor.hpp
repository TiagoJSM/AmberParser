#pragma once

#include <vector>

#include "BaseDescriptor.hpp"
#include "FieldDescriptor.hpp"
#include "TranslationUnitDescriptor.hpp"

namespace AP
{
	class ClassDescriptor : public BaseDescriptor
	{
	public:
		ClassDescriptor(const TranslationUnitDescriptor& translationUnit, BaseDescriptor* parent, const std::string& name, AccessSpecifier accessSpecifier, CXCursor cursor);

		std::vector<FieldDescriptor*> fields;
	};
}