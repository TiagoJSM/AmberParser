#pragma once

#include <vector>
#include <string>

#include "BaseDescriptor.hpp"
#include "TranslationUnitDescriptor.hpp"

namespace AP
{
	class NamespaceDescriptor : public BaseDescriptor
	{
	public:
		NamespaceDescriptor(const TranslationUnitDescriptor& translationUnit, BaseDescriptor* parent, const std::string& name, AccessSpecifier accessSpecifier, CXCursor cursor);
		IRegistrationCommandWritter* GetRegistrationCommandWritter() override;
	};
}