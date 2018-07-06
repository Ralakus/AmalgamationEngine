#pragma once

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include <Core/Platform/HelperMacros.hpp>

#include <vector>

namespace Amalgamation{

	class VKInstance {

		bool m_Valid = false;

	public:

		 VKInstance();
		 VKInstance(const char* Name);
		~VKInstance();

		vk::Instance Instance;
		bool ValidationLayers = false;

		bool CreateInstance(const char* Name = "AEVK") {

			vk::ApplicationInfo AppInfo = {};
			AppInfo.pApplicationName   = Name;
			AppInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
			AppInfo.apiVersion         = VK_API_VERSION_1_1;

			vk::InstanceCreateInfo CreateInfo = {};
			CreateInfo.pApplicationInfo = &AppInfo;

			std::vector<const char*> RequiredExtensions = GetRequiredExtensions();
			CreateInfo.enabledExtensionCount = static_cast<uint32_t>(RequiredExtensions.size());
			CreateInfo.ppEnabledExtensionNames = RequiredExtensions.data();

			Instance = vk::createInstance(CreateInfo, nullptr);

			m_Valid = true;

			return true;
		}

		FORCEINLINE bool DestroyInstance() { if (m_Valid) { Instance.destroy(nullptr); return true; } else { return false; } }

		std::vector<const char*> GetRequiredExtensions() {
			uint32_t glfwExtensionCount = 0;
			const char** glfwExtensions;
			glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

			std::vector<const char*> Extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

			return Extensions;
		}

	};

}

#if !defined(AE_NO_IMPL)
    #include "VKInstance.inl"
#endif
