#pragma once

class Engine
{
public:
	Engine();

	virtual ~Engine() = 0;

	virtual void Init() = 0;

	virtual void Loop() = 0;
};

