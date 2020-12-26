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
		if (auto child = _translationUnit.Find(parent->GetCursor())) 
		{
			_children.push_back(child);
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

	bool BaseDescriptor::operator==(const BaseDescriptor& other) const {
		return GetCursor() == other.GetCursor();
	}
}