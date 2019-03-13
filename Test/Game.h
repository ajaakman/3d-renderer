#pragma once

#include "../Engine/Engine.h"

class Game : Engine
{
public:
	Game();
	virtual ~Game() override;
	virtual void Begin() override;
	virtual void Tick(float deltaTime) override;
private:

	Renderable* p_Box = nullptr;
	std::vector<Renderable*> p_Boxes;

	bool created = false;

	float pendulum = 0.f;
	float linear = 0.f;
	float increment = 0.0015f;
};

