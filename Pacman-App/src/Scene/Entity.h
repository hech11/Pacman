#pragma once

#include "Scene.h"

namespace Core
{
	class Entity
	{

		public :
			Entity() = default;
			Entity(EntityHandle handle, Scene* context)
				: m_Handle(handle), m_Context(context) { }

			template<typename T, typename... args>
			T& AddComponent(args&&... arg)
			{
				return m_Context->GetRegistry().AddComponent<T>(m_Handle, std::forward<args>(arg)...);
			}

			template<typename T>
			T& GetComponent()
			{
				return m_Context->GetRegistry().GetComponent<T>(m_Handle);
			}

			template<typename T>
			bool HasComponent()
			{
				return m_Context->GetRegistry().HasComponent<T>(m_Handle);
			}


		private :
			EntityHandle m_Handle;
			Scene* m_Context;
	};

}