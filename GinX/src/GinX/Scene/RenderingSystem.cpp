#include "gxpch.h"
#include "RenderingSystem.h"
#include "Components.h"
#include "GinX/Renderer/Renderer2D.h"
#include <glm/gtc/matrix_transform.hpp>

namespace GinX
{
	using namespace Component;

	MoveRandomSystem::MoveRandomSystem(Scene* scene)
		: System("MoveRandomSystem", scene)
	{
		
	}

	MoveRandomSystem::~MoveRandomSystem()
	{

	}

	void MoveRandomSystem::OnUpdate(TimeStep ts)
	{
		//auto group = m_Scene->GetGroup<TransformComponent, SpriteRenderer>();

		const float bounds = 1.0f;

		auto group = m_Scene->GetGroup<TransformComponent, SpriteRenderer, MoveState>();
		
		for (auto entity : group)
		{
			auto& transform = group.get<TransformComponent>(entity);
			auto& state = group.get<MoveState>(entity);
			
			int multiplierX = state.XFlipped ? -1 : 1;
			int multiplierY = state.YFlipped ? -1 : 1;

			glm::vec3 movementDir(
				multiplierX * ts * state.MovementSpeed, 
				multiplierY * ts * state.MovementSpeed, 
				0.0f);

			transform.Position += movementDir;
			
			//if character runs out of bounds, flip direction
			if (transform.Position.x > bounds)
				state.XFlipped = true;
			if (transform.Position.x < -bounds)
				state.XFlipped = false;
			if (transform.Position.y > bounds)
				state.YFlipped = true;
			if (transform.Position.y < -bounds)
				state.YFlipped = false;
			
			transform.ConstructMatrix();
			
		}
		
		//GX_CORE_TRACE("Updating {0} Entities for Rendering", group.size());
	
	}

	RenderingSystem::RenderingSystem(Scene* scene)
		: System("RenderingSystem", scene)
	{

	}

	RenderingSystem::~RenderingSystem()
	{

	}

	void RenderingSystem::OnUpdate(TimeStep ts)
	{
		
		auto group = m_Scene->GetGroup<TransformComponent, SpriteRenderer>();

		for (auto entity : group)
		{
			auto& transform = group.get<TransformComponent>(entity);
			auto& spriteRenderer = group.get<SpriteRenderer>(entity);
			Renderer2D::DrawQuad(transform.Transform, spriteRenderer.Color);
		}
		
	}



}