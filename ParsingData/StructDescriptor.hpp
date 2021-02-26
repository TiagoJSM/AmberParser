#pragma once

#include <vector>

#include "BaseDescriptor.hpp"
#include "FieldDescriptor.hpp"
#include "TranslationUnitDescriptor.hpp"

namespace AP
{
	class StructDescriptor : public BaseDescriptor
	{
	public:
		StructDescriptor(const TranslationUnitDescriptor& translationUnit, BaseDescriptor* parent, const std::string& name, AccessSpecifier accessSpecifier, CXCursor cursor);

		std::vector<FieldDescriptor*> fields;
	};
}