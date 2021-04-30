#pragma once

#include <filesystem>
#include <string>

namespace APT
{
    void Init(int argc, char* argv[]);
    const std::filesystem::path& GetAbsoluteRootPath();
}