#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

#include "Core/Assert.h"

namespace Vally
{
	std::shared_ptr<spdlog::logger> Logger::sLogger;

	void Logger::Initialize()
	{
		VALLY_ASSERT(sLogger == nullptr, "Can not initialize logger more than once");

		auto sink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
		sink->set_level(spdlog::level::trace);
		sLogger = std::make_shared<spdlog::logger>("Vally logger", sink);
	}

	std::shared_ptr<spdlog::logger>& Logger::GetLogger()
	{
		return sLogger;
	}
}
