#pragma once

#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL
		#define GINX_API __declspec(dllexport)
	#else 
		#define GINX_API __declspec(dllimport)
	#endif
#else
	#error GinX only supports windows
#endif