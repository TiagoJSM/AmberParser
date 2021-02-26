#include "RegistrationWritter.hpp"

namespace AP
{
	RegistrationWritter::RegistrationWritter(std::vector<std::string>& output)
		: _output(output)
	{
	}

	void RegistrationWritter::Write(const std::string& data)
	{
		Ident();
		_output.push_back(data);
		_requiresIdent = false;
	}

	void RegistrationWritter::NewLine(int count)
	{
		while (count-- > 0)
		{
			_output.push_back("\n");
		}
		_requiresIdent = true;
	}

	void RegistrationWritter::SetIdentLevel(int identLevel)
	{
		_identLevel = identLevel;
	}

	void RegistrationWritter::IncrementIdentLevel()
	{
		_identLevel++;
	}

	void RegistrationWritter::DecrementIdentLevel()
	{
		_identLevel--;
	}

	int RegistrationWritter::GetIdentLevel() const
	{
		return _identLevel;
	}

	void RegistrationWritter::Ident()
	{
		if (!_requiresIdent)
		{
			return;
		}
		auto identLevel = _identLevel;
		while (identLevel-- > 0)
		{
			_output.push_back("\t");
		}
	}
}