#pragma once

#include "Core.h"

#include "Window.h"
#include "GinX/Core/LayerStack.h"
#include "Ginx/Events/Event.h"
#include "GinX/Core/Window.h"
#include "GinX/Events/ApplicationEvent.h"

#include "GinX/ImGui/ImGuiLayer.h"
#include "GinX/Renderer/Shader.h"
#include "GinX/Renderer/Buffer.h"
#include "GinX/Renderer/VertexArray.h"
#include "Ginx/Renderer/Camera.h"

#include "GinX/Core/Timestep.h"

namespace GinX {
	class GINX_API Application
	{
	public: 
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	//to be defined in client
	Application* CreateApplication();

}

