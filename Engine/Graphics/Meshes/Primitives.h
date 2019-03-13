#pragma once

#include <array>

struct Sprite
{
	const std::array<float, 28> vertices = {
							-0.5f, -0.5f,     0.f, 0.f,     0.f, 0.f, 1.f,
							 0.5f, -0.5f,     1.f, 0.f,     0.f, 0.f, 1.f,
							 0.5f,  0.5f,     1.f, 1.f,     0.f, 0.f, 1.f,
							-0.5f,  0.5f,     0.f, 1.f,     0.f, 0.f, 1.f,
	};

	std::array<unsigned, 6> indices = {
		0, 1, 2,
		0, 2, 3
	};

	std::array<unsigned, 3> layout = { 2, 2, 3 };
};

struct Cube
{
	std::array<float, 64> vertices = {
							-0.5f, -0.5f,  0.5f,     1.f, 1.f,    -0.5f, -0.5f,  0.5f,
							 0.5f, -0.5f,  0.5f,     0.f, 1.f,     0.5f, -0.5f,  0.5f,
							 0.5f,  0.5f,  0.5f,     0.f, 0.f,     0.5f,  0.5f,  0.5f,
							-0.5f,  0.5f,  0.5f,     1.f, 0.f,    -0.5f,  0.5f,  0.5f,
							-0.5f, -0.5f, -0.5f,     0.f, 1.f,    -0.5f, -0.5f, -0.5f,
							 0.5f, -0.5f, -0.5f,     1.f, 1.f,     0.5f, -0.5f, -0.5f,
							 0.5f,  0.5f, -0.5f,     1.f, 0.f,     0.5f,  0.5f, -0.5f,
							-0.5f,  0.5f, -0.5f,     0.f, 0.f,    -0.5f,  0.5f, -0.5f
	};

	std::array<unsigned, 36> indices = {
		0, 1, 2,
		0, 2, 3,
		1, 6, 2,
		1, 5, 6,
		4, 7, 5,
		7, 6, 5,
		3, 7, 4,
		0, 3, 4,
		3, 6, 7,
		3, 2, 6,
		0, 4, 5,
		0, 5, 1
	};

	std::array<unsigned, 3> layout = { 3, 2, 3 };
};