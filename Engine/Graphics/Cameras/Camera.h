#pragma once

#include "../../Libraries/glm/glm.hpp"

class Camera
{
public:
	enum Direction { FORWARD = 0, BACK, LEFT, RIGHT };

	Camera(glm::vec3 position = glm::vec3(0.f))
		:m_ViewMatrix(glm::mat4(1.f)), m_Position(glm::vec3(0.f))
	{};

	virtual ~Camera() {};

	virtual const glm::mat4 & GetViewMatrix() { return m_ViewMatrix; }
	inline const glm::vec3 & GetPosition() const { return m_Position; };

	virtual void UpdateKeyboardInput(const float & deltaTime, const int & direction) = 0;
	virtual void UpdateInput(const float & deltaTime, const int & offsetX, const int & offsetY) = 0;

public:
	glm::mat4 m_ViewMatrix;
	glm::vec3 m_Position;
};