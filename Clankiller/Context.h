#pragma once

#include "Base.h"
#include "Player.h"
#include "Enemy.h"

class Context
{
public:
	Context();
	~Context();

	const bool getIsRunning() const;
	Registry& getRegistry();

	void test();

private:
	bool isRunning;
	Registry registry;
	
	Model dummyModel;
};
