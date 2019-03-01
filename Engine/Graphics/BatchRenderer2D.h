#pragma once

#include "../Libraries/glm/glm.hpp"

#include "GLBase/ElementArrayBuffer.h"
#include "GLBase/Buffer.h"
#include "GLBase/VertexArray.h"
#include "GLBase/Program.h"

#include <unordered_map>
#include <string>

class BatchRenderer2D
{
public:
	BatchRenderer2D();
	~BatchRenderer2D();

	class SimpleBatchRenderable
	{
	public:
		SimpleBatchRenderable(glm::vec2 position, glm::vec2 size, int centered = 0);
		~SimpleBatchRenderable();

		void SetColor(glm::vec4 color);
		void SetPosition(glm::vec2 position);
		void SetRotation(glm::vec3 rotation);
		glm::vec2 m_Position;
		glm::vec3 m_Rotation;
		glm::vec4 m_Color;
	private:
	};

	void Clear();
	void Draw();
	bool CreateSimpleRenderable(const std::string & name, const glm::vec2 & position, const glm::vec2 & size, const int & centered = 0);
	SimpleBatchRenderable* GetSimpleRenderable(const std::string & name);
private:
	ElementArrayBuffer* p_ElementArrayBuffer;
	VertexArray* p_VertexArray;
	Program* p_Program;
	Buffer* p_Buffer;

	std::unordered_map<std::string, SimpleBatchRenderable*> m_SimpleRenderables;
};

