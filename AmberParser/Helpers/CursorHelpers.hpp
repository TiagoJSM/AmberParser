#pragma once

#include <string>

#include <clang-c/Index.h>

namespace AP
{
	inline bool operator==(const CXCursor& lhs, const CXCursor& rhs);
}