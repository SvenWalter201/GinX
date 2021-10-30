#pragma once

#include "Core.h"

#include "Window.h"
#include "GinX/Layers/LayerStack.h"
#include "Events/Event.h"
#include "GinX/Window.h"
#include "GinX/Events/ApplicationEvent.h"

#include "GinX/ImGui/ImGuiLayer.h"
#include "GinX/Renderer/Shader.h"
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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
	private:
		static Application* s_Instance;
	};

	//to be defined in client
	Application* CreateApplication();

}

