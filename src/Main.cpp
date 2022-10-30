#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include "Core/Engine.h"
#include "Core/Log.h"

int main(int, char**)
{
	Vally::Logger::Initialize();
	Vally::Engine engine;

	try
	{
		engine.Run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}