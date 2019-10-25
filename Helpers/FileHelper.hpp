#pragma once

#include <string>

namespace AP 
{
	std::string RemoveExtension(const std::string& filename);
	std::string GetExtension(const std::string& filename);
}