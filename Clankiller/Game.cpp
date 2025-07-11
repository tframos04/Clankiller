#include "Game.h"

Game::Game()
	: context(), camera()
{
	InitWindow(800, 450, "ClanKiller");
	SetTargetFPS(60);
	DisableCursor();

	auto& assets = AssetManager::getInstance();

	assets.models.load("cube", "assets/cube.obj");
	assets.shaders.load("lighting", "assets/lighting");

	lightingShader = assets.shaders.get("lighting"); 
	lightingShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(lightingShader, "viewPos");

	Model& cubeModel = assets.models.get("cube");
	for (int i = 0; i < cubeModel.materialCount; i++) {
		cubeModel.materials[i].shader = lightingShader;
	}

	camera.up = { 0.0f, 1.0f, 0.0f };
	camera.fovy = 60.0f;
	camera.projection = CAMERA_PERSPECTIVE;
	context.test(lightingShader);
}

Game::~Game()
{
	AssetManager::getInstance().unloadAllAssets();
	CloseWindow();
}

void Game::run()
{
	Registry& registry = context.getRegistry();

	while (context.getIsRunning())
	{
		float deltaTime = GetFrameTime();

		InputSystem(registry, inputMapping);

		ActionSystem(registry);

		MovementSystem(registry, deltaTime);

		CollisionSystem(registry);

		CameraSystem(registry, camera);

		LightingSystem(registry, lightingShader);

		RenderSystem(registry, camera);
	}
}
