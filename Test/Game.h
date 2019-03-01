#pragma once

#include "../Engine/Engine.h"

class Game : Engine
{
public:
	Game();
	~Game() override;
	void Begin() override;
	void Tick(double deltaTime) override;
private:
	float col = 0.0f;
	float rot = 0.0f;
	float increment = 0.0015f;
};

