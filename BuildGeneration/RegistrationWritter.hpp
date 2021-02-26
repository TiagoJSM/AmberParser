#pragma once

#include <iostream>
#include <fstream>
#include <cstdint>
#include <filesystem>
#include <sstream>

namespace AP
{
    class RegistrationWritter
    {
    public:
        RegistrationWritter(std::vector<std::string>& output);
        void Write(const std::string& data);
        void NewLine(int count = 1);
        void SetIdentLevel(int identLevel);
        void IncrementIdentLevel();
        void DecrementIdentLevel();
        int GetIdentLevel() const;
    private:
        std::vector<std::string>& _output;
        bool _requiresIdent = true;
        int _identLevel = 0;

        void Ident();
    };
}