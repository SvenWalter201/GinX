#include "gxpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>
#include <gl/GLU.h>

namespace GinX
{

	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
		/*
		gl
		float aspectRatio = 1280.0f / 720.0f;
		if (width >= height)
		{
			gluOrtho2D(-aspectRatio, aspectRatio, 0.0f, 1.0f);
		}
		else
		{
			gluOrtho2D(-1.0f, 1.0f, 0.0f, 1.0f / aspectRatio);
		}
		*/
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count)
	{
		count = count ? count : vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}