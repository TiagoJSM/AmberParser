#include "CompoundDescriptor.hpp"

namespace AP
{
    CompoundDescriptor::CompoundDescriptor(const TranslationUnitDescriptor& translationUnit, BaseDescriptor* parent, const std::string& name, AccessSpecifier accessSpecifier, CXCursor cursor)
        : BaseDescriptor(translationUnit, parent, name, accessSpecifier, cursor), _command(*this)
    {
    }

    IRegistrationCommandWritter* CompoundDescriptor::GetRegistrationCommandWritter()
    {
        return &_command;
    }
}