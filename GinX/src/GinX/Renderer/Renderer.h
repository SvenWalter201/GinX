#pragma once

#include "RenderCommand.h"

namespace GinX
{

	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
		static void Flush();

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	};
}