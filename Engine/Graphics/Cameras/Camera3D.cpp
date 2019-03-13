#include "Camera3D.h"

Camera3D::Camera3D(Window* window, const float & speed, const float & sensitivity, const glm::vec3 & position, const glm::vec3 & direction, const glm::vec3 & worldUp)
	:m_fSensitivity(sensitivity), m_Up(worldUp), m_Right(glm::vec3(0.f)), m_fPitch(0.f), m_fYaw(-90.f), m_fRoll(0.f)
{
	m_pWindow = window;
	m_fMovementSpeed = speed;
	m_Direction = direction;
	m_WorldUp = worldUp;
	m_Position = position;
	m_ViewMatrix = glm::mat4(1.f);
#ifdef EMSCRIPTEN
	m_fSensitivity = 0.02f;
#endif
}

const glm::mat4 & Camera3D::GetMatrix()
{
	m_Front.x = cos(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch));
	m_Front.y = sin(glm::radians(m_fPitch));
	m_Front.z = sin(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch));

	m_Front = glm::normalize(m_Front);
	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));

	m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	m_ViewMatrix = glm::perspective(80.f, (float)m_pWindow->GetWidth() / (float)m_pWindow->GetHeight(), 1.f, 10000.f) * m_ViewMatrix;

	return m_ViewMatrix;
}

void Camera3D::Rotate(const float & deltaTime, const int & offsetX, const int & offsetY)
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

void Camera3D::Move(const float & deltaTime, const int & direction)
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
	case UP:
		break;
	case DOWN:
		break;
	}
}