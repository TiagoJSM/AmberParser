#pragma once

#include <vector>
#include <string>

#include "BaseDescriptor.hpp"
#include "TranslationUnitDescriptor.hpp"

namespace AP
{
	class MethodDescriptor : public BaseDescriptor
	{
	public:
		MethodDescriptor(const TranslationUnitDescriptor& translationUnit, BaseDescriptor* parent, const std::string& name, AccessSpecifier accessSpecifier, CXCursor cursor, bool isStatic);
		IRegistrationCommandWritter* GetRegistrationCommandWritter() override;

		const bool isStatic;
	private:
		ConstructorCommandWritter _ctorCommand;
	};
}