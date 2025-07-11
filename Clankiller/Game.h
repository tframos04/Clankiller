#pragma once

#include "Base.h"
#include "Context.h"
#include "AssetManager.h"
#include "InputSystem.h"
#include "ActionSystem.h"
#include "MovementSystem.h"
#include "CollisionSystem.h"
#include "CameraSystem.h"
#include "LightingSystem.h"
#include "RenderSystem.h"

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	Context context;
	Camera3D camera;
	InputMapping inputMapping;
	Shader lightingShader;
	Light mainLight;
};
