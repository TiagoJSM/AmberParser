#pragma once

#include <string>
#include <vector>

#include <clang-c/Index.h>

#include "AttributeData.hpp"
#include "../BuildGeneration/TypeRegistration.hpp"


namespace AP
{
	bool operator==(const CXCursor& lhs, const CXCursor& rhs);

	enum class AccessSpecifier 
	{
		Invalid,
		Public,
		Private,
		Protected
	};

	AccessSpecifier Convert(CX_CXXAccessSpecifier accessSpecifier);

	struct TranslationUnitDescriptor;
	
	class BaseDescriptor
	{
	public:
		const std::string name;
		const AccessSpecifier accessSpecifier;
		//std::string attribute;
		std::vector<AttributeData> attributes;

		BaseDescriptor(const TranslationUnitDescriptor& translationUnit, BaseDescriptor* parent, const std::string& name, AccessSpecifier accessSpecifier, CXCursor cursor);
		BaseDescriptor* GetParent() const;
		const CXCursor& GetCursor() const;
		bool IsSameCursor(const CXCursor& cursor) const;
		const std::vector<BaseDescriptor*>& GetChildren() const;
		std::string GetFullName() const;
		bool HasAttribute(const std::string& attributeName) const;

		bool operator==(const BaseDescriptor& other) const;

		virtual IRegistrationCommandWritter* GetRegistrationCommandWritter() = 0;
		//virtual ~BaseDescriptor() = default;
	private:
		const TranslationUnitDescriptor& _translationUnit;
		BaseDescriptor* _parent;
		CXCursor _cursor;
		std::vector<BaseDescriptor*> _children;
	};
}