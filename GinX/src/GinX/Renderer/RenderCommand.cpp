#include "gxpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace GinX
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}