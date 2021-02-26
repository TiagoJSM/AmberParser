#pragma once

#include <string>
#include <vector>

#include <clang-c/Index.h>

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

	class TranslationUnitDescriptor;
	
	class BaseDescriptor
	{
	public:
		const std::string name;
		const AccessSpecifier accessSpecifier;

		BaseDescriptor(const TranslationUnitDescriptor& translationUnit, BaseDescriptor* parent, const std::string& name, AccessSpecifier accessSpecifier, CXCursor cursor);
		BaseDescriptor* GetParent() const;
		const CXCursor& GetCursor() const;
		bool IsSameCursor(const CXCursor& cursor) const;
		const std::vector<BaseDescriptor*>& GetChildren() const;

		bool operator==(const BaseDescriptor& other) const;

		virtual ~BaseDescriptor() = default;
	private:
		const TranslationUnitDescriptor& _translationUnit;
		BaseDescriptor* _parent;
		CXCursor _cursor;
		std::vector<BaseDescriptor*> _children;
	};
}