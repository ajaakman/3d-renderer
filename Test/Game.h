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
	float col = 0.f;
	float rot = 0.f;
	float increment = 0.0015f;
};

