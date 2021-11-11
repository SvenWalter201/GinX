workspace "GinX"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "GinX/vendor/GLFW/include"
IncludeDir["Glad"] = "GinX/vendor/Glad/include"
IncludeDir["ImGui"] = "GinX/vendor/imgui"
IncludeDir["glm"] = "GinX/vendor/glm"
IncludeDir["stb_image"] = "GinX/vendor/stb_image"
IncludeDir["EnTT"] = "GinX/vendor/EnTT"

group "Dependencies"
	include "GinX/vendor/GLFW"
	include "GinX/vendor/Glad"
	include "GinX/vendor/imgui"
group ""


project "GinX"
	location "GinX"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "gxpch.h"
	pchsource "GinX/src/gxpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/EnTT/entt.hpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.EnTT}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"GX_PLATFORM_WINDOWS",
			"GX_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "GX_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GX_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GX_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"GinX/vendor/spdlog/include",
		"GinX/src",
		"GinX/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.EnTT}"
	}

	links
	{
		"GinX"
	}

	filter "system:windows"		
		systemversion "latest"

		defines
		{
			"GX_PLATFORM_WINDOWS"
		}	

	filter "configurations:Debug"
		defines "GX_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GX_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GX_DIST"
		runtime "Release"
		optimize "on"

project "GinXUnitTest"
	location "GinXUnitTest"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"GinX/vendor/spdlog/include",
		"GinX/src",
		"GinX/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GinX"
	}

	filter "system:windows"		
		systemversion "latest"

		defines
		{
			"GX_PLATFORM_WINDOWS"
		}	

	filter "configurations:Debug"
		defines "GX_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GX_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GX_DIST"
		runtime "Release"
		optimize "on"