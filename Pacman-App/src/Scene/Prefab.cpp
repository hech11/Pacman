#include "Prefab.h"


namespace Core
{

	Core::Entity Prefab::GetBlockPrefab(Scene* context)
	{
		
		Entity e = context->CreateEntity();
		e.AddComponent<SpriteRenderingComponent>().TexCoords = { 0, 16, 17, 17 };
		return e;
	}

	Core::Entity Prefab::GetPacmanPrefab(Scene* context)
	{
		Entity e = context->CreateEntity();
		e.AddComponent<SpriteRenderingComponent>().TexCoords = { 0, 0, 16, 16 };
		return e;
	}

}