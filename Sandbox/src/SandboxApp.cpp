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
		Layer("Example"), m_CameraController(1270.0f / 720.0f)
	{

		/*
		m_TriangleVA = GinX::VertexArray::Create();

		float triangleVertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			+0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};

		GinX::Ref<GinX::VertexBuffer> triangleVB;
		triangleVB = GinX::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices));

		triangleVB->SetLayout({
			{GinX::ShaderDataType::Float3, "a_Position"},
			{GinX::ShaderDataType::Float4, "a_Color"}
			});

		m_TriangleVA->AddVertexBuffer(triangleVB);

		unsigned int triangleIndizes[3] = { 0,1,2 };

		auto triangleIB = GinX::IndexBuffer::Create(triangleIndizes, std::size(triangleIndizes));
		m_TriangleVA->SetIndexBuffer(triangleIB);

		m_SquareVA = GinX::VertexArray::Create();

		float squareVertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			+0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			+0.5f, +0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f, +0.5f, 0.0f, 0.0f, 1.0f
		};

		auto squareVB = GinX::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

		squareVB->SetLayout({
			{GinX::ShaderDataType::Float3, "a_Position"},
			{GinX::ShaderDataType::Float2, "a_TexCoord"}
		});

		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndizes[6] = { 0,1,2,2,3,0 };

		auto squareIB = GinX::IndexBuffer::Create(squareIndizes, std::size(squareIndizes));
		m_SquareVA->SetIndexBuffer(squareIB);


		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		m_ShaderLibrary.Load("assets/shaders/FlatColor.glsl");

		m_Texture2D = GinX::Texture2D::Create("assets/textures/checkerboard.png");
		m_TextureLogo2D = GinX::Texture2D::Create("assets/textures/logo2.png");

		std::static_pointer_cast<GinX::OpenGLShader>(textureShader)->Bind();
		std::static_pointer_cast<GinX::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

		*/

		GinX::Renderer2D::Init();


	}

	void OnUpdate(GinX::TimeStep ts) override
	{
		float time = ts;

		m_CameraController.OnUpdate(ts);

		GinX::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
		GinX::RenderCommand::Clear();

		GinX::Renderer2D::BeginScene(m_CameraController.GetCamera());

		GinX::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.3f, 0.2f, 1.0f });
		GinX::Renderer2D::DrawQuad({ -0.5f, 0.0f }, { 0.3f, 0.2f }, { 0.3f, 0.8f, 0.2f, 1.0f });
		GinX::Renderer2D::DrawQuad({ 0.0f, +0.5f }, { 0.8f, 0.9f }, { 0.2f, 0.3f, 0.8f, 1.0f });

		GinX::Renderer2D::EndScene();
		/*

		GinX::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f));
		int res = 50;
		glm::vec4 red(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blue(0.3f, 0.2f, 0.8f, 1.0f);

		//std::static_pointer_cast<GinX::OpenGLShader>(m_FlatShader)->Bind();

		glm::mat4 squareTransform = glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, 0.0f });

		//std::static_pointer_cast<GinX::OpenGLShader>(m_FlatShader)->UploadUniformFloat3("u_Color",{0.3f, 0.8f, 0.2f});

		auto flatColorShader = m_ShaderLibrary.Get("FlatColor");


		for (size_t i = 0, x = 0, y = 0; i < res * res; i++, x++)
		{
			if (x == res)
			{
				x = 0;
				y += 1;
			}

			if (x % 2 == y % 2)
				std::static_pointer_cast<GinX::OpenGLShader>(flatColorShader)->UploadUniformFloat3("u_Color", m_TriColorA);
			else
				std::static_pointer_cast<GinX::OpenGLShader>(flatColorShader)->UploadUniformFloat3("u_Color", m_TriColorB);

			glm::vec3 pos(x * 0.06f - 0.75f, y * 0.06f - 0.75f, 0.0f);
			glm::mat4 t = glm::translate(glm::mat4(1.0f), pos) * scale;
			GinX::Renderer::Submit(flatColorShader, m_TriangleVA,  t);
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture2D->Bind();
		GinX::Renderer::Submit(textureShader, m_SquareVA, squareTransform);


		m_TextureLogo2D->Bind();
		GinX::Renderer::Submit(textureShader, m_SquareVA, squareTransform);

		GinX::Renderer::EndScene();

		GinX::Renderer::Flush();

		*/
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
		m_CameraController.OnEvent(event);
	}

private:

	GinX::ShaderLibrary m_ShaderLibrary;
	GinX::Ref<GinX::VertexArray> m_TriangleVA;
	GinX::CameraController m_CameraController;
	GinX::Ref<GinX::VertexArray> m_SquareVA;
	GinX::Ref<GinX::Texture2D> m_Texture2D;
	GinX::Ref<GinX::Texture2D> m_TextureLogo2D;
	//GinX::OrthographicCamera m_Camera;
	//glm::vec3 m_cameraPosition;
	//float m_CameraSpeed = 6.0f;
	//float m_TriangleSpeed = 1.0f;
	//float m_CameraRotation = 0.0f;
	//float m_CameraRotationSpeed = 50.0f;

	//glm::vec3 m_TrianglePosition;
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