#pragma once

#include "BaseDescriptor.hpp"
#include "TranslationUnitDescriptor.hpp"

namespace AP
{
    class CompoundDescriptor : public BaseDescriptor
    {
    public:
        CompoundDescriptor(const TranslationUnitDescriptor& translationUnit, BaseDescriptor* parent, const std::string& name, AccessSpecifier accessSpecifier, CXCursor cursor);
        std::vector<BaseDescriptor*> baseDescriptors;     

        IRegistrationCommandWritter* GetRegistrationCommandWritter() override;
    private:
        RegisterCompoundCommandWritter _command;
    };
}