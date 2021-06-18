#include "CompoundDescriptor.hpp"

#include "../BuildGeneration/Attributes.hpp"

namespace AP
{
    CompoundDescriptor::CompoundDescriptor(const TranslationUnitDescriptor& translationUnit, BaseDescriptor* parent, const std::string& name, AccessSpecifier accessSpecifier, CXCursor cursor)
        : BaseDescriptor(translationUnit, parent, name, accessSpecifier, cursor), _command(*this)
    {
    }

    IRegistrationCommandWritter* CompoundDescriptor::GetRegistrationCommandWritter()
    {
        return (HasAttribute(Reflect) || HasAttribute(Component)) ? &_command : nullptr;
    }
}