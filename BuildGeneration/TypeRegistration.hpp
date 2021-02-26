#pragma once

#include <string>
#include <vector>
#include <ostream>
#include <iostream>
#include "RegistrationWritter.hpp"

namespace AP
{
    class TypeRegistration;
    class StructDescriptor;
    class ClassDescriptor;
    class BaseDescriptor;
    class FieldDescriptor;
    class CompoundDescriptor;

    class IRegistrationCommandWritter
    {
    public:
        virtual RegistrationWritter& operator<<(RegistrationWritter& writter) = 0;
    };

    class RegisterCompoundCommand : public IRegistrationCommandWritter
    {
    public:
        RegisterCompoundCommand(const CompoundDescriptor& type);
        RegistrationWritter& operator<<(RegistrationWritter& writter) override;
    private:
        std::string _type;
        const CompoundDescriptor& _descriptor;
    };

    class ConstructorCommand : public IRegistrationCommandWritter
    {
    public:
        ConstructorCommand(const std::string& ctorFunc);
        RegistrationWritter& operator<<(RegistrationWritter& writter) override
        {
            writter.Write(".Ctor(" + _ctorFunc + ")");
            return writter;
        }
    private:
        std::string _ctorFunc;
    };

    class MemberFieldCommand : public IRegistrationCommandWritter
    {
    public:
        MemberFieldCommand(const FieldDescriptor& fieldDescriptor);
        RegistrationWritter& operator<<(RegistrationWritter& writter) override;
    private:
        const FieldDescriptor& _fieldDescriptor;
    };

    class BaseCommand : public IRegistrationCommandWritter
    {
    public:
        BaseCommand(const std::string& type);
        RegistrationWritter& operator<<(RegistrationWritter& writter) override
        {
            writter.Write(".Base<" + _type + ", " + _type + ">()");
            return writter;
        }
    private:
        std::string _type;
    };

    class TemplateBaseCommand : public IRegistrationCommandWritter
    {
    public:
        TemplateBaseCommand(const std::string& templateType, const std::string& templateParameter);
        RegistrationWritter& operator<<(RegistrationWritter& writter) override
        {
            writter.Write(".TemplateBase<" + _templateType + ", " + _templateParameter + ">()");
            return writter;
        }
    private:
        std::string _templateType;
        std::string _templateParameter;
    };

    class TypeRegistration
    {
    private:
        TypeRegistration() = default;

        std::vector<IRegistrationCommandWritter*> _commands;
    };

    class AmberReflectionMacroCommandWritter : public IRegistrationCommandWritter
    {
    public:
        AmberReflectionMacroCommandWritter(const std::vector<IRegistrationCommandWritter*>& commandWritters);
        RegistrationWritter& operator<<(RegistrationWritter& writter) override;
    private:
        const std::vector<IRegistrationCommandWritter*> _commandWritters;
    };

	/*
	ARefl::RegisterCompound<Amber::Vec3f>()
        .MemberField(Amber::Vec3f, x)
        .MemberField(Amber::Vec3f, y)
        .MemberField(Amber::Vec3f, z);

    ARefl::RegisterCompound<Amber::ResourceAssetObject>().Base<Amber::AssetObject>();
    ARefl::RegisterCompound<Amber::Mesh>().TemplateBase<Amber::ResourceAssetObject, Amber::MeshInterfacePtr>().Ctor(Amber::Mesh::New);
	*/
}