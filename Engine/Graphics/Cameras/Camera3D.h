#pragma once

#include "../../Libraries/glm/glm.hpp"
#include "../../Libraries/glm/gtc/matrix_transform.hpp"
#include "Camera.h"

class Camera3D : public Camera
{
public:	

	Camera3D(const glm::vec3 & position, const glm::vec3 & direction, const glm::vec3 & worldUp)
		:m_Direction(direction), m_WorldUp(worldUp), m_fMovementSpeed(0.5f), m_fSensitivity(1.f),
		 m_Up(worldUp), m_Right(glm::vec3(0.f)), m_fPitch(0.f), m_fYaw(-90.f), m_fRoll(0.f)
	{
		m_Position = position;
		m_ViewMatrix = glm::mat4(1.f);
#ifdef EMSCRIPTEN
		m_fSensitivity = 0.01f;
#endif
	}

	virtual ~Camera3D() override {};

	virtual const glm::mat4 & GetViewMatrix() override
	{
		m_Front.x = cos(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch));
		m_Front.y = sin(glm::radians(m_fPitch));
		m_Front.z = sin(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch));

		m_Front = glm::normalize(m_Front);
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));

		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
		
		return m_ViewMatrix;
	}
			
	virtual void UpdateInput(const float & deltaTime, const int & offsetX, const int & offsetY) override
	{
		UpdateMouseInput(deltaTime, offsetX, offsetY);
	}

	virtual void UpdateKeyboardInput(const float & deltaTime, const int & direction) override
	{
		switch (direction)
		{
		case FORWARD:
			m_Position += m_Front * m_fMovementSpeed * deltaTime;
			break;
		case BACK:
			m_Position -= m_Front * m_fMovementSpeed * deltaTime;
			break;
		case LEFT:
			m_Position += m_Right * m_fMovementSpeed * deltaTime;
			break;
		case RIGHT:
			m_Position -= m_Right * m_fMovementSpeed * deltaTime;
			break;
		}
	}

private:

	void UpdateMouseInput(const float & deltaTime, const int & offsetX, const int & offsetY)
	{
		m_fPitch -= (float)offsetY * m_fSensitivity * deltaTime;
		m_fYaw -= (float)offsetX * m_fSensitivity * deltaTime;

		if (m_fPitch > 80.f)
			m_fPitch = 80.f;
		else if (m_fPitch < -80.f)
			m_fPitch = -80.f;

		if (m_fYaw > 360.f || m_fYaw < -360.f)
			m_fYaw = 0.f;
	}	

	float m_fPitch;
	float m_fYaw;
	float m_fRoll;

	float m_fMovementSpeed;
	float m_fSensitivity;
		
	glm::vec3 m_Front;
	glm::vec3 m_Right;
	glm::vec3 m_Up;

	glm::vec3 m_Direction;
	glm::vec3 m_WorldUp;
};