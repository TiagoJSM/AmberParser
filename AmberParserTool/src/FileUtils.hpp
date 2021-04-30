#pragma once

#include <string>
#include <filesystem>

namespace APT
{
    const std::string GeneratedOutputFolder = "auto-generated";

    std::filesystem::path GetPathOfGeneratedFile(const std::string& absolutePath);
}