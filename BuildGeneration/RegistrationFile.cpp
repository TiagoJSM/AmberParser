#include "RegistrationFile.hpp"
#include "RegistrationWritter.hpp"

namespace AP
{
	static void Write(RegistrationWritter& rw, std::vector<IRegistrationCommandWritter*>& commandWritters)
	{
		for (auto commandWritter : commandWritters)
		{
			*commandWritter << rw;
		}

		/*rw.Write(";");
		rw.NewLine(2);*/
	}

	void RegistrationFile::Write(std::stringstream& output, AP::TranslationUnitDescriptor descriptor)
	{
		std::vector<std::string> registrations;
		RegistrationWritter rw(registrations);
		std::vector<IRegistrationCommandWritter*> commandWritter;

		for (auto rootDescriptor : descriptor.compoundDescriptors)
		{
			rw.SetIdentLevel(0);
			commandWritter.push_back(rootDescriptor->GetRegistrationCommandWritter());
		}

		rw.Write("#include \"AmberReflection.hpp\"");
		rw.NewLine(2);
		AmberReflectionMacroCommandWritter amberReflMacro(commandWritter);
		amberReflMacro << rw;
		WriteToOutput(output, registrations);
	}

	void RegistrationFile::Write(RegistrationWritter& rw, std::vector<BaseDescriptor*>& descriptors)
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