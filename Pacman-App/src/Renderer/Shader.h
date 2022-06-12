#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Core
{
	struct ShaderSourcePaths
	{
		std::string VertexShaderPath;
		std::string FragmentShaderPath;
	};
	class Shader
	{
		public:	
			Shader(const ShaderSourcePaths& filepaths);
			~Shader();


			void Bind();
			void Unbind();


			void SetUniform1i(const std::string& name, int value);
			void SetUniform4f(const std::string& name, const glm::vec4& values);
			void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

		private :
			std::string GetShaderSource(const std::string& path);
			uint32_t CreateShader(uint32_t type, std::string& source);

		private :
			uint32_t m_ShaderID;
			ShaderSourcePaths m_Filepaths;
	};

}
