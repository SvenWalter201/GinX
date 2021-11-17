#pragma once

#include "System.h"

namespace GinX
{
	class MoveRandomSystem : public System
	{
	public:
		MoveRandomSystem(Scene* scene);
		~MoveRandomSystem();
		virtual void OnUpdate(TimeStep ts) override;
	};

	class RenderingSystem : public System
	{
	public:
		RenderingSystem(Scene* scene);
		~RenderingSystem();
		virtual void OnUpdate(TimeStep ts) override;
	};
}