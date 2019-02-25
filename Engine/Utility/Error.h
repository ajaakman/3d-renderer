#pragma once

#ifdef EMSCRIPTEN
#include <iostream>
#define ASSERT(x) if (!(x)) std::cout << "Assertion Failed\n";
#else
#define ASSERT(x) if (!(x)) __debugbreak();
#endif
#define GL(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

extern void GLClearError();

extern bool GLLogCall(const char* function, const char* file, int line);