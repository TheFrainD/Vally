#pragma once

#include "Base.h"
#include "Core/Log.h"

#ifdef VALLY_DEBUG

#ifdef VALLY_PLATFORM_WINDOWS

#define VALLY_DEBUG_BREAK() __debugbreak()

#else

#define VALLY_DEBUG_BREAK() __builtin_trap()

#endif

#define VALLY_ASSERT(EXPR, MSG) {\
	if ((EXPR)) {\
	} else {\
		VALLY_CRITICAL("Assertation failure: ({}), {} -- {}:{}", #EXPR, #MSG, __FILE__, __LINE__);\
		VALLY_DEBUG_BREAK();\
		}\
	}

#else

#define VALLY_ASSERT(EXPR, MSG)

#endif