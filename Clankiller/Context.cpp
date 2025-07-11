#include "Context.h"

Context::Context()
	: isRunning(true), registry()
{
}

Context::~Context()
{
}

const bool Context::getIsRunning() const
{
	return isRunning && !WindowShouldClose();
}

Registry& Context::getRegistry()
{
	return registry;
}

void Context::test(Shader& lightingShader)
{
	createPlayer(registry, { 0.0f, 1.0f, 0.0f });

	for (int i = 0; i < 5; ++i)
	{
		createEnemy(registry, { 10.0f * (i + 1), 0.5f, 0.0f});
	}

	createPointLight(registry, lightingShader, { -20.0f, -12.0f, -22.0f }, WHITE);
	createPointLight(registry, lightingShader, { 20.0f, 12.0f, 23.0f }, BLUE);
}
