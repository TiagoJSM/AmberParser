#include "RegistrationWrittable.hpp"

namespace AP
{
	RegistrationWrittable::RegistrationWrittable(std::vector<std::string>& output)
		: _output(output)
	{
	}

	void RegistrationWrittable::Write(const std::string& data)
	{
		Ident();
		_output.push_back(data);
		_requiresIdent = false;
	}

	void RegistrationWrittable::NewLine(int count)
	{
		while (count-- > 0)
		{
			_output.push_back("\n");
		}
		_requiresIdent = true;
	}

	void RegistrationWrittable::SetIdentLevel(int identLevel)
	{
		_identLevel = identLevel;
	}

	void RegistrationWrittable::IncrementIdentLevel()
	{
		_identLevel++;
	}

	void RegistrationWrittable::DecrementIdentLevel()
	{
		_identLevel--;
	}

	int RegistrationWrittable::GetIdentLevel() const
	{
		return _identLevel;
	}

	void RegistrationWrittable::Ident()
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