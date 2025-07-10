#include "Context.h"

Context::Context()
	: isRunning(true)
{
}

Context::~Context()
{
}

const bool Context::getIsRunning() const
{
	return isRunning;
}
