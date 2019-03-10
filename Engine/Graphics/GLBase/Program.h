#pragma once

#include <string>
#include <unordered_map>
#include "../../Libraries/glm/glm.hpp"

class Program
{
	public:
		Program();
		Program(const std::string& filepath);
		~Program();

		void Bind() const;

		void SetUniform1i(const std::string& name, const int value);
		void SetUniform1f(const std::string& name, const float value);
		void SetUniform4f(const std::string& name, const glm::vec4& vector);
		void SetUniform3f(const std::string& name, const glm::vec3& vector);
		void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	private:

		struct ShaderProgramSource
		{
			std::string VertexSource;
			std::string FragmentSource;
		};
		std::string m_FilePath;
		unsigned m_ShaderID;
		std::unordered_map<std::string, int> m_UniformLocationCache;

	private:
		ShaderProgramSource ParseShader(const std::string& filepath);
		unsigned CompileShader(unsigned type, const std::string& source);
		unsigned CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

		int GetUniformLocation(const std::string& name);
};

