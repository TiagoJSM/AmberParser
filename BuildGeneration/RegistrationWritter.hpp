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
    private:
        std::vector<std::string>& _output;
    };
}