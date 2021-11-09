#pragma once

#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"

namespace GinX
{
	class Renderer2D
	{
	public:
		static void Init();
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		static void Flush();
		static void ShutDown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}
	