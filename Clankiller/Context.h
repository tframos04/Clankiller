#pragma once

#include "Base.h"
#include "TransformComponent.h"
#include "ModelComponent.h"

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

