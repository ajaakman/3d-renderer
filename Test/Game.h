#pragma once

#include "../Engine/Engine.h"

class Game : Engine
{
public:
	Game();
	~Game() override;
	void Begin() override;
	void Tick() override;
private:
	float col = 0.0f;
	float rot = 0.0f;
	float increment = 0.02f;
};

