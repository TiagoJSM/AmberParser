#include <iostream>
#include <filesystem>
#include <sstream>

#include "Parser/Parser.h"
#include "BuildGeneration/RegistrationFile.hpp"

#include "Config.hpp"
#include "FileUtils.hpp"
#include "Filewatch.hpp"

using namespace std;

#define INTERESTING __attribute__((annotate("interesting")))

const std::string CMakeFile = "CMakeLists.txt";

int main(int argc, char* argv[])
{
	APT::Init(argc, argv);

	std::filesystem::create_directory(APT::GeneratedOutputFolder);

	APT::Filewatch watch(
		APT::GetAbsoluteRootPath().string(),
		std::regex("^(?!auto-generated.*)(.*\.(h|hpp))$"),
		[](const APT::Filewatch::FilewatchEventContext& ctx, const APT::Filewatch::Event changeType) {
			std::cout << ctx.path << " : ";
			auto path = APT::GetPathOfGeneratedFile(ctx.path);

			switch (changeType)
			{
			/*case APT::Filewatch::Event::Added:
				std::cout << "The file was added to the directory." << '\n';
				break;*/
			case APT::Filewatch::Event::Removed:
				std::cout << "The file was removed from the directory." << '\n';
				std::filesystem::remove(path);
				break;
			case APT::Filewatch::Event::Added:
			case APT::Filewatch::Event::Modified:
			{
				std::stringstream output;
				AP::Parser parser;
				{
					auto translationUnitDesc = parser.Parse((APT::GetAbsoluteRootPath() / ctx.path).string());
					AP::RegistrationFile file;
					file.Write(output, translationUnitDesc);
				}
				auto s = output.str();

				if (!std::filesystem::exists(path))
				{
					std::filesystem::create_directories(path.parent_path());
				}

				std::fstream outputFileStream(path, fstream::in | fstream::out | fstream::trunc);
				outputFileStream << s;
				outputFileStream.close();
			}
			break;
			case APT::Filewatch::Event::Renamed:
				std::cout << "The file was renamed and this is the old name " << ctx.oldPath << '\n';
				break;
			};
		}
	);

	while (true) {}
}