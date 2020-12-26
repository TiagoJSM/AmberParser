#include "ClassDescriptor.hpp"

#include "TranslationUnitDescriptor.hpp"

namespace AP
{
	ClassDescriptor::ClassDescriptor(const TranslationUnitDescriptor& translationUnit, BaseDescriptor* parent, const std::string& name, AccessSpecifier accessSpecifier, CXCursor cursor)
		: BaseDescriptor(translationUnit, parent, name, accessSpecifier, cursor) {}
}