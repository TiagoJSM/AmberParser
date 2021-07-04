#include "FileHelper.hpp"

#include <string>

namespace AP
{
	std::string RemoveExtension(const std::string& filename) 
	{
		size_t lastdot = filename.find_last_of(".");
		if (lastdot == std::string::npos) return filename;
		return filename.substr(0, lastdot);
	}

	std::string GetExtension(const std::string& filename)
	{
		return filename.substr(filename.find_last_of(".") + 1);
	}

	std::filesystem::path ReplacePath(const std::filesystem::path& path, const std::filesystem::path& toReplace, const std::filesystem::path& replacement)
	{
		auto strPath = path.string();
		
		auto startPos = strPath.find(toReplace.string());
		if (startPos == std::string::npos)
			return std::filesystem::path();
		return std::filesystem::path(strPath.replace(startPos, toReplace.string().length(), replacement.string()));
	}
}