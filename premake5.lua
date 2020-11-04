-- premake5.lua
workspace "Chess-Program"
	configurations {"Debug", "Release"}

project "Chess-Program"
	location "Chess-Program"
	kind "ConsoleApp"
	language "C++"

	targetdir "%{cfg.buildcfg}"
	
	files {"%{prj.name}/**.cpp","%{prj.name}/**.h"}

filter "configurations:Debug"
	defines {"DEBUG"}
	symbols "On"

filter "configurations:Release"
	defines {"NDEBUG"}
	optimize "On"