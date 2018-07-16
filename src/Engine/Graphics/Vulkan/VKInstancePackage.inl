
namespace Amalgamation {


	//============================================
	//Vulakn Creation
	//============================================

	FORCEINLINE void AEVK::InitVulkan(GLFWwindow* Window, uint32_t Width, uint32_t Height) {
		CreateVKInstance();
		SetUpDebugCallbacks();
		CreateSurface(Window);
		PickPhysicalDevice();
		CreateLogicalDevice();
		CreateSwapChain(Width, Height);
	}

	//============================================
	//Vulakn Instance Creation
	//============================================

	FORCEINLINE void AEVK::CreateVKInstance() {

		if (EnableValidationLayers && !CheckValidationLayerSupport()) {
			throw std::runtime_error("Vulkan validation layers requested but not supported!");
		}

		vk::ApplicationInfo AppInfo = {};
		AppInfo.pApplicationName = "Amalgamation";
		AppInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
		AppInfo.pEngineName = "No Engine";
		AppInfo.engineVersion = VK_MAKE_VERSION(1, 1, 0);
		AppInfo.apiVersion = VK_API_VERSION_1_1;

		vk::InstanceCreateInfo CreateInfo = {};
		CreateInfo.pApplicationInfo = &AppInfo;

		auto Extensions = GetRequiredExtensions();
		CreateInfo.enabledExtensionCount = static_cast<uint32_t>(Extensions.size());
		CreateInfo.ppEnabledExtensionNames = Extensions.data();

		if (EnableValidationLayers) {
			CreateInfo.enabledLayerCount = static_cast<uint32_t>(ValidationLayers.size());
			CreateInfo.ppEnabledLayerNames = ValidationLayers.data();
		}
		else {
			CreateInfo.enabledLayerCount = 0;
		}

		Instance = vk::createInstance(CreateInfo);

	}

	//============================================
	//Vulakn Valadation Layer Creation
	//============================================

	FORCEINLINE bool AEVK::CheckValidationLayerSupport() {
		std::vector<vk::LayerProperties> AvailableLayers = vk::enumerateInstanceLayerProperties();

		bool LayerFound = false;
		for (const char* LayerName : ValidationLayers) {

			for (const auto& LayerProperties : AvailableLayers) {
				if (strcmp(LayerName, LayerProperties.layerName) == 0) {
					LayerFound = true;
					break;
				}
			}

			if (!LayerFound) {
				return false;
			}
		}

		return true;
	}

	FORCEINLINE std::vector<const char*> AEVK::GetRequiredExtensions() {
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> Extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		if (EnableValidationLayers) {
			Extensions.emplace_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		}

		return Extensions;
	}

	FORCEINLINE void AEVK::SetUpDebugCallbacks() {
		if (!EnableValidationLayers) return;

		vk::DebugReportCallbackCreateInfoEXT CreateInfo;
		CreateInfo.flags = vk::DebugReportFlagBitsEXT::eError | vk::DebugReportFlagBitsEXT::eWarning | vk::DebugReportFlagBitsEXT::ePerformanceWarning;
		CreateInfo.pfnCallback = DebugCallback;

		//ValidationCallback =  Instance.createDebugReportCallbackEXT(CreateInfo);
		VkDebugReportCallbackCreateInfoEXT cCallback = CreateInfo;

		if (CreateDebugReportCallbackEXT(Instance, &cCallback,
			nullptr, reinterpret_cast<VkDebugReportCallbackEXT*>(&ValidationCallback)) != VK_SUCCESS) {

		}

	}

	FORCEINLINE VkResult AEVK::CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkDebugReportCallbackEXT * pCallback) {
		auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pCallback);
		}
		else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	FORCEINLINE void AEVK::DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks * pAllocator) {
		auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
		if (func != nullptr) {
			func(instance, callback, pAllocator);
		}
	}

	//============================================
	//Vulakn Surface Creation
	//============================================

	FORCEINLINE void AEVK::CreateSurface(GLFWwindow* Window) {
		if (glfwCreateWindowSurface(Instance, Window, nullptr, reinterpret_cast<VkSurfaceKHR*>(&Surface)) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}
	}

	//============================================
	//Vulakn Physical Device Creation
	//============================================

	FORCEINLINE void AEVK::PickPhysicalDevice() {
		std::vector<vk::PhysicalDevice> Devices = Instance.enumeratePhysicalDevices();
		if (Devices.size() == 0) {
			throw std::runtime_error("Failed to find GPU with Vulkan Support!");
		}

		for (const auto& Device : Devices) {
			if (IsDeviceSuitable(Device)) {
				PhysicalDevice = Device;
				break;
			}
		}

		if (!PhysicalDevice) {
			throw std::runtime_error("failed to find a suitable GPU!");
		}
	}

	FORCEINLINE AEVK::QueueFamilyIndices AEVK::FindQueueFamilies(const vk::PhysicalDevice & Device) {
		QueueFamilyIndices Indices;

		std::vector<vk::QueueFamilyProperties> QueueFamilies = Device.getQueueFamilyProperties();

		for (size_t i = 0; i < QueueFamilies.size(); i++) {
			if (QueueFamilies[i].queueCount > 0 && QueueFamilies[i].queueFlags & vk::QueueFlagBits::eGraphics) {
				Indices.GraphicsFamily = static_cast<int>(i);
			}

			if (QueueFamilies[i].queueCount > 0 && Device.getSurfaceSupportKHR(static_cast<uint32_t>(i), Surface)) {
				Indices.PresentFamily = static_cast<int>(i);
			}

			if (Indices.IsComplete()) {
				break;
			}
		}

		return Indices;

	}

	FORCEINLINE bool AEVK::CheckDeviceExtensionSupport(const vk::PhysicalDevice & Device) {
		std::vector<vk::ExtensionProperties> AvailableExtensions = Device.enumerateDeviceExtensionProperties();
		std::set<std::string> RequiredExtensions(DeviceExtensions.begin(), DeviceExtensions.end());

		for (const auto& Extension : AvailableExtensions) {
			RequiredExtensions.erase(Extension.extensionName);
		}

		return RequiredExtensions.empty();
	}

	FORCEINLINE AEVK::SwapChainSupportDetails AEVK::QuerySwapChainSupport(const vk::PhysicalDevice & Device) {
		SwapChainSupportDetails Details;

		Details.Capabilities = Device.getSurfaceCapabilitiesKHR(Surface);
		Details.Formats = Device.getSurfaceFormatsKHR(Surface);
		Details.PresentModes = Device.getSurfacePresentModesKHR(Surface);

		return Details;
	}

	FORCEINLINE bool AEVK::IsDeviceSuitable(const vk::PhysicalDevice & Device) {

		QueueFamilyIndices Indices = FindQueueFamilies(Device);
		bool ExtensionsSupported = CheckDeviceExtensionSupport(Device);

		bool SwapChainAdequate = false;
		if (ExtensionsSupported) {
			SwapChainSupportDetails SwapChainSupport = QuerySwapChainSupport(Device);
			SwapChainAdequate = !SwapChainSupport.Formats.empty() && !SwapChainSupport.PresentModes.empty();
		}

		return Indices.IsComplete() && ExtensionsSupported && SwapChainAdequate;

	}

	//============================================
	//Vulakn Logical Device Creation
	//============================================

	FORCEINLINE void AEVK::CreateLogicalDevice() {

		QueueFamilyIndices Indices = FindQueueFamilies(PhysicalDevice);

		std::vector<vk::DeviceQueueCreateInfo> QueueCreateInfo;
		std::set<int> UniqueQueueFamilies = { Indices.GraphicsFamily, Indices.PresentFamily };

		float QueuePriority = 1.f;
		for (int QueueFamily : UniqueQueueFamilies) {
			QueueCreateInfo.emplace_back(vk::DeviceQueueCreateFlags(), QueueFamily, 1, &QueuePriority);
		}

		vk::PhysicalDeviceFeatures DeviceFeatures = {};

		vk::DeviceCreateInfo CreateInfo = {};

		CreateInfo.queueCreateInfoCount = static_cast<uint32_t>(QueueCreateInfo.size());
		CreateInfo.pQueueCreateInfos = QueueCreateInfo.data();

		CreateInfo.pEnabledFeatures = &DeviceFeatures;

		CreateInfo.enabledExtensionCount = static_cast<uint32_t>(DeviceExtensions.size());
		CreateInfo.ppEnabledExtensionNames = DeviceExtensions.data();

		if (EnableValidationLayers) {
			CreateInfo.enabledExtensionCount = static_cast<uint32_t>(ValidationLayers.size());
			CreateInfo.ppEnabledLayerNames = ValidationLayers.data();
		}
		else {
			CreateInfo.enabledLayerCount = 0;
		}

		Device = PhysicalDevice.createDevice(CreateInfo);

		GraphicsQueue = Device.getQueue(Indices.GraphicsFamily, 0);
		PresendQueue = Device.getQueue(Indices.PresentFamily, 0);

	}

	//============================================
	//Vulakn Swap Chain Creation
	//============================================

	FORCEINLINE vk::SurfaceFormatKHR AEVK::ChooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& AvailableFormats) {
		if (AvailableFormats.size() == 1 && AvailableFormats[0].format == vk::Format::eUndefined) {
			return { vk::Format::eB8G8R8A8Unorm, vk::ColorSpaceKHR::eSrgbNonlinear };
		}

		for (const auto& AvailableFormat : AvailableFormats) {
			if (AvailableFormat.format == vk::Format::eB8G8R8A8Unorm && AvailableFormat.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
				return AvailableFormat;
			}
		}

		return AvailableFormats[0];
	}

	FORCEINLINE vk::PresentModeKHR AEVK::ChooseSwapPresentMode(const std::vector<vk::PresentModeKHR>& AvailablePresentModes) {
		vk::PresentModeKHR BestMode = vk::PresentModeKHR::eFifo;

		for (const auto& AvailablePresentMode : AvailablePresentModes) {
			if (AvailablePresentMode == vk::PresentModeKHR::eMailbox) {
				return AvailablePresentMode;
			}
			else if (AvailablePresentMode == vk::PresentModeKHR::eImmediate) {
				BestMode = AvailablePresentMode;
			}
		}

		return BestMode;
	}

	FORCEINLINE vk::Extent2D AEVK::ChooseSwapExtent(const vk::SurfaceCapabilitiesKHR& Capablilities, uint32_t Width, uint32_t Height) {
		if (Capablilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
			return Capablilities.currentExtent;
		}
		else {
			vk::Extent2D ActualExtent = { Width, Height };

			ActualExtent.width = std::max(Capablilities.minImageExtent.width, std::min(Capablilities.maxImageExtent.width, ActualExtent.width));
			ActualExtent.height = std::max(Capablilities.minImageExtent.height, std::min(Capablilities.maxImageExtent.height, ActualExtent.height));

			return ActualExtent;
		}
	}

	FORCEINLINE void AEVK::CreateSwapChain(uint32_t Width, uint32_t Height) {
		SwapChainSupportDetails SwapChainSupport = QuerySwapChainSupport(PhysicalDevice);

		vk::SurfaceFormatKHR SurfaceFormat = ChooseSwapSurfaceFormat(SwapChainSupport.Formats);
		vk::PresentModeKHR PresentMode = ChooseSwapPresentMode(SwapChainSupport.PresentModes);
		vk::Extent2D Extent = ChooseSwapExtent(SwapChainSupport.Capabilities, Width, Height);

		uint32_t ImageCount = SwapChainSupport.Capabilities.minImageCount + 1;
		if (SwapChainSupport.Capabilities.maxImageCount > 0 && ImageCount > SwapChainSupport.Capabilities.maxImageCount) {
			ImageCount = SwapChainSupport.Capabilities.maxImageCount;
		}

		vk::SwapchainCreateInfoKHR CreateInfo = {};
		CreateInfo.surface = Surface;

		CreateInfo.minImageCount = ImageCount;
		CreateInfo.imageFormat = SurfaceFormat.format;
		CreateInfo.imageColorSpace = SurfaceFormat.colorSpace;
		CreateInfo.imageExtent = Extent;
		CreateInfo.imageArrayLayers = 1;
		CreateInfo.imageUsage = vk::ImageUsageFlagBits::eColorAttachment;

		QueueFamilyIndices Indices = FindQueueFamilies(PhysicalDevice);
		uint32_t QueueFamiliyIndices[] = { static_cast<uint32_t>(Indices.GraphicsFamily), static_cast<uint32_t>(Indices.PresentFamily) };

		if (Indices.GraphicsFamily != Indices.PresentFamily) {
			CreateInfo.imageSharingMode = vk::SharingMode::eConcurrent;
			CreateInfo.queueFamilyIndexCount = 2;
			CreateInfo.pQueueFamilyIndices = QueueFamiliyIndices;
		}
		else {
			CreateInfo.imageSharingMode = vk::SharingMode::eExclusive;
			CreateInfo.queueFamilyIndexCount = 0;
			CreateInfo.pQueueFamilyIndices = nullptr;
		}

		CreateInfo.preTransform = SwapChainSupport.Capabilities.currentTransform;
		CreateInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;

		CreateInfo.presentMode = PresentMode;
		CreateInfo.clipped = VK_TRUE;

		CreateInfo.oldSwapchain = nullptr;

		SwapchainFormat = SurfaceFormat.format;
		SwapChainExtent = Extent;

		SwapChain = Device.createSwapchainKHR(CreateInfo);

		SwapChainImages = Device.getSwapchainImagesKHR(SwapChain);

	}

	//============================================
	//Vulakn Clean up
	//============================================

	FORCEINLINE void AEVK::VulkanCleanUp() {
		if (EnableValidationLayers) {
			DestroyDebugReportCallbackEXT(Instance, ValidationCallback, nullptr);
		}

		Device.destroySwapchainKHR(SwapChain);
		Device.destroy();
		Instance.destroySurfaceKHR(Surface);
		Instance.destroy();

	}

}