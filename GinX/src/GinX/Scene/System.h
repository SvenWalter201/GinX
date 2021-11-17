#pragma once

#include "Scene.h"
#include "entt.hpp"
#include "GinX/Core/Timestep.h"
namespace GinX
{
	class System
	{
	public:
		System(const char* name, Scene* scene);
		virtual ~System() {}
		virtual void OnUpdate(TimeStep ts) = 0;	

		inline const char* GetName() { return m_Name; }

	protected:
		Scene* m_Scene;
		const char* m_Name;
	};
}