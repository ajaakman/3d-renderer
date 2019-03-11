#pragma once

#include "../Engine/Engine.h"

class Game : Engine
{
public:
	Game();
	~Game() override;
	void Begin() override;
	void Tick(float deltaTime) override;
private:
	float pendulum = 0.f;
	float linear = 0.f;
	float increment = 0.0015f;
};

