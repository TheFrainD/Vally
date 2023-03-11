#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <memory>

#include "Core/Engine.h"
#include "Core/Log.h"

int main(int, char**)
{
	Vally::Logger::Initialize();
	std::unique_ptr<Vally::Engine> pEngine;

	try
	{
		pEngine = std::make_unique<Vally::Engine>();
		pEngine->Run();
	}
	catch (const std::exception& e)
	{
		VALLY_CRITICAL("Critical error: {}", e.what());
		VALLY_CRITICAL("Stop executing!");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}