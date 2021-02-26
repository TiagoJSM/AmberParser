#include "RegistrationFile.hpp"
#include "RegistrationWritter.hpp"

namespace AP
{
	static void Ident(std::stringstream& output, int identLevel)
	{
		while (identLevel > 0)
		{
			output << "\t";
			identLevel--;
		}
	}

	void RegistrationFile::Write(std::stringstream& output, AP::TranslationUnitDescriptor descriptor)
	{
		std::vector<std::string> registrations;
		RegistrationWritter rw(registrations);
		std::vector<BaseDescriptor*> descriptors;

		for (auto rootDescriptor : descriptor.compoundDescriptors)
		{
			descriptors.clear();
			registrations.clear();
			descriptors.push_back(rootDescriptor);
			GetDescriptors(rootDescriptor, descriptors);
			Write(rw, descriptors);

			WriteToOutput(output, registrations);
		}
	}

	void RegistrationFile::GetDescriptors(BaseDescriptor* descriptor, std::vector<BaseDescriptor*>& descriptors)
	{
		for (auto child : descriptor->GetChildren())
		{
			descriptors.push_back(child);
			GetDescriptors(child, descriptors);
		}
	}

	void RegistrationFile::Write(RegistrationWritter& rw, std::vector<BaseDescriptor*>& descriptors)
	{
		for (auto descriptor : descriptors)
		{
			auto command = descriptor->GetRegistrationCommandWritter();
			if (command)
			{
				command->operator<<(rw);
			}
		}
	}

	void RegistrationFile::WriteToOutput(std::stringstream& output, const std::vector<std::string>& registrations)
	{
		if (registrations.size() > 0)
		{
			int idx = 0;
			for (auto& registration : registrations)
			{
				Ident(output, idx == 0 ? 0 : 1);
				output << registration;
				if ((idx + 1) != registrations.size()) 
				{
					output << std::endl;
				}
				else 
				{
					output << ";" << std::endl << std::endl;
				}
				idx++;
			}
		}
	}
}