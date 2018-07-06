#pragma once

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include <Core/Platform/HelperMacros.hpp>

#include <vector>

namespace Amalgamation{

	class VKInstance {

	public:

		vk::Instance Instance;
		bool ValidationLayers = false;

		bool CreateInstance(const char* Name, const char* EngineName) {

			vk::ApplicationInfo AppInfo = {};
			AppInfo.pApplicationName   = Name;
			AppInfo.applicationVersion = VK_MAKE_VERSION(1, 1, 77);
			AppInfo.pEngineName        = EngineName;
			AppInfo.engineVersion      = VK_MAKE_VERSION(1, 1, 77);
			AppInfo.apiVersion         = VK_API_VERSION_1_1;

			vk::InstanceCreateInfo CreateInfo = {};
			CreateInfo.pApplicationInfo = &AppInfo;

			std::vector<const char*> RequiredExtensions = GetRequiredExtensions();
			CreateInfo.enabledExtensionCount = static_cast<uint32_t>(RequiredExtensions.size());
			CreateInfo.ppEnabledExtensionNames = RequiredExtensions.data();

			/*if (vk::CreateInstance(&CreateInfo, nullptr, &Instance) != VK_SUCCESS) {
				throw std::runtime_error("failed to create instance!");
			}*/
		}

		FORCEINLINE bool DestroyInstance() { Instance.destroy(); }

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
