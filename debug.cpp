#include "debug.h"

void Debug::Log(std::string message)
{
	std::cout << message << std::endl;
}

void Debug::Log(const char* message)
{
	std::cout << message << std::endl;
}

void Debug::Warning(std::string message)
{
	std::cout << message << std::endl;
}

void Debug::Warning(const char* message)
{
	std::cout << message << std::endl;
}

void Debug::Error(std::string message)
{
	std::cout << message << std::endl;
}

void Debug::Error(const char* message)
{
	std::cout << message << std::endl;
}

Debug::Debug()
{
}

Debug::~Debug()
{
}

