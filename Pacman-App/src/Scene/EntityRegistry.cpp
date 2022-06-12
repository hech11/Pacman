#include "EntityRegistry.h"
#include "../Core/Random.h"


namespace Core
{

	Core::EntityHandle EntityRegistry::CreateEntity()
	{
		
		EntityHandle handle = Random::Generate64();
		m_Registry[handle].clear();
		return handle;
	}

}