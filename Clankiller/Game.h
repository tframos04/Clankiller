#pragma once

#include "Base.h"
#include "Context.h"
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
};

