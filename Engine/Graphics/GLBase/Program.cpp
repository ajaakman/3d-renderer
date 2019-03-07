#include "Program.h"

#ifdef EMSCRIPTEN
#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#else
#include <GL/glew.h>
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../../Utility/Error.h"

Program::Program(const int& type)
	:m_ShaderID(0)
{
	std::string vertex, fragment;
	if (type == 0)
	{
#ifdef EMSCRIPTEN
		vertex =
			"attribute highp vec4 position;\n"
			"uniform mat4 u_MVP;\n"
			"\n"
			"void main()\n"
			"{\n"
			"	gl_Position = u_MVP * position;\n"
			"}\n";
		fragment =
			"precision highp float;\n"
			"\n"
			"uniform vec4 u_Color;\n"
			"\n"
			"void main()\n"
			"{\n"
			"	gl_FragColor = u_Color;\n"
			"}\n";
#else
		vertex =
			"#version 330 core\n"
			"\n"
			"layout(location = 0) in vec4 position;\n"
			"\n"
			"uniform mat4 u_MVP;\n"
			"\n"
			"void main()\n"
			"{\n"
			"	gl_Position = u_MVP * position;\n"
			"};\n";
		fragment =
			"#version 330 core\n"
			"\n"
			"layout(location = 0) out vec4 color;\n"
			"\n"
			"uniform vec4 u_Color;\n"
			"\n"
			"void main()\n"
			"{\n"
			"	color = u_Color;\n"
			"};\n";
#endif
	}
	else if (type == 1)
	{
#ifdef EMSCRIPTEN
		vertex =
			"attribute highp vec4 position;\n"
			"attribute highp vec2 texCoord;\n"
			"\n"
			"uniform mat4 u_MVP;\n"
			"\n"
			"varying highp vec2 v_TexCoord;\n"
			"\n"
			"void main()\n"
			"{\n"
			"	gl_Position = u_MVP * position;\n"
			"	v_TexCoord = texCoord;\n"
			"}\n";
		fragment =
			"precision highp float;\n"
			"\n"
			"varying highp vec2 v_TexCoord;\n"
			"\n"
			"uniform vec4 u_Color;\n"
			"uniform sampler2D u_Texture0;\n"
			"uniform sampler2D u_Texture1;\n"
			"\n"
			"void main()\n"
			"{\n"
			"	vec4 texColor = texture2D(u_Texture0, v_TexCoord);\n"
			"	gl_FragColor = texColor * u_Color;\n"
			"}\n";
#else
		vertex =
			"#version 330 core\n"
			"\n"
			"layout(location = 0) in vec4 position;\n"
			"layout(location = 1) in vec2 texCoord;\n"
			"layout(location = 2) in vec3 normal;\n"
			"\n"
			"out vec2 v_TexCoord;\n"
			"out vec3 v_Normal;\n"
			"out vec3 v_Position;\n"
			"\n"
			"uniform mat4 u_MVP;\n"
			"uniform mat4 u_Model;\n"
			"\n"
			"void main()\n"
			"{\n"
			"	gl_Position = u_MVP * position;\n"
			"	v_Normal = mat3(u_Model) * normal;\n"
			"	v_TexCoord = texCoord;\n"
			"	v_Position = vec4(u_Model * position).xyz;\n"
			"};\n";
		fragment =
			"#version 330 core\n"
			"\n"
			"in vec2 v_TexCoord;"
			"in vec3 v_Normal;"
			"in vec3 v_Position;"
			"\n"
			"layout(location = 0) out vec4 color;\n"
			"\n"
			"uniform vec4 u_Color;\n"
			"uniform vec3 u_Light;\n"
			"uniform sampler2D u_Texture0;\n"
			"uniform sampler2D u_Texture1;\n"
			"\n"
			"void main()\n"
			"{\n"
			"	vec4 texColor = texture(u_Texture0, v_TexCoord);\n"
			"	vec3 ambientLight = vec3(0.1f, 0.1f, 0.1f);\n"
			"	vec3 posToLightDirVec = normalize(v_Position - u_Light);\n"
			"	vec3 diffuseColor = vec3( 1.f, 1.f, 1.f );\n"
			"	float diffuse = clamp(dot(posToLightDirVec, v_Normal), 0, 1);\n"
			"	vec3 diffuseFinal = diffuseColor * diffuse;\n"
			"	color = texColor * u_Color * (vec4(ambientLight, 1.0f) + vec4(diffuseFinal, 1.f));\n"
			"};\n";
#endif
	}
	m_ShaderID = CreateShader(vertex, fragment);
}

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

void Program::SetUniform1i(const std::string & name, const int value)
{
	GL(glUniform1i(GetUniformLocation(name), value));
}

void Program::SetUniform4f(const std::string & name, const glm::vec4 & vector)
{
	GL(glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w));
}

void Program::SetUniform3f(const std::string & name, const glm::vec3 & vector)
{
	GL(glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z));
}

void Program::SetUniformMat4f(const std::string & name, const glm::mat4 & matrix)
{
	GL(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
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
