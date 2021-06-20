#include "TypeRegistration.hpp"
#include "../ParsingData/FieldDescriptor.hpp"
#include "../ParsingData/CompoundDescriptor.hpp"
#include "../ParsingData/MethodDescriptor.hpp"
#include "Attributes.hpp"

namespace AP
{
    std::string GetCustomAttributesWrittable(const BaseDescriptor& descriptor)
    {
        std::string attributeWrittable = "{ ";
        auto idx = 0;
        for (auto& attribute : descriptor.attributes)
        {
            attributeWrittable += "new " + attribute.attributeName + "(" + attribute.attributeParametersText + ")";
            idx++;

            if (idx != descriptor.attributes.size())
            {
                attributeWrittable += ", ";
            }
        }

        attributeWrittable += " }";

        return attributeWrittable;
    }

    RegisterCompoundCommandWritter::RegisterCompoundCommandWritter(const CompoundDescriptor& descriptor)
        : _descriptor(descriptor)
    {
    }

    RegistrationWrittable& RegisterCompoundCommandWritter::operator<<(RegistrationWrittable& writter)
    {
        writter.Write("ARefl::RegisterCompound<" + _descriptor.GetFullName() + ">()");
        for (auto baseDescriptor : _descriptor.baseDescriptors)
        {
            writter.Write(".Base(" + baseDescriptor->GetFullName() + ")");
        }

        auto& children = _descriptor.GetChildren();
        std::vector<IRegistrationCommandWritter*> commandWritters;
        std::transform(children.begin(), children.end(), std::back_inserter(commandWritters),
            [](BaseDescriptor* desc) -> IRegistrationCommandWritter* { return desc->GetRegistrationCommandWritter(); });

        commandWritters.erase(std::remove_if(commandWritters.begin(),
            commandWritters.end(),
            [](IRegistrationCommandWritter* commandWritter) {
                return commandWritter == nullptr;
            }),
            commandWritters.end());

        if (commandWritters.size() > 0)
        {
            writter.IncrementIdentLevel();
            writter.NewLine();

            for (auto idx = 0; idx < commandWritters.size(); idx++)
            {
                auto commandWritter = commandWritters[idx];
                if (commandWritter != nullptr)
                {
                    (*commandWritter) << writter;
                }
                if (idx != (commandWritters.size() - 1))
                {
                    writter.NewLine();
                }
            }
        }
        return writter;
    }

    ConstructorCommandWritter::ConstructorCommandWritter(const MethodDescriptor& descriptor)
        : _descriptor(descriptor), _ctorFunc(descriptor.GetFullName())
    {
    }

    RegistrationWrittable& ConstructorCommandWritter::operator<<(RegistrationWrittable& writter)
    {
        writter.Write(".Ctor(" + _ctorFunc + ", " + GetCustomAttributesWrittable(_descriptor) + ")");
        return writter;
    }

    MemberFieldCommandWritter::MemberFieldCommandWritter(const FieldDescriptor& fieldDescriptor)
        : _fieldDescriptor(fieldDescriptor)
    {
    }

    RegistrationWrittable& MemberFieldCommandWritter::operator<<(RegistrationWrittable& writter)
    {
        writter.Write(".MemberField(" + _fieldDescriptor.GetParent()->GetFullName() + ", " + _fieldDescriptor.name + ", " + GetCustomAttributesWrittable(_fieldDescriptor) + ")");
        return writter;
    }

    BaseCommandWritter::BaseCommandWritter(const std::string& type)
        : _type(type)
    {
    }

    TemplateBaseCommandWritter::TemplateBaseCommandWritter(const std::string& templateType, const std::string& templateParameter)
        : _templateType(templateType), _templateParameter(templateParameter)
    {
    }

    AmberReflectionMacroCommandWritter::AmberReflectionMacroCommandWritter(const std::vector<IRegistrationCommandWritter*>& commandWritters)
        :_commandWritters(commandWritters)
    {}

    RegistrationWrittable& AmberReflectionMacroCommandWritter::operator<<(RegistrationWrittable& writter)
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