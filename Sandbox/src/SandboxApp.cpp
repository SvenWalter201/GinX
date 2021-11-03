#include <GinX.h>
#include"glm/glm.hpp"
#include "imgui/imgui.h"

class ExampleLayer : public GinX::Layer
{
public:
	ExampleLayer() :
		Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_cameraPosition(0.0f)
	{
		m_VertexArray.reset(GinX::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			+0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};

		std::shared_ptr<GinX::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(GinX::VertexBuffer::Create(vertices, sizeof(vertices)));

		vertexBuffer->SetLayout({
			{GinX::ShaderDataType::Float3, "a_Position"},
			{GinX::ShaderDataType::Float4, "a_Color"}
			});

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0,1,2 };

		std::shared_ptr<GinX::IndexBuffer> indexBuffer;
		indexBuffer.reset(GinX::IndexBuffer::Create(indices, std::size(indices)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(GinX::VertexArray::Create());

		std::string vertexSrc = R"(
			#version 330 core

			layout(location=0) in vec3 a_Position;
			layout(location=1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position,1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location=0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(new GinX::Shader(vertexSrc, fragmentSrc));
	}

	void OnUpdate(GinX::TimeStep ts) override 
	{
		float time = ts;

		GX_TRACE("DeltaTime {0} [{1}]:", ts.GetSeconds(), ts.GetMiliseconds());
		if (GinX::Input::IsKeyPressed(GX_KEY_LEFT))
			m_cameraPosition.x -= m_CameraSpeed * time;
		else if (GinX::Input::IsKeyPressed(GX_KEY_RIGHT))
			m_cameraPosition.x += m_CameraSpeed * time;

		if (GinX::Input::IsKeyPressed(GX_KEY_DOWN))
			m_cameraPosition.y -= m_CameraSpeed * time;
		else if (GinX::Input::IsKeyPressed(GX_KEY_UP))
			m_cameraPosition.y += m_CameraSpeed * time;

		if (GinX::Input::IsKeyPressed(GX_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * time;
		else if (GinX::Input::IsKeyPressed(GX_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * time;

		m_Camera.SetPosition(m_cameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		GinX::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
		GinX::RenderCommand::Clear();

		GinX::Renderer::BeginScene(m_Camera);

		GinX::Renderer::Submit(m_VertexArray, m_Shader);

		GinX::Renderer::EndScene();

		GinX::Renderer::Flush();
	}

	virtual void OnImGuiRender() override 
	{
		
	}

	void OnEvent(GinX::Event& event) override 
	{
	}

private:

	std::shared_ptr<GinX::Shader> m_Shader;
	std::shared_ptr<GinX::VertexArray> m_VertexArray;

	std::shared_ptr<GinX::VertexArray> m_SquareVA;

	GinX::OrthographicCamera m_Camera;
	glm::vec3 m_cameraPosition;
	float m_CameraSpeed = 6.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 50.0f;
};


class Sandbox : public GinX::Application 
{

public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
		//PushOverlay(new GinX::ImGuiLayer());
	}

	~Sandbox() 
	{

	}
};

GinX::Application* GinX::CreateApplication() 
{
	return new Sandbox();
}