#include "BaseDescriptor.hpp"

#include "TranslationUnitDescriptor.hpp"

namespace AP
{
	AccessSpecifier Convert(CX_CXXAccessSpecifier accessSpecifier)
	{
		switch (accessSpecifier)
		{
		case CX_CXXAccessSpecifier::CX_CXXPublic: return AccessSpecifier::Public;
		case CX_CXXAccessSpecifier::CX_CXXProtected: return AccessSpecifier::Protected;
		case CX_CXXAccessSpecifier::CX_CXXPrivate: return AccessSpecifier::Private;
		default: return AccessSpecifier::Invalid;
		}
	}

	bool operator==(const CXCursor& lhs, const CXCursor& rhs) {
		return
			lhs.xdata == rhs.xdata &&
			lhs.kind == rhs.kind &&
			lhs.data[0] == rhs.data[0] &&
			lhs.data[1] == rhs.data[1] &&
			lhs.data[2] == rhs.data[2];
	}

	BaseDescriptor::BaseDescriptor(const TranslationUnitDescriptor& translationUnit, BaseDescriptor* parent, const std::string& name, AccessSpecifier accessSpecifier, CXCursor cursor)
		: _translationUnit(translationUnit), _parent(parent), name(name), accessSpecifier(accessSpecifier), _cursor(cursor)
	{
		if (parent != nullptr)
		{
			parent->_children.push_back(this);
		}
	}

	BaseDescriptor* BaseDescriptor::GetParent() const
	{
		return _parent;
	}
	const CXCursor& BaseDescriptor::GetCursor() const
	{
		return _cursor;
	}
	bool BaseDescriptor::IsSameCursor(const CXCursor& cursor) const {
		return _cursor == cursor;
	}
	const std::vector<BaseDescriptor*>& BaseDescriptor::GetChildren() const {
		return _children;
	}
	std::string BaseDescriptor::GetFullName() const 
	{
		if (_parent)
		{
			return _parent->GetFullName() + "::" + name;
		}
		return name;
	}
	bool BaseDescriptor::HasAttribute(const std::string& attributeName) const
	{
		return 
			std::find_if(
				std::begin(attributes), 
				std::end(attributes), 
				[attributeName](const AttributeData& attribute) {return attribute.attributeName == attributeName; }) != std::end(attributes);
	}

	bool BaseDescriptor::operator==(const BaseDescriptor& other) const {
		return GetCursor() == other.GetCursor();
	}
}