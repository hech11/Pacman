#include "Shader.h"

#include <GL/glew.h>
#include <sstream>
#include <fstream>

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
namespace Core
{

	Shader::Shader(const ShaderSourcePaths& filepaths)
		: m_Filepaths(filepaths)
	{


		m_ShaderID = glCreateProgram();
		glUseProgram(m_ShaderID);

		std::string vertexShaderSource = GetShaderSource(filepaths.VertexShaderPath);
		std::string fragmentShaderSource = GetShaderSource(filepaths.FragmentShaderPath);

		uint32_t vs = CreateShader(GL_VERTEX_SHADER, vertexShaderSource);
		uint32_t fs = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

		glAttachShader(m_ShaderID, vs);
		glAttachShader(m_ShaderID, fs);

		glValidateProgram(m_ShaderID);
		glLinkProgram(m_ShaderID);

		glDeleteShader(vs);
		glDeleteShader(fs);
		glUseProgram(0);


	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ShaderID);
	}

	void Shader::Bind()
	{
		glUseProgram(m_ShaderID);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}

	void Shader::SetUniform1i(const std::string& name, int value)
	{
		uint32_t location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniform1i(location, value);
	}

	void Shader::SetUniform4f(const std::string& name, const glm::vec4& values)
	{
		glUniform4f(glGetUniformLocation(m_ShaderID, name.c_str()), values.x, values.y, values.z, values.w);
	}

	void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
	{

		glUniformMatrix4fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));

	}

	std::string Shader::GetShaderSource(const std::string& path)
	{
		std::fstream file(path);
		if (!file.is_open())
		{
			__debugbreak();
		}

		std::string line;
		std::stringstream source;
		while (getline(file, line))
		{
			source << line << "\n";
		}

		return source.str();

	}

	uint32_t Shader::CreateShader(uint32_t type, std::string& source)
	{
		uint32_t shader = glCreateShader(type);

		int length;
		glGetShaderiv(shader, GL_SHADER_SOURCE_LENGTH, &length);
		const char* src = source.c_str();


		glShaderSource(shader, 1, &src, &length);
		glCompileShader(shader);

		int validation;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &validation);

		if (!validation)
		{

			int logLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

			char* msg = (char*)alloca(logLength);


			glGetShaderInfoLog(shader, logLength, &logLength, msg);
			std::cout << "Shader error!\t [" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "]: " << msg << "\n";
			__debugbreak();
		}

		return shader;
	}

}