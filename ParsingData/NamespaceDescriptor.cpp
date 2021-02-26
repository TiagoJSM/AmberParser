#include "NamespaceDescriptor.hpp"

namespace AP 
{
	NamespaceDescriptor::NamespaceDescriptor(const TranslationUnitDescriptor& translationUnit, BaseDescriptor* parent, const std::string& name, AccessSpecifier accessSpecifier, CXCursor cursor)
		: BaseDescriptor(translationUnit, parent, name, accessSpecifier, cursor) {}
}