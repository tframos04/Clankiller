#include "Game.h"

Game::Game()
	: context(), camera()
{
	InitWindow(800, 450, "ClanKiller");
	SetTargetFPS(60);
	DisableCursor();

	auto& assets = AssetManager::getInstance();

	assets.models.load("cube", "assets/cube.obj");

	camera.up = { 0.0f, 1.0f, 0.0f };
	camera.fovy = 60.0f;
	camera.projection = CAMERA_PERSPECTIVE;
	context.test();
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

		CameraSystem(registry, camera);

		RenderSystem(registry, camera);
	}
}
