#include "CursorHelpers.hpp"

namespace AP 
{
	inline bool operator==(const CXCursor& lhs, const CXCursor& rhs)
	{
		return std::memcmp(&lhs, &rhs, sizeof(CXCursor)) == 0;
	}
}