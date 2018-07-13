#pragma once

#include <Core/Platform/Platform.hpp>

#define GLFW_INCLUDE_VULKAN
#undef APIENTRY
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>


#include <iostream>
#include <vector>

#undef APIENTRY
#include <rang.hpp>
#undef max
#undef min
#undef APIENTRY

namespace Amalgamation {

	class AEVKInstance {

		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
			VkDebugReportFlagsEXT flags,
			VkDebugReportObjectTypeEXT objType,
			uint64_t obj,
			size_t location,
			int32_t code,
			const char* layerPrefix,
			const char* msg,
			void* userData) {

			std::cerr << rang::fgB::red << "[ vk::error ]: " << rang::fg::reset << msg << rang::fgB::yellow << "\nEND" << rang::fg::reset << std::endl;

			return VK_FALSE;
		}

	public:

		vk::Instance                  VulkanInstance;
		vk::DebugReportCallbackEXT    ValidationCallback;

		const std::vector<const char*> ValidationLayers = {
			"VK_LAYER_LUNARG_standard_validation",
		};
		const std::vector<const char*> DeviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};
		std::vector<const char*> GetRequiredExtensions();
		bool CheckValidationLayerSupport();

		bool ValidationLayersEnabled = true;

		 AEVKInstance() {}
		~AEVKInstance() {}

		void Create();
		void Destroy();


		FORCEINLINE operator vk::Instance&() { return VulkanInstance; }

		vk::Result CreateDebugReportCallbackEXT(vk::Instance& Instance, const vk::DebugReportCallbackCreateInfoEXT& CreateInfo,
												const vk::Optional<vk::AllocationCallbacks>& Allocator, vk::DebugReportCallbackEXT& Callback);

		void DestroyDebugReportCallbackEXT(vk::Instance& Instance, vk::DebugReportCallbackEXT& Callback, const vk::AllocationCallbacks& Allocator);

	};


}

#ifndef AE_NO_IMPL
	#include "VKInstance.inl"
#endif