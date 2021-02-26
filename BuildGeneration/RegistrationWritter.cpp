#include "RegistrationWritter.hpp"

namespace AP
{
	RegistrationWritter::RegistrationWritter(std::vector<std::string>& output)
		: _output(output)
	{
	}

	void RegistrationWritter::Write(const std::string& data)
	{
		_output.push_back(data);
	}
}