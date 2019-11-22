#include "BaseDescriptor.hpp"

namespace AP
{
	BaseDescriptor::BaseDescriptor(BaseDescriptor* parent) : _parent(parent) {}
	BaseDescriptor* BaseDescriptor::getParent() const
	{
		return _parent;
	}
}