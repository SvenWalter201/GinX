#pragma once

#include "entt.hpp"

namespace GinX
{
	class Entity;

	class System;

	class Scene
	{
	public:
		Scene();
		~Scene();

		template<typename Component>
		auto GetView()
		{
			auto view = m_Registry.view<Component>();
			return view;
		}

		template<typename Component1, typename Component2>
		auto GetGroup() 
		{
			auto group = m_Registry.group<Component1>(entt::get<Component2>);
			return group;
		}

		template<typename Component1, typename Component2, typename Component3>
		auto GetGroup()
		{
			auto group = m_Registry.group<Component1>(entt::get<Component2, Component3>);
			return group;
		}

		Entity CreateEntity();

	private:
		entt::registry m_Registry;
		friend class Entity;
		friend class System;
	};
}