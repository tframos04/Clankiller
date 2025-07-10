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

	auto playerEntity = registry.create();
	registry.emplace<TransformComponent>(playerEntity,
		Vector3{ 0.0f, 0.5f, 0.0f },
		Vector3{ 0.0f, 0.0f, 0.0f },
		Vector3{ 1.0f, 1.0f, 1.0f }
	);
	registry.emplace<ModelComponent>(playerEntity, dummyModel, BLUE);

	for (int i = 0; i < 5; ++i)
	{
		auto enemyEntity = registry.create();
		registry.emplace<TransformComponent>(enemyEntity,
			Vector3{ (float)(i - 2) * 3.0f, 0.25f, 5.0f },
			Vector3{ 0.0f, 0.0f, 0.0f },
			Vector3{ 0.5f, 0.5f, 0.5f }
		);
		registry.emplace<ModelComponent>(enemyEntity, dummyModel, RED);
	}
}
