#include "Camera2D.h"

#include "../../Libraries/glm/gtc/matrix_transform.hpp"

Camera2D::Camera2D(Window* window, const float & speed, const glm::vec3 & position, const glm::vec3 & direction, const glm::vec3 & worldUp)
{
	m_pWindow = window;
	m_fMovementSpeed = speed;
	m_Direction = direction;
	m_WorldUp = worldUp;
	m_Position = position;
	m_ViewMatrix = glm::mat4(1.f);
}

Camera2D::~Camera2D()
{
}

const glm::mat4 & Camera2D::GetMatrix()
{
	m_ViewMatrix = glm::translate(glm::ortho(0.f, (float)m_pWindow->GetWidth(), 0.f, (float)m_pWindow->GetHeight(), -100.f, 100.f),
		glm::vec3(GetPosition().x, GetPosition().y, 0.f));
	return m_ViewMatrix;	
}

void Camera2D::Rotate(const float & deltaTime, const int & offsetX, const int & offsetY)
{
}

void Camera2D::Move(const float & deltaTime, const int & direction)
{
	switch (direction)
	{
	case FORWARD:
		break;
	case BACK:		
		break;
	case LEFT:		
		m_Position.x += deltaTime * m_fMovementSpeed;
		break;
	case RIGHT:		
		m_Position.x -= deltaTime * m_fMovementSpeed;
		break;
	case UP:
		m_Position.y -= deltaTime * m_fMovementSpeed;
		break;
	case DOWN:
		m_Position.y += deltaTime * m_fMovementSpeed;
		break;
	}
}
