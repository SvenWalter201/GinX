#pragma once

#ifdef GX_PLATFORM_WINDOWS

extern GinX::Application* GinX::CreateApplication();

int main(int argc, char** argv)
{
	GinX::Log::Init();
	GX_INFO("Initialized Log");
	auto app = GinX::CreateApplication();
	app->Run();
	delete app;
}

#endif

