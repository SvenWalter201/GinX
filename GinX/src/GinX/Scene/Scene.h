#pragma once

#include "../../vendor/EnTT/entt.hpp"

namespace GinX
{
	class Scene
	{
	public:
		Scene();
		~Scene();

	private:
		entt::registry m_Registry;
	};
}