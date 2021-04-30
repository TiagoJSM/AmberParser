#include "FileUtils.hpp"

#include <algorithm>

#include "Config.hpp"

namespace APT
{
    static const std::string FolderReplacer = "___";

    void ReplaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace) {
        size_t pos = 0;
        while ((pos = subject.find(search, pos)) != std::string::npos) {
            subject.replace(pos, search.length(), replace);
            pos += replace.length();
        }
    }

    std::filesystem::path GetPathOfGeneratedFile(const std::string& relativePath)
    {
        std::string relative = relativePath;
        ReplaceStringInPlace(relative, "\\", FolderReplacer);
        ReplaceStringInPlace(relative, "/", FolderReplacer);

        return GetAbsoluteRootPath() / GeneratedOutputFolder / relative;
    }
}