#include "Program.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "GL/glew.h"

#include "../Utility/Error.h"

Program::Program(const std::string & filepath)
	: m_FilePath(filepath), m_ShaderID(0)
{
	ShaderProgramSource source = ParseShader(filepath);
	m_ShaderID = CreateShader(source.VertexSource, source.FragmentSource);
}

Program::~Program()
{
	GL(glDeleteProgram(m_ShaderID));
}

Program::ShaderProgramSource Program::ParseShader(const std::string& filepath)
{
	std::fstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::FRAGMENT;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}

unsigned int Program::CompileShader(unsigned int type, const std::string& source)
{
	GL(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GL(glShaderSource(id, 1, &src, nullptr));
	GL(glCompileShader(id));

	int result;
	GL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GL(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "Failed to Compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "Shader!" << std::endl;
		std::cout << message << std::endl;
		GL(glDeleteShader(id));
		return 0;
	}

	return id;
}

unsigned int Program::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GL(unsigned int program = glCreateProgram());
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GL(glAttachShader(program, vs));
	GL(glAttachShader(program, fs));
	GL(glLinkProgram(program));
	GL(glValidateProgram(program));

	GL(glDeleteShader(vs));
	GL(glDeleteShader(fs));

	return program;
}

void Program::Bind() const
{
	GL(glUseProgram(m_ShaderID));
}

void Program::SetUniform4f(const std::string & name, float v0, float v1, float v2, float v3)
{
	GL(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

int Program::GetUniformLocation(const std::string & name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GL(int location = glGetUniformLocation(m_ShaderID, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

	m_UniformLocationCache[name] = location;
	return location;
}
