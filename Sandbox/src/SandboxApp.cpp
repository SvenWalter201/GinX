#include <GinX.h>
#include"glm/glm.hpp"

class ExampleLayer : public GinX::Layer
{
public:
	ExampleLayer() :
		Layer("Example")
	{

	}

	void OnUpdate() override {
		if (GinX::Input::IsKeyPressed(GX_KEY_TAB))
			GX_TRACE("Tab key is pressed");
	}

	void OnEvent(GinX::Event& event) override {
		//GX_TRACE("{0}", event);
	}
};


class Sandbox : public GinX::Application {

public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new GinX::ImGuiLayer());
	}

	~Sandbox() {

	}
};

GinX::Application* GinX::CreateApplication() {
	return new Sandbox();
}