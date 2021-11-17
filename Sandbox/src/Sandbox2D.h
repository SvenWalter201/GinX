#pragma once

#include <GinX.h>

class Sandbox2D : public GinX::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(GinX::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(GinX::Event& event) override;

private:

	GinX::Scene m_Scene;
	GinX::ShaderLibrary m_ShaderLibrary;
	GinX::Ref<GinX::VertexArray> m_TriangleVA;
	GinX::CameraController m_CameraController;
	GinX::Ref<GinX::VertexArray> m_SquareVA;
	GinX::Ref<GinX::Texture2D> m_Texture2D;
	GinX::Ref<GinX::Texture2D> m_TextureLogo2D;

	glm::vec3 m_TriColorA = { 0.8f, 0.2f, 0.3f };
	glm::vec3 m_TriColorB = { 0.3f, 0.2f, 0.8f };

	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;
	std::vector<GinX::System*> m_Systems;
};
