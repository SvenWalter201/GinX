#include "gxpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include "Glad/Glad.h"

namespace GinX
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_windowHandle(windowHandle)
	{
		GX_CORE_ASSERT(windowHandle, "WindowHandle is null");
	}

	void OpenGLContext::Init() 
	{
		glfwMakeContextCurrent(m_windowHandle);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GX_CORE_ASSERT(status, "Failed to initialize GLAD");

		GX_CORE_INFO("OpenGL Renderer");
		GX_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		GX_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		GX_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() 
	{
		glfwSwapBuffers(m_windowHandle);

	}

}