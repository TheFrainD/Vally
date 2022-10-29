#pragma once

#include <cstdint>

#ifdef _DEBUG
#define VALLY_DEBUG
#endif

// Platform detection
#if defined(_WIN32)

#define VALLY_PLATFORM_WINDOWS

#ifndef NOMINMAX

#define NOMINMAX

#endif // !NOMINMAX

#elif defined(__linux__)
	// Linux
#define VALLY_PLATFORM_LINUX

#endif

namespace Vally
{
	typedef uint8_t		U8;
	typedef uint16_t	U16;
	typedef uint32_t	U32;
	typedef uint64_t	U64;

	typedef int8_t		I8;
	typedef int16_t		I16;
	typedef int32_t		I32;
	typedef int64_t		I64;

	typedef float		F32;
}