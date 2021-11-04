#include <GinX.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public GinX::Layer
{
public:
	ExampleLayer() :
		Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_cameraPosition(0.0f), m_TrianglePosition(0.0f,0.0f,0.0f)
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
			uniform mat4 u_Transform;

			out vec3 v_Position;

			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position,1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location=0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatShader.reset(GinX::Shader::Create(vertexSrc, fragmentSrc));
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

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f));
		int res = 50;
		glm::vec4 red(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blue(0.3f, 0.2f, 0.8f, 1.0f);

		std::static_pointer_cast<GinX::OpenGLShader>(m_FlatShader)->Bind();


		for (size_t i = 0, x = 0, y = 0; i < res * res; i++, x++)
		{
			if (x == res)
			{
				x = 0;
				y += 1;
			}

			if (x % 2 == y % 2)
				std::static_pointer_cast<GinX::OpenGLShader>(m_FlatShader)->UploadUniformFloat3("u_Color", m_TriColorA);
			else 
				std::static_pointer_cast<GinX::OpenGLShader>(m_FlatShader)->UploadUniformFloat3("u_Color", m_TriColorB);

			glm::vec3 pos(x * 0.06f - 0.75f, y * 0.06f - 0.75f, 0.0f);
			glm::mat4 t = glm::translate(glm::mat4(1.0f), pos) * scale;
			GinX::Renderer::Submit(m_VertexArray, m_FlatShader, t);
		}


		GinX::Renderer::EndScene();

		GinX::Renderer::Flush();
	}

	virtual void OnImGuiRender() override 
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("ColorA", glm::value_ptr(m_TriColorA));
		ImGui::ColorEdit3("ColorB", glm::value_ptr(m_TriColorB));
		ImGui::End();
	}

	void OnEvent(GinX::Event& event) override 
	{
	}

private:

	std::shared_ptr<GinX::Shader> m_FlatShader;
	std::shared_ptr<GinX::VertexArray> m_VertexArray;

	std::shared_ptr<GinX::VertexArray> m_SquareVA;

	GinX::OrthographicCamera m_Camera;
	glm::vec3 m_cameraPosition;
	float m_CameraSpeed = 6.0f;
	float m_TriangleSpeed = 1.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 50.0f;

	glm::vec3 m_TrianglePosition;
	glm::vec3 m_TriColorA = {0.8f, 0.2f, 0.3f};
	glm::vec3 m_TriColorB = {0.3f, 0.2f, 0.8f};
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