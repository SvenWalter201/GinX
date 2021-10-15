#pragma once

#ifdef GX_PLATFORM_WINDOWS
	#ifdef GX_BUILD_DLL
		#define GINX_API __declspec(dllexport)
	#else 
		#define GINX_API __declspec(dllimport)
	#endif
#else
	#error GinX only supports windows
#endif

#ifdef GX_DEBUG
	#define GX_ENABLE_ASSERTS
#endif

#ifdef GX_ENABLE_ASSERTS
	#define GX_ASSERT(x, ...) { if(!(x)) { GX_ERROR("Assertion Failes: {0}", __VA_ARGS__); __debugbreak(); }}
	#define GX_CORE_ASSERT(x, ...){if (!(x)){GX_CORE_ERROR("Assertion Failes: {0}", __VA_ARGS__);__debugbreak();}}
#else
	#define GX_ASSERT(x, ...)
	#define GX_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1<<x)

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
