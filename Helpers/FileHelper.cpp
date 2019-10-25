#pragma once

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
}