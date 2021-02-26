#include "TypeRegistration.hpp"
#include "../ParsingData/FieldDescriptor.hpp"
#include "../ParsingData/CompoundDescriptor.hpp"
#include "Attributes.hpp"

namespace AP
{
    RegisterCompoundCommand::RegisterCompoundCommand(const CompoundDescriptor& descriptor)
        : _descriptor(descriptor)
    {
    }

    RegistrationWritter& RegisterCompoundCommand::operator<<(RegistrationWritter& writter)
    {
        if (_descriptor.attribute == Reflect || _descriptor.attribute == Component)
        {
            writter.Write("ARefl::RegisterCompound<" + _descriptor.GetFullName() + ">()");
            for (auto baseDescriptor : _descriptor.baseDescriptors)
            {
                writter.Write(".Base(" + baseDescriptor->GetFullName() + ")");
            }
        }
        return writter;
    }

    ConstructorCommand::ConstructorCommand(const std::string& ctorFunc)
        : _ctorFunc(ctorFunc)
    {
    }

    MemberFieldCommand::MemberFieldCommand(const FieldDescriptor& fieldDescriptor)
        : _fieldDescriptor(fieldDescriptor)
    {
    }

    RegistrationWritter& MemberFieldCommand::operator<<(RegistrationWritter& writter)
    {
        if (_fieldDescriptor.accessSpecifier == AccessSpecifier::Public)
        {
            writter.Write(".MemberField(" + _fieldDescriptor.GetFullName() + ", " + _fieldDescriptor.name + ")");
        }
        return writter;
    }

    BaseCommand::BaseCommand(const std::string& type)
        : _type(type)
    {
    }

    TemplateBaseCommand::TemplateBaseCommand(const std::string& templateType, const std::string& templateParameter)
        : _templateType(templateType), _templateParameter(templateParameter)
    {
    }
}