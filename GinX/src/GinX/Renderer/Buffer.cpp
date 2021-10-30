#include "gxpch.h"
#include "Buffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer.h"

namespace GinX
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) 
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: GX_CORE_ASSERT(false, "RenderAPI::NONE is currently not supported"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		GX_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: GX_CORE_ASSERT(false, "RenderAPI::NONE is currently not supported"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
		}

		GX_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}