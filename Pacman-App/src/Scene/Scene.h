#pragma once


#include "EntityRegistry.h"

namespace Core
{

	class Entity;
	class Scene
	{
		public :
			Scene();
			~Scene();

			void LoadLevel(const std::string& filepath);

			void OnUpdate(float ts = 0.0016f);

			Entity CreateEntity();

			EntityRegistry& GetRegistry() { return *m_Registry; }

		private :
			EntityRegistry* m_Registry;
	};
}