#include "StructDescriptor.hpp"

#include "TranslationUnitDescriptor.hpp"

namespace AP
{
	StructDescriptor::StructDescriptor(const TranslationUnitDescriptor& translationUnit, BaseDescriptor* parent, const std::string& name, AccessSpecifier accessSpecifier, CXCursor cursor)
		: BaseDescriptor(translationUnit, parent, name, accessSpecifier, cursor) {}
}