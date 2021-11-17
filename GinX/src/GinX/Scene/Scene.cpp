#include "gxpch.h"
#include "Scene.h"

#include <glm/glm.hpp>

#include "Entity.h"

namespace GinX
{

	Scene::Scene() : m_Registry(entt::registry())
	{
	/*
		struct SomeThirdComponent
		{
			float X = 0.0f;
		};

		struct QuadRendererComponent
		{
			glm::vec4 Color;
			glm::vec2 Scale;

			QuadRendererComponent() = default;
			QuadRendererComponent(const QuadRendererComponent&) = default;
			QuadRendererComponent(const glm::vec4& color, const glm::vec2& scale) 
				: Color(color), Scale(scale) {}
		};

		struct TransformComponent
		{
			glm::mat4 Transform;

			TransformComponent() = default;
			TransformComponent(const TransformComponent&) = default;
			TransformComponent(const glm::mat4& transform) : Transform(transform) {}

			operator glm::mat4&() { return Transform; }
			operator const glm::mat4&() const { return Transform; }
		};

		for (uint32_t i = 0; i < 1000; i++)
		{
			entt::entity entity = m_Registry.create();
			if (i % 3 == 0)
			{
				m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));
			}
			if (i % 2 == 0)
			{
				QuadRendererComponent c(glm::vec4(1.0f, 0.2f, 0.3f, 1.0f), glm::vec2(0.9f, 0.8f));
				m_Registry.emplace<QuadRendererComponent>(entity, c);
			}
			if (i % 5 == 0)
			{
				m_Registry.emplace<SomeThirdComponent>(entity);
			}

		}

		entt::entity entity = m_Registry.create();
		entt::entity entity2 = m_Registry.create();

		m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

		//TransformComponent& transform = m_Registry.get<TransformComponent>(entity);

		auto view = m_Registry.view<TransformComponent>();
		size_t size = view.size();
		GX_CORE_TRACE("{0} Components have Transform", size);

		auto group = m_Registry.group<TransformComponent>(entt::get<QuadRendererComponent, SomeThirdComponent>);
		size_t groupSize = group.size();
		GX_CORE_TRACE("{0} Components have Transform and QuadRenderer", groupSize);

		m_Registry.clear();
		*/
	}

	Scene::~Scene()
	{

	}

	GinX::Entity Scene::CreateEntity()
	{
		return Entity(m_Registry.create(), this);
	}

}