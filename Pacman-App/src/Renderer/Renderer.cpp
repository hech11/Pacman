#include "Renderer.h"

#include <memory>
#include "Shader.h"
#include "Texture.h"

#include <gl/glew.h>
#include <array>

namespace Core
{

	struct VertexData
	{
		glm::vec2 Position;
		glm::vec2 TexCoord;
		uint32_t Color;
	};

	struct RendererData
	{
		static const uint32_t MAX_SPRITES = 10000;
		static const uint32_t MAX_VERTICES = MAX_SPRITES * 4;
		static const uint32_t MAX_INDICES = MAX_SPRITES * 6;

		uint32_t VAO, VBO, IBO;
		std::shared_ptr<Shader> Shader;
		std::shared_ptr<Texture> Texture;

		uint32_t IndexCount = 0;
		VertexData* VertexPtrBase = nullptr;
		VertexData* VertexPtrData = nullptr;

		std::array<glm::vec4, 4> SpritePivots;
	} ;

	static RendererData* s_Data = nullptr;
	void Renderer::Init()
	{
		s_Data = new RendererData;
		s_Data->VertexPtrBase = new VertexData[s_Data->MAX_VERTICES];

		auto& vao = s_Data->VAO;
		auto& vbo = s_Data->VBO;
		auto& ibo = s_Data->IBO;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);


		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, s_Data->MAX_VERTICES*sizeof(VertexData), nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)offsetof(VertexData, VertexData::Position));


		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)offsetof(VertexData, VertexData::TexCoord));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, 5 * sizeof(uint32_t), (const void*)offsetof(VertexData, VertexData::Color));

		uint32_t* indicies = new uint32_t[s_Data->MAX_INDICES];
		int offset = 0;
		for (int i = 0; i < s_Data->MAX_INDICES; i+=6)
		{
			indicies[i] = offset + 0;
			indicies[i+1] = offset + 1;
			indicies[i+2] = offset + 2;
			indicies[i+3] = offset + 2;
			indicies[i+4] = offset + 3;
			indicies[i+5] = offset + 0;
			offset += 4;
		}


		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, s_Data->MAX_INDICES, indicies, GL_STATIC_DRAW);


		ShaderSourcePaths paths;
		paths.VertexShaderPath = "assets/shaders/test.vert";
		paths.FragmentShaderPath = "assets/shaders/test.frag";

		s_Data->Shader = std::make_shared<Shader>(paths);
		s_Data->Shader->Bind();


		s_Data->Texture = std::make_shared<Texture>("assets/textures/spritesheet.png");
		s_Data->Texture->Bind();

		s_Data->Shader->SetUniform1i("u_Texture", 0);

		s_Data->SpritePivots[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data->SpritePivots[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
		s_Data->SpritePivots[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
		s_Data->SpritePivots[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

	}

	void Renderer::Shutdown()
	{
		glDeleteBuffers(1, &s_Data->VBO);
		glDeleteBuffers(1, &s_Data->IBO);
		glDeleteVertexArrays(1, &s_Data->VAO);

		delete s_Data;
	}

	void Renderer::Begin(const glm::mat4& viewProjection)
	{
		s_Data->VertexPtrData = s_Data->VertexPtrBase;
		s_Data->IndexCount = 0;

		s_Data->Shader->Bind();
		s_Data->Shader->SetUniformMat4f("u_ViewProj", viewProjection);


	}


	void Renderer::SumbitSprite(const glm::mat4 transform, const glm::u32vec4& texCoords)
	{

		float xOffset = (float)texCoords.x / s_Data->Texture->GetWidth();
		float yOffset = (float)texCoords.y / s_Data->Texture->GetHeight();

		float xSize = (float)texCoords.z / s_Data->Texture->GetWidth();
		float ySize = (float)texCoords.w / s_Data->Texture->GetHeight();



		std::array<glm::vec2, 4> texCoord;
		texCoord[0] = {xOffset, 1.0f - (yOffset + ySize)};
		texCoord[1] = {xOffset + xSize, 1.0f - (yOffset + ySize)};
		texCoord[2] = {xOffset + xSize, 1.0f - yOffset};
		texCoord[3] = {xOffset, 1.0f -yOffset};

		for (int i = 0; i < 4; i++)
		{
			s_Data->VertexPtrData->Position = transform * s_Data->SpritePivots[i];
			s_Data->VertexPtrData->TexCoord = texCoord[i];
			s_Data->VertexPtrData->Color = 0xffffffff;
			s_Data->VertexPtrData++;
		}

		s_Data->IndexCount += 6;
	}

	void Renderer::End()
	{
		uint32_t size = (uint8_t*)s_Data->VertexPtrData - (uint8_t*)s_Data->VertexPtrBase;
		if (size)
		{
			s_Data->Shader->Bind();
			glBindVertexArray(s_Data->VAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data->IBO);
			glBindBuffer(GL_ARRAY_BUFFER, s_Data->VBO);

			glBufferSubData(GL_ARRAY_BUFFER, 0, size, s_Data->VertexPtrBase);
			glDrawElements(GL_TRIANGLES, s_Data->IndexCount, GL_UNSIGNED_INT, nullptr);

			
		}
	}

}