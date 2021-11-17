#pragma once

#include "Scene.h"
#include "entt.hpp"
namespace GinX
{
	
	class Entity
	{
	public:
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename Component, typename... Args>
		Component& AddComponent(Args&&... args) 
		{
			return m_Scene->m_Registry.emplace<Component>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename Component>
		Component& GetComponent() 
		{
			return m_Scene->m_Registry.get<Component>(m_EntityHandle);
		}

		template<typename Component>
		bool HasComponent()
		{
			return m_Scene->m_Registry.all_of<Component>(m_EntityHandle);
		}

		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="Component"></typeparam>
		/// <returns>If the component to remove was present</returns>
		template<typename Component>
		bool RemoveComponent() 
		{
			size_t num = m_Scene->m_Registry.remove<Component>(m_EntityHandle);
			return num != 0;
		}

	private:
		entt::entity m_EntityHandle;
		Scene* m_Scene;
	};
	
}