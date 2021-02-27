#pragma once

#include <string>

#include "BaseDescriptor.hpp"
#include "TranslationUnitDescriptor.hpp"

namespace AP
{
	class FieldDescriptor : public BaseDescriptor
	{
	public:
		FieldDescriptor(const TranslationUnitDescriptor& translationUnit, BaseDescriptor* parent, const std::string& name, AccessSpecifier accessSpecifier, CXCursor cursor);
		IRegistrationCommandWritter* GetRegistrationCommandWritter() override;

		std::string type;
	private:
		MemberFieldCommandWritter _command;
	};
}