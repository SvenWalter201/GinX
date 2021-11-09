#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace GinX {

	class GINX_API Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;

	};
}

//Core log macros
#define GX_CORE_TRACE(...) ::GinX::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GX_CORE_INFO(...)  ::GinX::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GX_CORE_WARN(...)  ::GinX::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GX_CORE_ERROR(...) ::GinX::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GX_CORE_FATAL(...) ::GinX::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log macros
#define GX_TRACE(...) ::GinX::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GX_INFO(...)  ::GinX::Log::GetClientLogger()->info(__VA_ARGS__)
#define GX_WARN(...)  ::GinX::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GX_ERROR(...) ::GinX::Log::GetClientLogger()->error(__VA_ARGS__)
#define GX_FATAL(...) ::GinX::Log::GetClientLogger()->fatal(__VA_ARGS__)

