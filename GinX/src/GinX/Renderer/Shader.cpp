#include "gxpch.h"
#include "Shader.h"
#include "Renderer.h"
#include <glad/glad.h>
#include "Platform/OpenGL/OpenGLShader.h"
namespace GinX
{
	GinX::Shader* Shader::Create(const std::string& filePath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: GX_CORE_ASSERT(false, "RenderAPI::NONE is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLShader(filePath);
		}

		GX_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: GX_CORE_ASSERT(false, "RenderAPI::NONE is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		GX_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}



}