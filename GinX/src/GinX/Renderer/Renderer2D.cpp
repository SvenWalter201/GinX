#include "gxpch.h"
#include "Renderer2D.h"
#include "GinX/Renderer/Buffer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/matrix_transform.hpp>

namespace GinX
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
	};

	struct Renderer2DData
	{
		const uint32_t MAX_QUADS = 100000;
		const uint32_t MAX_VERTICES = MAX_QUADS * 4;
		const uint32_t MAX_INDICES = MAX_QUADS * 6;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		
		QuadVertex* QuadVertexBasePtr = nullptr;
		QuadVertex* QuadVertexEndPtr = nullptr;

		uint32_t QuadCount = 0;

		glm::vec4 QuadVertexPositions[4];
	};

	static Renderer2DData s_Data;

	Renderer2D::SceneData* Renderer2D::m_SceneData = new Renderer2D::SceneData;

	void Renderer2D::Init()
	{
		s_Data.QuadVertexArray = VertexArray::Create();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MAX_VERTICES *sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->SetLayout({
			{ShaderDataType::Float3, "Position"},
			{ShaderDataType::Float4, "Color"},
			{ShaderDataType::Float2, "TexCoord"}
			});

		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBasePtr = new QuadVertex[s_Data.MAX_VERTICES];

		uint32_t* quadIndizes = new uint32_t[s_Data.MAX_INDICES];

		for (uint32_t i = 0, vertexIndex = 0; i < s_Data.MAX_INDICES; vertexIndex+=4)
		{
			quadIndizes[i++] = vertexIndex;
			quadIndizes[i++] = vertexIndex + 1;
			quadIndizes[i++] = vertexIndex + 2;
			quadIndizes[i++] = vertexIndex + 2;
			quadIndizes[i++] = vertexIndex + 3;
			quadIndizes[i++] = vertexIndex;
		}

		Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(quadIndizes, s_Data.MAX_INDICES);
		s_Data.QuadVertexArray->SetIndexBuffer(indexBuffer);

		delete[] quadIndizes;

		s_Data.QuadVertexPositions[0] = glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
		s_Data.QuadVertexPositions[1] = glm::vec4( 0.5f, -0.5f, 0.0f, 1.0f);
		s_Data.QuadVertexPositions[2] = glm::vec4( 0.5f,  0.5f, 0.0f, 1.0f);
		s_Data.QuadVertexPositions[3] = glm::vec4(-0.5f,  0.5f, 0.0f, 1.0f);


		s_Data.TextureShader = Shader::Create("assets/shaders/Texture2D.glsl");

	}

	void Renderer2D::OnWindowResize(uint32_t width, uint32_t height)
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f }) *
			glm::scale(glm::mat4(1.0f), {size.x, size.y, 0.0f
	});

		DrawQuad(transform, color);
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		constexpr uint32_t quadVertexCount = 4;
		constexpr glm::vec2 textureCoords[] = { {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f} };
		for (uint32_t i = 0; i < quadVertexCount; i++)
		{
			s_Data.QuadVertexEndPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexEndPtr->Color = color;
			s_Data.QuadVertexEndPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexEndPtr++;
		}

		s_Data.QuadCount++;
	}

	void Renderer2D::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();

		s_Data.QuadCount = 0;
		s_Data.QuadVertexEndPtr = s_Data.QuadVertexBasePtr;
	}

	void Renderer2D::EndScene()
	{
		Flush();
	}

	void Renderer2D::Flush()
	{
		if (s_Data.QuadCount == 0)
			return;

		uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexEndPtr - (uint8_t*)s_Data.QuadVertexBasePtr);
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBasePtr, dataSize);


		s_Data.TextureShader->Bind();
		std::static_pointer_cast<OpenGLShader>(s_Data.TextureShader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadCount * 6);
	}

	void Renderer2D::ShutDown()
	{
		delete[] s_Data.QuadVertexBasePtr;
	}
}