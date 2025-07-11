#pragma once

#include "Base.h"
#include "Player.h"
#include "Enemy.h"
#include "PointLight.h"

class Context
{
public:
	Context();
	~Context();

	const bool getIsRunning() const;
	Registry& getRegistry();

	void test(Shader& lightingShader);

private:
	bool isRunning;
	Registry registry;
};
