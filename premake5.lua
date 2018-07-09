-- premake5.lua

Is64bit = true  -- 32 bit if false

function IncludeGlm()   --GLM include
   includedirs "lib/glm/"
end

function IncludeGLFW() --GLFW include
   includedirs "lib/glfw/include"
end

function IncludeVulkan() --Vulkan SDK include
   includedirs "C:/VulkanSDK/1.1.77.0/Include"
end

function IncludeRang()
   includedirs "lib/rang/"
end

function IncludeStb()
        includedirs "lib/stb/"
end

function LinkVulkan() --Vulkan Static Link
        filter { "architecture:x86_64" }
           libdirs "C:/VulkanSDK/1.1.77.0/Lib"

        filter { "architecture:x86" }
           libdirs "C:/VulkanSDK/1.1.77.0/Lib32"
        filter {}
	
	filter "kind:not StaticLib"
		links "vulkan-1"
	filter {}
end

function LinkGLFW() --GLFW Static link
	libdirs "lib/glfw/"
	
	filter "kind:not StaticLib"
		links "glfw3"
	filter {}
end

workspace "Amalgamation"
   language "C++"

   location "build"

   if(Is64bit) then
      architecture "x86_64"
   else
      architecture "x86"
   end

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
   IncludeRang()
   IncludeStb()
   LinkGLFW()
   LinkVulkan()

   files { "**.hpp", "**.cpp", "**.inl" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      defines { "AE_DEBUG" }

   filter "configurations:Release"
      defines { "NDEBUG" }
      defines { "AE_RELEASE" }