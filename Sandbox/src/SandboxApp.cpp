#include <GinX.h>

class Sandbox : public GinX::Application {

public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

GinX::Application* GinX::CreateApplication() {
	return new Sandbox();
}