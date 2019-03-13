#pragma once

#include "Camera.h"

class Camera2D : public Camera
{
public:
	Camera2D(Window* window, const float & speed, const glm::vec3 & position = glm::vec3(0.f), const glm::vec3 & direction = glm::vec3(0.f, 0.f, -1.f), const glm::vec3 & worldUp = glm::vec3(0.f, 1.f, 0.f));
	virtual ~Camera2D() override;
	
	virtual const glm::mat4 & GetMatrix() override;

	virtual void Rotate(const float & deltaTime, const int & offsetX, const int & offsetY) override;
	virtual void Move(const float & deltaTime, const int & direction) override;
};

