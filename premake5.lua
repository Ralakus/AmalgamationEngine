-- premake5.lua
workspace "Amalgamation"
   language "C++"

   location "build"

   configurations { "Debug", "Release" }

	filter { "configurations:Debug" }
        symbols "On"
	
	filter { "configurations:Release" }
		optimize "On"

	filter { }
	
   targetdir ("build/bin/%{prj.name}/%{cfg.longname}")

   objdir ("build/obj/%{prj.name}/%{cfg.longname}")

project "Amalgamation"

   kind "ConsoleApp"

   files { "**.hpp", "**.cpp", "**.inl" }

   filter "configurations:Debug"
      defines { "AE_DEBUG" }

   filter "configurations:Release"
      defines { "AE_RELEASE" }