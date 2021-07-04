#pragma once

#include <iostream>
#include <cstdlib>
#include <filesystem>
#include "cxxopts/include/cxxopts.hpp"

namespace APT
{
    static std::filesystem::path _rootPath;

    cxxopts::ParseResult Init(int argc, char* argv[], cxxopts::Options& options)
    {
        auto result = options.parse(argc, argv);

        if (!result.count("src"))
        {
            std::cout << "Missing parameter 'src'" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        std::filesystem::path path(result["src"].as<std::string>());
        if (!path.is_absolute())
        {
            std::cout << "Path provided needs to be absolute" << '\n';
            std::exit(EXIT_FAILURE);
        }
        _rootPath = path;

        return result;
    }

    const std::filesystem::path& GetAbsoluteRootPath()
    {
        return _rootPath;
    }
}