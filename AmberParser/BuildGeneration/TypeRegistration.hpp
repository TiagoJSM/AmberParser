#pragma once

#include <string>
#include <vector>
#include <ostream>
#include <iostream>
#include "RegistrationWrittable.hpp"

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
        virtual RegistrationWrittable& operator<<(RegistrationWrittable& writter) = 0;
    };

    class RegisterCompoundCommandWritter : public IRegistrationCommandWritter
    {
    public:
        RegisterCompoundCommandWritter(const CompoundDescriptor& type);
        RegistrationWrittable& operator<<(RegistrationWrittable& writter) override;
    private:
        std::string _type;
        const CompoundDescriptor& _descriptor;
    };

    class ConstructorCommandWritter : public IRegistrationCommandWritter
    {
    public:
        ConstructorCommandWritter(const std::string& ctorFunc);
        RegistrationWrittable& operator<<(RegistrationWrittable& writter) override
        {
            writter.Write(".Ctor(" + _ctorFunc + ")");
            return writter;
        }
    private:
        std::string _ctorFunc;
    };

    class MemberFieldCommandWritter : public IRegistrationCommandWritter
    {
    public:
        MemberFieldCommandWritter(const FieldDescriptor& fieldDescriptor);
        RegistrationWrittable& operator<<(RegistrationWrittable& writter) override;
    private:
        const FieldDescriptor& _fieldDescriptor;
    };

    class BaseCommandWritter : public IRegistrationCommandWritter
    {
    public:
        BaseCommandWritter(const std::string& type);
        RegistrationWrittable& operator<<(RegistrationWrittable& writter) override
        {
            writter.Write(".Base<" + _type + ", " + _type + ">()");
            return writter;
        }
    private:
        std::string _type;
    };

    class TemplateBaseCommandWritter : public IRegistrationCommandWritter
    {
    public:
        TemplateBaseCommandWritter(const std::string& templateType, const std::string& templateParameter);
        RegistrationWrittable& operator<<(RegistrationWrittable& writter) override
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
        RegistrationWrittable& operator<<(RegistrationWrittable& writter) override;
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