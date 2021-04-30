#include "TranslationUnitDescriptor.hpp"

namespace AP {
    TranslationUnitDescriptor::~TranslationUnitDescriptor()
    {
        for (auto* descriptor : allDescriptors) 
        {
            delete descriptor;
        }
    }

    BaseDescriptor* TranslationUnitDescriptor::Find(const CXCursor& cursor) const {
        return Find<BaseDescriptor>(cursor);
    }

    BaseDescriptor* TranslationUnitDescriptor::FindByFullName(const std::string& fullName) const {
        auto iter = std::find_if(allDescriptors.begin(), allDescriptors.end(), [fullName](const BaseDescriptor* desc) {return desc->GetFullName() == fullName; });
        return iter == allDescriptors.end() ? nullptr : *iter;
    }
}