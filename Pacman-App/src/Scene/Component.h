#pragma once


#include <glm/glm.hpp>

namespace Core
{
	struct Component
	{
		virtual ~Component() {}
	};


	struct TransformComponent : public Component
	{
		glm::mat4 Transform;

		TransformComponent() = default;
		TransformComponent(const glm::mat4& transform) : Transform(transform) {}
		TransformComponent(const TransformComponent& comp) : Transform(comp.Transform) {}

	};



	struct SpriteRenderingComponent : public Component
	{
		
		glm::uvec4 TexCoords = {0, 0, 0, 0};

		SpriteRenderingComponent() = default;
		SpriteRenderingComponent(const glm::uvec4& texCoords) : TexCoords(texCoords) {}
		SpriteRenderingComponent(const SpriteRenderingComponent& comp) : TexCoords(comp.TexCoords) {}

	};
}