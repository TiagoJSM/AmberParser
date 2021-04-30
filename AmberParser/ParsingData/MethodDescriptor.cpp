#include "MethodDescriptor.hpp"

#include "../BuildGeneration/Attributes.hpp"

namespace AP
{
	MethodDescriptor::MethodDescriptor(const TranslationUnitDescriptor& translationUnit, BaseDescriptor* parent, const std::string& name, AccessSpecifier accessSpecifier, CXCursor cursor, bool isStatic)
		: BaseDescriptor(translationUnit, parent, name, accessSpecifier, cursor), isStatic(isStatic), _ctorCommand(*this){}

	IRegistrationCommandWritter* MethodDescriptor::GetRegistrationCommandWritter()
	{
		return accessSpecifier == AccessSpecifier::Public && attribute == Ctor ? &_ctorCommand : nullptr;
	}
}