#include "FieldDescriptor.hpp"

#include "TranslationUnitDescriptor.hpp"

namespace AP
{
	FieldDescriptor::FieldDescriptor(const TranslationUnitDescriptor& translationUnit, BaseDescriptor* parent, const std::string& name, AccessSpecifier accessSpecifier, CXCursor cursor)
		: BaseDescriptor(translationUnit, parent, name, accessSpecifier, cursor), _command(*this)
	{}

	IRegistrationCommandWritter* FieldDescriptor::GetRegistrationCommandWritter()
	{
		return &_command;
	}
}