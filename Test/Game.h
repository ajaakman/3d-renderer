#pragma once
#include <Engine.h>

class Game : Engine
{
public:
	Game();
	~Game() override;
	void Init() override;
	void Loop() override;
};
