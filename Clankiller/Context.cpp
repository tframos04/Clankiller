#include "Context.h"

Context::Context()
	: isRunning(true), registry(), dummyModel({ 0 })
{
}

Context::~Context()
{
	UnloadModel(dummyModel);
}

const bool Context::getIsRunning() const
{
	return isRunning && !WindowShouldClose();
}

Registry& Context::getRegistry()
{
	return registry;
}

void Context::test()
{
	Mesh cubeMesh = GenMeshCube(1.0f, 1.0f, 1.0f);
	dummyModel = LoadModelFromMesh(cubeMesh);

	createPlayer(registry, dummyModel, { 0.0f, 0.0f, 0.0f });

	for (int i = 0; i < 5; ++i)
	{
		createEnemy(registry, dummyModel, { 10.0f * (i + 1), 10.0f * (i + 1), 10.0f * (i + 1) });
	}
}
