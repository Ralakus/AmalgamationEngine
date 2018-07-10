#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>
#include <iostream>
#include <set>

#undef APIENTRY
#include <rang.hpp>
#undef max
#undef min

namespace Amalgamation {

	class AEVK {

	public:

		const std::vector<const char*> ValidationLayers = {
			"VK_LAYER_LUNARG_standard_validation"
		};

		const std::vector<const char*> DeviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

		bool						 EnableValidationLayers;
		vk::Instance				 Instance;
		vk::PhysicalDevice			 PhysicalDevice;
		vk::Device					 Device;
		vk::Queue					 GraphicsQueue;
		vk::Queue					 PresendQueue;
		vk::DebugReportCallbackEXT	 ValidationCallback;
		vk::SurfaceKHR				 Surface;
		vk::SwapchainKHR			 SwapChain;
		std::vector<vk::Image>		 SwapChainImages;
		vk::Format					 SwapchainFormat;
		vk::Extent2D				 SwapChainExtent;


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

		//============================================
		//Vulakn Data Structures
		//============================================

		struct QueueFamilyIndices {
			int GraphicsFamily = -1;
			int PresentFamily = -1;

			bool IsComplete() {
				return GraphicsFamily >= 0 && PresentFamily >= 0;
			}
		};
		struct SwapChainSupportDetails {
			vk::SurfaceCapabilitiesKHR Capabilities;
			std::vector<vk::SurfaceFormatKHR> Formats;
			std::vector<vk::PresentModeKHR> PresentModes;
		};

		//============================================
		//Vulakn Creation
		//============================================

		void InitVulkan(GLFWwindow* Window, uint32_t Width, uint32_t Height);

		//============================================
		//Vulakn Instance Creation
		//============================================

		void CreateVKInstance();

		//============================================
		//Vulakn Valadation Layer Creation
		//============================================

		bool CheckValidationLayerSupport();
		std::vector<const char*> GetRequiredExtensions();
		void SetUpDebugCallbacks();
		VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback);
		void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator);

		//============================================
		//Vulakn Surface Creation
		//============================================

		void CreateSurface(GLFWwindow* Window);

		//============================================
		//Vulakn Physical Device Creation
		//============================================

		void PickPhysicalDevice();
		QueueFamilyIndices FindQueueFamilies(const vk::PhysicalDevice& Device);
		bool CheckDeviceExtensionSupport(const vk::PhysicalDevice& Device);
		SwapChainSupportDetails QuerySwapChainSupport(const vk::PhysicalDevice& Device);
		bool IsDeviceSuitable(const vk::PhysicalDevice& Device);

		//============================================
		//Vulakn Logical Device Creation
		//============================================

		void CreateLogicalDevice();

		//============================================
		//Vulakn Swap Chain Creation
		//============================================

		vk::SurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& AvailableFormats);
		vk::PresentModeKHR ChooseSwapPresentMode(const std::vector<vk::PresentModeKHR>& AvailablePresentModes);
		vk::Extent2D ChooseSwapExtent(const vk::SurfaceCapabilitiesKHR& Capablilities, uint32_t Width, uint32_t Height);
		void CreateSwapChain(uint32_t Width, uint32_t Height);

		//============================================
		//Vulakn Clean up
		//============================================

		void VulkanCleanUp();

		 AEVK() {}
		~AEVK() {}

	};

}

#ifndef AE_NO_IMPL
	#include "VKInstancePackage.inl"
#endif