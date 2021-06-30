#include "RegistrationFile.hpp"
#include "RegistrationWrittable.hpp"

namespace AP
{
	static void Write(RegistrationWrittable& rw, std::vector<IRegistrationCommandWritter*>& commandWritters)
	{
		for (auto commandWritter : commandWritters)
		{
			*commandWritter << rw;
		}
	}

	void RegistrationFile::Write(std::stringstream& output, AP::TranslationUnitDescriptor& descriptor)
	{
		std::vector<std::string> registrations;
		RegistrationWrittable rw(registrations);
		std::vector<IRegistrationCommandWritter*> commandWritters;

		for (auto rootDescriptor : descriptor.compoundDescriptors)
		{
			rw.SetIdentLevel(0);
			auto commandWritter = rootDescriptor->GetRegistrationCommandWritter();
			if (commandWritter != nullptr)
			{
				commandWritters.push_back(commandWritter);
			}
		}

		if (!commandWritters.empty())
		{
			rw.Write("#include \"AmberReflection.hpp\"");
			rw.NewLine(2);
			AmberReflectionMacroCommandWritter amberReflMacro(commandWritters);
			amberReflMacro << rw;
			WriteToOutput(output, registrations);
		}
	}

	void RegistrationFile::Write(RegistrationWrittable& rw, std::vector<BaseDescriptor*>& descriptors)
	{
		for (auto descriptor : descriptors)
		{
			auto command = descriptor->GetRegistrationCommandWritter();
			if (command)
			{
				*command << rw;
			}
		}

		rw.Write(";");
		rw.NewLine(2);
	}

	void RegistrationFile::WriteToOutput(std::stringstream& output, const std::vector<std::string>& registrations)
	{
		if (registrations.size() > 0)
		{
			for (auto& registration : registrations)
			{
				output << registration;
			}
		}
	}
}