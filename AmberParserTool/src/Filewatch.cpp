#include "Filewatch.hpp"

namespace APT
{
	static const std::string EmptyString;

    Filewatch::Filewatch(std::string path, std::regex regex, FilewatchCallback callback)
        :_callback(callback), 
		_filewatchHandler(path,
			regex,
			[this](const std::string& path, const filewatch::Event changeType) {
				FilewatchHandlerCallback(*this, path, changeType);
			})
    {			
    }

	void Filewatch::FilewatchHandlerCallback(Filewatch& filewatch, const std::string& path, const filewatch::Event changeType)
	{
		FilewatchEventContext ctx{ path , filewatch._oldName };
		switch (changeType)
		{
		case filewatch::Event::added:
			filewatch._callback(ctx, Event::Added);
			break;
		case filewatch::Event::removed:
			filewatch._callback(ctx, Event::Removed);
			break;
		case filewatch::Event::modified:
			filewatch._callback(ctx, Event::Modified);
			break;
		case filewatch::Event::renamed_old:
			filewatch._oldName = path;
			break;
		case filewatch::Event::renamed_new:
			
			filewatch._callback(ctx, Event::Renamed);
			filewatch._oldName = EmptyString;
			break;
		};
	}
}