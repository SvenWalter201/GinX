#include "gxpch.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
namespace GinX
{

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader,
		const glm::mat4& transform)
	{
		shader->Bind();
		std::static_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		std::static_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::Flush()
	{

	}

}