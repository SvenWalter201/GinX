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

group "Dependencies"
	include "GinX/vendor/GLFW"
	include "GinX/vendor/Glad"
	include "GinX/vendor/imgui"
group ""

project "GinX"
	location "GinX"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "gxpch.h"
	pchsource "GinX/src/gxpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"GX_PLATFORM_WINDOWS",
			"GX_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "GX_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "GX_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "GX_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
		staticruntime "off"

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
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"GX_PLATFORM_WINDOWS"
		}	

	filter "configurations:Debug"
		defines "GX_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "GX_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "GX_DIST"
		runtime "Release"
		optimize "On"