#include <GinX.h>
#include "GinX/Core/EntryPoint.h"
#include "Sandbox2D.h"

class Sandbox : public GinX::Application 
{

public:
	Sandbox() 
	{
		PushLayer(new Sandbox2D());
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