#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

#include "Core/Assert.h"

namespace Vally
{
	std::shared_ptr<spdlog::logger> Logger::s_logger;

	void Logger::Initialize()
	{
		VALLY_ASSERT(s_logger == nullptr, "Can not initialize logger more than once");

		auto sink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
		sink->set_level(spdlog::level::trace);
		s_logger = std::make_shared<spdlog::logger>("Vally logger", sink);
	}

	std::shared_ptr<spdlog::logger>& Logger::GetLogger()
	{
		return s_logger;
	}
}
