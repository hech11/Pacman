#pragma once

#include <unordered_map>
#include <memory>

#include "Component.h"
#include <functional>

namespace Core
{

	using EntityHandle = int64_t;
	class EntityRegistry
	{
		public :
			EntityHandle CreateEntity();


			template<typename T, typename... args>
			T& AddComponent(EntityHandle handle, args&&... arg)
			{
				if (m_Registry.find(handle) == m_Registry.end())
				{
					__debugbreak();
				}
				// TODO: Check if already has component.....


				std::shared_ptr<T> result = std::make_shared<T>(std::forward<args>(arg)...);
				m_Registry[handle].push_back(result);

				return *result.get();
			}

			template<typename T, typename... args>
			T& GetComponent(EntityHandle handle)
			{
				if (m_Registry.find(handle) == m_Registry.end())
				{
					__debugbreak();
				}
				T* result = nullptr;
				int typeToCompare = typeid(T).hash_code();
				for (auto& comp : m_Registry[handle])
				{
					result = static_cast<T*>(comp.get());
					int typeInfo = typeid(*result).hash_code();
					if (typeInfo == typeToCompare)
					{
						return *result;
					}
				}

				__debugbreak();
				return *result;
			}

			template<typename T>
			bool HasComponent(EntityHandle handle)
			{
				if (m_Registry.size())
				{
					if (m_Registry.find(handle) == m_Registry.end())
					{
						__debugbreak();
					}

					T* result = nullptr;
					int typeToCompare = typeid(T).hash_code();
					for (auto& comp : m_Registry[handle])
					{
						result = static_cast<T*>(comp.get());
						int typeInfo = typeid(*result).hash_code();
						if (typeInfo == typeToCompare)
						{
							return true;
						}
					}
				}

				return false;
			}


			template<typename T>
			void ForEach(const std::function<void(EntityHandle handle, T& comp)>& func)
			{
				for (auto& entry : m_Registry)
				{
					if (HasComponent<T>(entry.first))
					{
						auto& comp = GetComponent<T>(entry.first);
						func(entry.first, comp);
					}
				}
			}

		private :
			std::unordered_map < EntityHandle, std::vector<std::shared_ptr<Component>>> m_Registry;
	};

}