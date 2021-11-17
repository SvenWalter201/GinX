#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace GinX
{
	namespace Component
	{
		struct MoveState
		{
			MoveState() = default;
			MoveState(const MoveState&) = default;
			MoveState(float movementSpeed) 
				: MovementSpeed(movementSpeed), XFlipped(false), YFlipped(false) {}
			bool XFlipped = false;
			bool YFlipped = false;
			float MovementSpeed = 1.0f;
		};

		struct SpriteRenderer
		{
			SpriteRenderer() = default;
			SpriteRenderer(const SpriteRenderer&) = default;

			SpriteRenderer(const glm::vec4& color) : Color(color) {}
			glm::vec4 Color;
		};

		struct TransformComponent
		{
			glm::vec3 Position;
			glm::vec3 Scale;
			glm::mat4 Transform;

			TransformComponent() = default;
			TransformComponent(const TransformComponent&) = default;
			TransformComponent(const glm::vec3& position, const glm::vec3& scale) : Position(position),
				Scale(scale)
			{
				ConstructMatrix();
			}
			//TransformComponent(const glm::mat4& transform) : Transform(transform) {}

			void ConstructMatrix()
			{
				Transform = glm::translate(glm::mat4(1.0f), Position) * glm::scale(glm::mat4(1.0f), Scale);
			}

			//operator glm::mat4& () { return Transform; }
			//operator const glm::mat4& () const { return Transform; }
		};
	}
	
}