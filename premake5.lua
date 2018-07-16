-- premake5.lua

Is64bit = true  -- 32 bit if false
VulkanSDKPath = os.getenv("VULKAN_SDK")

IncludePaths = {}
IncludePaths["glm"] = "lib/glm"
IncludePaths["glfw"] = "lib/glfw/include"
IncludePaths["vulkan"] = (VulkanSDKPath .. "/Include")
IncludePaths["rang"] = "lib/rang"
IncludePaths["stb"] = "lib/stb"
IncludePaths["glad"] = "lib/glad/include"
IncludePaths["imgui"] = "lib/ImGui"

LinkerPathsx86 = {}
LinkerPathsx86["vulkan"] = (VulkanSDKPath.."/Lib32")
LinkerPathsx86["glfw"] = "lib/glfw"
LinkerPathsx86["glad"] = "Glad"
LinkerPathsx86["imgui"] = "ImGui"

LinkerPathsx64 = {}
LinkerPathsx64["vulkan"] = (VulkanSDKPath.."/Lib")
LinkerPathsx64["glfw"] = "lib/glfw"
LinkerPathsx64["glad"] = "Glad"
LinkerPathsx64["imgui"] = "ImGui"


--Linker functions ========================================================================

function LinkImGui()
        links "ImGui"
end

function LinkGlad()

        links (LinkerPathsx64["glad"])

        filter { "system:windows" }
                links { "OpenGL32" }

        filter { "system:not windows" }
                links { "GL" }
        filter {}
end

function LinkVulkan() --Vulkan Static Link
        filter { "architecture:x86_64" }
                libdirs (LinkerPathsx64["vulkan"])

        filter { "architecture:x86" }
                libdirs (LinkerPathsx86["vulkan"])

        filter "kind:not StaticLib"
                links "vulkan-1"
        filter {}
end

function LinkGLFW() --GLFW Static link
        filter { "architecture:x86_64" }
                libdirs (LinkerPathsx64["glfw"])

        filter { "architecture:x86" }
                libdirs (LinkerPathsx86["glfw"])

        filter "kind:not StaticLib"
                links "glfw3"
        filter {}
end

--Project Setup ========================================================================

workspace "Amalgamation"
        language "C++"
        cppdialect "C++14" 

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

--Engine project ========================================================================

project "Amalgamation"

        kind "ConsoleApp"

        includedirs "src"

        includedirs (IncludePaths["glfw"])
        includedirs (IncludePaths["glm"])
        includedirs (IncludePaths["vulkan"])
        includedirs (IncludePaths["rang"])
        includedirs (IncludePaths["stb"])
        includedirs (IncludePaths["glad"])
        includedirs (IncludePaths["imgui"])

        LinkGLFW()
        LinkVulkan()
        LinkGlad()
        LinkImGui()

        files { "src/**.hpp", "src/**.cpp", "src/**.inl" }

        filter "configurations:Debug"
                defines { "DEBUG" }

        filter "configurations:Release"
                defines { "NDEBUG" }


-- Dependency projects ========================================================================

project "ImGui"
        kind "StaticLib"

        includedirs (IncludePaths["glad"])
        includedirs (IncludePaths["glfw"])

        files { "lib/ImGui/**" }

        filter "configurations:Debug"
                defines { "DEBUG" }

        filter "configurations:Release"
                defines { "NDEBUG" }
        filter {}

        project "Glad"

        kind "StaticLib"

        includedirs (IncludePaths["glad"])

        files { "lib/glad/src/**" }

        filter "configurations:Debug"
                defines { "DEBUG" }

        filter "configurations:Release"
                defines { "NDEBUG" }
        filter {}
