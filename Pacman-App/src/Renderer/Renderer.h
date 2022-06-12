#pragma once

#include <glm/glm.hpp>
namespace Core
{


	class Renderer
	{

		public :
			static void Init();
			static void Shutdown();


			static void Begin(const glm::mat4& viewProjection);
			static void SumbitSprite(const glm::mat4 transform, const glm::u32vec4& texCoords);
			static void End();
	};
}