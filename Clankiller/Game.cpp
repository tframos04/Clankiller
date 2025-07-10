#include "Game.h"

Game::Game()
	: context(), camera()
{
	InitWindow(800, 450, "raylib [core] example - basic window");
	SetTargetFPS(60);

	camera.position = { 10.0f, 10.0f, 10.0f }; 
	camera.target = { 0.0f, 0.0f, 0.0f };     
	camera.up = { 0.0f, 1.0f, 0.0f };         
	camera.fovy = 45.0f;                      
	camera.projection = CAMERA_PERSPECTIVE;

	context.test();
}

Game::~Game()
{
	CloseWindow();
}

void Game::run()
{
	Registry& registry = context.getRegistry();

	while (context.getIsRunning())
	{
		UpdateCamera(&camera, CAMERA_ORBITAL);
		RenderSystem(registry, camera);
	}
}
