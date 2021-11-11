#include "Sandbox2D.h"
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Platform/OpenGL/OpenGLShader.h"

template<typename Fn>
class Timer
{
public:
	Timer(const char* name, Fn&& func)
		: m_Name(name), m_Stopped(false), m_Func(func)
	{
		m_StartTime = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Stop() {
		m_Stopped = true;
		auto endTime = std::chrono::high_resolution_clock::now();
		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTime).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();

		float duration = (end - start) * 0.001f;

		m_Func({ m_Name, duration });
		//std::cout << m_Name << ": " << duration << "ms" << std::endl;
	}

private:
	std::chrono::time_point < std::chrono::steady_clock> m_StartTime;
	const char* m_Name;
	bool m_Stopped;
	Fn m_Func;
};

Sandbox2D::Sandbox2D() :
	Layer("Example"), m_CameraController(1270.0f / 720.0f), m_Scene(GinX::Scene())
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

	//GinX::Manager mng;
}

void Sandbox2D::OnAttach()
{

}

void Sandbox2D::OnDetach()
{

}

#define PROFILE_SCOPE(name) Timer t##__LINE__ (name, [&](ProfileResult result) { m_ProfileResults.push_back(result); })

void Sandbox2D::OnUpdate(GinX::TimeStep ts)
{
	float time = ts;

	PROFILE_SCOPE("Sandbox2D::OnUpdate");

	m_CameraController.OnUpdate(ts);

	GinX::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
	GinX::RenderCommand::Clear();

	GinX::Renderer2D::BeginScene(m_CameraController.GetCamera());

	glm::vec2 scale = { 0.01f, 0.01f };

	{
		PROFILE_SCOPE("Batch together Quads");
		for (uint32_t x = 0; x < 100; x++)
		{
			for (uint32_t y = 0; y < 100; y++)
			{
				float xPos = x * 0.012f - 0.51f;
				float yPos = y * 0.012f - 0.51f;
				GinX::Renderer2D::DrawQuad({ xPos, yPos }, scale, { 0.8f, 0.3f, 0.2f, 1.0f });
			}
		}
	}
	//GinX::Renderer2D::DrawQuad({ -0.5f, 0.0f }, { 0.3f, 0.2f }, { 0.3f, 0.8f, 0.2f, 1.0f });
	//GinX::Renderer2D::DrawQuad({ 0.0f, +0.5f }, { 0.8f, 0.9f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	{
		PROFILE_SCOPE("Submit to GPU and Draw");
		GinX::Renderer2D::EndScene();
	}
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

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("ColorA", glm::value_ptr(m_TriColorA));
	ImGui::ColorEdit3("ColorB", glm::value_ptr(m_TriColorB));

	for (auto& result : m_ProfileResults)
	{
		char label[50];
		strcpy(label, "%.3fms ");
		strcat(label, result.Name);
		ImGui::Text(label, result.Time);
	}

	m_ProfileResults.clear();

	ImGui::End();
}

void Sandbox2D::OnEvent(GinX::Event& event)
{
	m_CameraController.OnEvent(event);
}