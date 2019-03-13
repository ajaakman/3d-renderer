#pragma once

#include "../../Libraries/glm/glm.hpp"
#include "../../IO/Window.h"

class Camera
{
public:
	enum Direction { FORWARD = 0, BACK, LEFT, RIGHT, UP, DOWN };

	Camera() {};

	virtual ~Camera() {};

	inline const glm::vec3 & GetPosition() const { return m_Position; };

	virtual const glm::mat4 & GetMatrix() = 0;

	virtual void Move(const float & deltaTime, const int & direction) = 0;
	virtual void Rotate(const float & deltaTime, const int & offsetX, const int & offsetY) = 0;

public:
	glm::mat4 m_ViewMatrix;
	glm::vec3 m_Position;
	glm::vec3 m_Direction;
	glm::vec3 m_WorldUp;

	Window* m_pWindow;

	float m_fMovementSpeed;
};