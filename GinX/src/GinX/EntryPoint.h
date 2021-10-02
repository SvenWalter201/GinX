#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern GinX::Application* GinX::CreateApplication();

int main(int argc, char** argv)
{
	auto app = GinX::CreateApplication();
	app->Run();
	delete app;
}

#endif

