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

function IncludeGlad()
   includedirs "lib/glad/include"
end

function IncludeImGui()
   includedirs "lib/ImGui"
end

function LinkImGui()
   links "ImGui"
end

function LinkGlad()

   links "Glad"

   filter { "system:windows" }
      links { "OpenGL32" }
        
   filter { "system:not windows" }
      links { "GL" }
   filter {}
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
        if(Is64bit) then
           libdirs "lib/glfw/"
        end
	
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

   --defines { "GLFW_INCLUDE_VULKAN" }

   includedirs "src"

   IncludeGLFW()
   IncludeGlm()
   IncludeVulkan()
   IncludeRang()
   IncludeStb()
   IncludeGlad()
   IncludeImGui()

   LinkGLFW()
   LinkVulkan()
   LinkGlad()
   LinkImGui()

   files { "src/**.hpp", "src/**.cpp", "src/**.inl" }

   filter "configurations:Debug"
      defines { "DEBUG" }

   filter "configurations:Release"
      defines { "NDEBUG" }

project "ImGui"
   kind "StaticLib"

   IncludeGlad()
   IncludeGLFW()

   files { "lib/ImGui/**" }

   filter "configurations:Debug"
      defines { "DEBUG" }

   filter "configurations:Release"
      defines { "NDEBUG" }
   filter {}

project "Glad"

   kind "StaticLib"

   IncludeGlad()

   files { "lib/glad/src/**" }

   filter "configurations:Debug"
      defines { "DEBUG" }

   filter "configurations:Release"
      defines { "NDEBUG" }
   filter {}
