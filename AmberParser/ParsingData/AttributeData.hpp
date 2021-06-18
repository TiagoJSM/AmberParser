#pragma once

#include <string>

namespace AP
{
	struct AttributeData
	{
		std::string attributeName;
		std::string attributeParametersText;

		AttributeData(const std::string& attributeName, const std::string& attributeParametersText) :attributeName(attributeName), attributeParametersText(attributeParametersText)
		{
		}
	};
}