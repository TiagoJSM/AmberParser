#pragma once

#include <string>
#include <filesystem>

namespace AP 
{
	std::string RemoveExtension(const std::string& filename);
	std::string GetExtension(const std::string& filename);
	std::filesystem::path ReplacePath(const std::filesystem::path& path, const std::filesystem::path& toReplace, const std::filesystem::path& replacement);
}