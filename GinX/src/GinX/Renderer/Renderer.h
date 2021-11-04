#pragma once

#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"

namespace GinX
{

	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader,
			const glm::mat4& transform = glm::mat4(1.0f));
		static void Flush();

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}