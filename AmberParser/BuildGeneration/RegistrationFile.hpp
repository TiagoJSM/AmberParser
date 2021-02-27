#pragma once

#include <iostream>
#include <fstream>
#include <cstdint>
#include <filesystem>
#include <sstream>

#include "TypeRegistration.hpp"
#include "../ParsingData/TranslationUnitDescriptor.hpp"

namespace AP
{
    class RegistrationFile
    {
    public:
        void Write(std::stringstream& output, AP::TranslationUnitDescriptor descriptor);
    private:
        void Write(RegistrationWrittable& rw, std::vector<BaseDescriptor*>& descriptors);
        void WriteToOutput(std::stringstream& output, const std::vector<std::string>& registrations);
    };
}