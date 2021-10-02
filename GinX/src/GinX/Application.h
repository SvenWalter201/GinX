#pragma once

#include "Core.h"

namespace GinX {
	class GINX_API Application
	{
	public: 
		Application();
		virtual ~Application();

		void Run();
	};

	//to be defined in client
	Application* CreateApplication();

}

