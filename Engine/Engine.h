#pragma once

#include "IO/Window.h"
#include "Libraries/glm/glm.hpp"
#include "Graphics/Renderer.h"

class Engine
{
protected:

	Engine();

	Renderer* p_Renderer;


	virtual ~Engine() = 0;

	virtual void Begin() = 0;

	virtual void Tick(float fDeltaTime) = 0;

	void Loop();

	inline const bool & IsPressedW() { return p_Window->IsPressedW(); }
	inline const bool & IsPressedA() { return p_Window->IsPressedA(); }
	inline const bool & IsPressedS() { return p_Window->IsPressedS(); }
	inline const bool & IsPressedD() { return p_Window->IsPressedD(); }
	inline const int & GetWidth()    { return p_Window->GetWidth();   }
	inline const int & GetHeight()   { return p_Window->GetHeight();  }

private:
	Window* p_Window;
};

