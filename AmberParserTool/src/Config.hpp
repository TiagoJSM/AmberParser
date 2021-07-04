#pragma once

#include <filesystem>
#include <string>
#include "cxxopts/include/cxxopts.hpp"

namespace APT
{
    cxxopts::ParseResult Init(int argc, char* argv[], cxxopts::Options& options);
    const std::filesystem::path& GetAbsoluteRootPath();
}