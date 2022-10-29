#pragma once

#include <memory>

#include <spdlog/spdlog.h>

#include "Base.h"

namespace Vally
{

	class Logger
	{
	public:
		static void Initialize();

		static std::shared_ptr<spdlog::logger>& GetLogger();
	private:
		static std::shared_ptr<spdlog::logger> s_logger;
	};

}

#define VALLY_TRACE(...)         ::Vally::Logger::GetLogger()->trace(__VA_ARGS__)
#define VALLY_INFO(...)          ::Vally::Logger::GetLogger()->info(__VA_ARGS__)
#define VALLY_WARN(...)          ::Vally::Logger::GetLogger()->warn(__VA_ARGS__)
#define VALLY_ERROR(...)         ::Vally::Logger::GetLogger()->error(__VA_ARGS__)
#define VALLY_CRITICAL(...)      ::Vally::Logger::GetLogger()->critical(__VA_ARGS__)