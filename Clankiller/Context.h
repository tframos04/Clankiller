#pragma once

class Context
{
public:
	Context();
	~Context();

	const bool getIsRunning() const;

private:
	bool isRunning;
};

