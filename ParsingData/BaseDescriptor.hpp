#pragma once

#include <clang-c/Index.h>

namespace AP
{
	class BaseDescriptor
	{
	public:
		BaseDescriptor(BaseDescriptor* parent);
		BaseDescriptor* getParent() const;
	private:
		BaseDescriptor* _parent;
	};
}