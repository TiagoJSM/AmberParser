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

            writter.IncrementIdentLevel();
            writter.NewLine();

            auto& children = _descriptor.GetChildren();
            for (auto idx = 0; idx < children.size(); idx++)
            {
                (*children[0]->GetRegistrationCommandWritter()) << writter;
                if (idx != (children.size() - 1))
                {
                    writter.NewLine();
                }
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

    AmberReflectionMacroCommandWritter::AmberReflectionMacroCommandWritter(const std::vector<IRegistrationCommandWritter*>& commandWritters)
        :_commandWritters(commandWritters)
    {}

    RegistrationWritter& AmberReflectionMacroCommandWritter::operator<<(RegistrationWritter& writter)
    {
        writter.Write("AMBER_REFLECT");
        writter.NewLine();
        writter.Write("{");
        writter.NewLine();
        writter.IncrementIdentLevel();

        auto identLevel = writter.GetIdentLevel();

        int idx = 0;
        for (auto commandWritter : _commandWritters)
        {
            *commandWritter << writter;
            writter.Write(";");
            if (idx != (_commandWritters.size() - 1))
            {
                writter.NewLine(2);
            }
            writter.SetIdentLevel(identLevel);
            idx++;
        }
        
        writter.NewLine();
        writter.DecrementIdentLevel();
        writter.Write("}");

        return writter;
    }
}