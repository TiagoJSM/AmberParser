#pragma once

#include <iostream>
#include <cstdlib>
#include <filesystem>

namespace APT
{
    static std::filesystem::path _rootPath;

    void Init(int argc, char* argv[])
    {
        if (argc < 2) 
        {
            std::cout << "Provide root path as argument." << '\n';
            std::exit(EXIT_FAILURE);
        }
        std::filesystem::path path(argv[1]);
        if (!path.is_absolute())
        {
            std::cout << "Path provided needs to be absolute" << '\n';
            std::exit(EXIT_FAILURE);
        }
        _rootPath = argv[1];
    }

    const std::filesystem::path& GetAbsoluteRootPath()
    {
        return _rootPath;
    }
}