#pragma once

#include "Filewatch/FileWatch.hpp"

namespace APT
{
	class Filewatch 
	{
	public:
		enum class Event
		{
			Added,
			Removed,
			Modified,
			Renamed,
		};
		struct FilewatchEventContext
		{
			const std::string& path;
			const std::string& oldPath;
		};
		using FilewatchCallback = std::function<void(const FilewatchEventContext& ctx, const Filewatch::Event eventType)>;

		Filewatch(std::string path, std::regex regex, FilewatchCallback callback);
	private:
		std::string _oldName;
		FilewatchCallback _callback;
		filewatch::FileWatch<std::string> _filewatchHandler;

		static void FilewatchHandlerCallback(Filewatch& filewatch, const std::string& path, const filewatch::Event changeType);
	};
}