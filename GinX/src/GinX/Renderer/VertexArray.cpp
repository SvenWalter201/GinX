#include "gxpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace GinX
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: GX_CORE_ASSERT(false, "RenderAPI::NONE is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
		}

		GX_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}