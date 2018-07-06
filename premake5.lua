-- premake5.lua

function IncludeGlm() 
   includedirs "lib/glm/"
end

function IncludeGLFW()
   includedirs "lib/glfw/include"
end

function IncludeVulkan() --Vulkan SDK include
   includedirs "C:/VulkanSDK/1.1.77.0/Include"
end

function LinkVulkan()
	libdirs "C:/VulkanSDK/1.1.77.0/Lib"
	
	filter "kind:not StaticLib"
		links "vulkan-1"
	filter {}
end

function LinkGLFW()
	libdirs "lib/glfw/"
	
	filter "kind:not StaticLib"
		links "glfw3"
	filter {}
end

workspace "Amalgamation"
   language "C++"

   location "build"

   architecture "x86_64"

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

   defines { "GLFW_INCLUDE_VULKAN" }

   includedirs "src"

   IncludeGLFW()
   IncludeGlm()
   IncludeVulkan()
   LinkGLFW()
   LinkVulkan()

   files { "**.hpp", "**.cpp", "**.inl" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      defines { "AE_DEBUG" }

   filter "configurations:Release"
      defines { "NDEBUG" }
      defines { "AE_RELEASE" }