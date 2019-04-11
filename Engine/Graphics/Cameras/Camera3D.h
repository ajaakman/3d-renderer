#pragma once

#include "../../Libraries/glm/glm.hpp"
#include "../../Libraries/glm/gtc/matrix_transform.hpp"
#include "Camera.h"

class Camera3D : public Camera
{
public:	
	Camera3D(Window* window, const float & speed, const float & sensitivity, const glm::vec3 & position = glm::vec3(0.f), const glm::vec3 & direction = glm::vec3(0.f, 0.f, 1.f), const glm::vec3 & worldUp = glm::vec3(0.f, 1.f, 0.f));

	virtual ~Camera3D() override {};

	virtual const glm::mat4 & GetMatrix() override;

	inline const glm::vec3 & GetForward() const { return m_Front; };
	inline const glm::vec3 & GetUp() const { return m_Up; };
			
	virtual void Rotate(const float & deltaTime, const int & offsetX, const int & offsetY) override;
	virtual void Move(const float & deltaTime, const int & direction) override;

private:
	
	float m_fPitch;
	float m_fYaw;
	float m_fRoll;

	float m_fSensitivity;
		
	glm::vec3 m_Front;
	glm::vec3 m_Right;
	glm::vec3 m_Up;	
};