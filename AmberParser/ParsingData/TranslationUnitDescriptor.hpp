#pragma once

#include <vector>

#include "BaseDescriptor.hpp"

namespace AP 
{
	struct TranslationUnitDescriptor
	{
	public:
		std::vector<BaseDescriptor*> allDescriptors;
		std::vector<BaseDescriptor*> rootDescriptors;
		std::vector<BaseDescriptor*> compoundDescriptors;

		TranslationUnitDescriptor() = default;
		TranslationUnitDescriptor(const TranslationUnitDescriptor&) = default;
		TranslationUnitDescriptor(TranslationUnitDescriptor&&) = default;
		~TranslationUnitDescriptor();

		template<typename TDescriptor, typename = std::enable_if_t<std::is_base_of_v<BaseDescriptor, TDescriptor>>>
		TDescriptor* Find(const CXCursor& cursor) const {
			auto iter = std::find_if(allDescriptors.begin(), allDescriptors.end(), [cursor](const BaseDescriptor* desc) {return desc->IsSameCursor(cursor); });
			return iter == allDescriptors.end() ? nullptr : dynamic_cast<TDescriptor*>(*iter);
		}
		BaseDescriptor* Find(const CXCursor& cursor) const;
		BaseDescriptor* FindByFullName(const std::string& fullName) const;
	};
}