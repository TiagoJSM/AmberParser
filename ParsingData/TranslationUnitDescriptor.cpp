#include "TranslationUnitDescriptor.hpp"

namespace AP {
    BaseDescriptor* TranslationUnitDescriptor::Find(const CXCursor& cursor) const {
        return Find<BaseDescriptor>(cursor);
    }
}