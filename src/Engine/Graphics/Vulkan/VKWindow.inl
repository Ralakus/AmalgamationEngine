
namespace Amalgamation {

	VKWindow::VKWindow() : Window() {}

	VKWindow::VKWindow(const std::string & Title, int Width, int Height, bool Fullscreen)
		: Window(Title, Width, Height, Fullscreen) {}

	VKWindow::~VKWindow() { VulkanCleanUp(); }

	//============================================
	//Vulakn Creation
	//============================================

	FORCEINLINE void VKWindow::InitVulkan() { 
		CreateVKInstance();
		SetUpDebugCallbacks();
		CreateSurface();
		PickPhysicalDevice();
		CreateLogicalDevice();
	}

	//============================================
	//Vulakn Instance Creation
	//============================================

	FORCEINLINE void VKWindow::CreateVKInstance() {

		if (Vulkan.EnableValidationLayers && !CheckValidationLayerSupport()) {
			throw std::runtime_error("Vulkan validation layers requested but not supported!");
		}

		vk::ApplicationInfo AppInfo = {};
		AppInfo.pApplicationName = m_Title.c_str();
		AppInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
		AppInfo.pEngineName = "No Engine";
		AppInfo.engineVersion = VK_MAKE_VERSION(1, 1, 0);
		AppInfo.apiVersion = VK_API_VERSION_1_1;

		vk::InstanceCreateInfo CreateInfo = {};
		CreateInfo.pApplicationInfo = &AppInfo;

		auto Extensions = GetRequiredExtensions();
		CreateInfo.enabledExtensionCount = static_cast<uint32_t>(Extensions.size());
		CreateInfo.ppEnabledExtensionNames = Extensions.data();

		if (Vulkan.EnableValidationLayers) {
			CreateInfo.enabledLayerCount = static_cast<uint32_t>(Vulkan.ValidationLayers.size());
			CreateInfo.ppEnabledLayerNames = Vulkan.ValidationLayers.data();
		}
		else {
			CreateInfo.enabledLayerCount = 0;
		}

		Vulkan.Instance = vk::createInstance(CreateInfo);

	}

	//============================================
	//Vulakn Valadation Layer Creation
	//============================================

	FORCEINLINE bool VKWindow::CheckValidationLayerSupport(){
		std::vector<vk::LayerProperties> AvailableLayers = vk::enumerateInstanceLayerProperties();

		bool LayerFound = false;
		for (const char* LayerName : Vulkan.ValidationLayers) {

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

	FORCEINLINE std::vector<const char*> VKWindow::GetRequiredExtensions() {
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> Extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		if (Vulkan.EnableValidationLayers) {
			Extensions.emplace_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		}

		return Extensions;
	}

	FORCEINLINE void VKWindow::SetUpDebugCallbacks() {
		if (!Vulkan.EnableValidationLayers) return;

		vk::DebugReportCallbackCreateInfoEXT CreateInfo;
		CreateInfo.flags = vk::DebugReportFlagBitsEXT::eError | vk::DebugReportFlagBitsEXT::eWarning | vk::DebugReportFlagBitsEXT::ePerformanceWarning;
		CreateInfo.pfnCallback = DebugCallback;

		//Vulkan.ValidationCallback =  Vulkan.Instance.createDebugReportCallbackEXT(CreateInfo);

		if (CreateDebugReportCallbackEXT(Vulkan.Instance, &static_cast<VkDebugReportCallbackCreateInfoEXT>(CreateInfo),
			nullptr, reinterpret_cast<VkDebugReportCallbackEXT*>(&Vulkan.ValidationCallback)) != VK_SUCCESS) {

		}
		
	}

	FORCEINLINE VkResult VKWindow::CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkDebugReportCallbackEXT * pCallback) {
		auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pCallback);
		}
		else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	FORCEINLINE void VKWindow::DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks * pAllocator) {
		auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
		if (func != nullptr) {
			func(instance, callback, pAllocator);
		}
	}

	//============================================
	//Vulakn Surface Creation
	//============================================

	FORCEINLINE void VKWindow::CreateSurface() {
		if (glfwCreateWindowSurface(Vulkan.Instance, m_Window, nullptr, reinterpret_cast<VkSurfaceKHR*>(&Vulkan.Surface)) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}
	}

	//============================================
	//Vulakn Physical Device Creation
	//============================================

	FORCEINLINE void VKWindow::PickPhysicalDevice() {
		std::vector<vk::PhysicalDevice> Devices = Vulkan.Instance.enumeratePhysicalDevices();
		if (Devices.size() == 0) {
			throw std::runtime_error("Failed to find GPU with Vulkan Support!");
		}

		for (const auto& Device : Devices) {
			if (IsDeviceSuitable(Device)) {
				Vulkan.PhysicalDevice = Device;
				break;
			}
		}

		if (!Vulkan.PhysicalDevice) {
			throw std::runtime_error("failed to find a suitable GPU!");
		}
	}

	FORCEINLINE VKWindow::QueueFamilyIndices VKWindow::FindQueueFamilies(const vk::PhysicalDevice & Device) {
		QueueFamilyIndices Indices;

		std::vector<vk::QueueFamilyProperties> QueueFamilies = Device.getQueueFamilyProperties();

		for (size_t i = 0; i < QueueFamilies.size(); i++) {
			if (QueueFamilies[i].queueCount > 0 && QueueFamilies[i].queueFlags & vk::QueueFlagBits::eGraphics) {
				Indices.GraphicsFamily = static_cast<int>(i);
			}

			if (QueueFamilies[i].queueCount > 0 && Device.getSurfaceSupportKHR(static_cast<uint32_t>(i), Vulkan.Surface)) {
				Indices.PresentFamily = static_cast<int>(i);
			}

			if (Indices.IsComplete()) {
				break;
			}
		}

		return Indices;

	}

	FORCEINLINE bool VKWindow::CheckDeviceExtensionSupport(const vk::PhysicalDevice & Device) {
		std::vector<vk::ExtensionProperties> AvailableExtensions = Device.enumerateDeviceExtensionProperties();
		std::set<std::string> RequiredExtensions(Vulkan.DeviceExtensions.begin(), Vulkan.DeviceExtensions.end());

		for (const auto& Extension : AvailableExtensions) {
			RequiredExtensions.erase(Extension.extensionName);
		}

		return RequiredExtensions.empty();
	}

	FORCEINLINE VKWindow::SwapChainSupportDetails VKWindow::QuerySwapChainSupport(const vk::PhysicalDevice & Device) {
		SwapChainSupportDetails Details;

		Details.Capabilities = Device.getSurfaceCapabilitiesKHR(Vulkan.Surface);
		Details.Formats      = Device.getSurfaceFormatsKHR     (Vulkan.Surface);
		Details.PresentModes = Device.getSurfacePresentModesKHR(Vulkan.Surface);

		return Details;
	}

	FORCEINLINE bool VKWindow::IsDeviceSuitable(const vk::PhysicalDevice & Device) {

		QueueFamilyIndices Indices = FindQueueFamilies(Device);
		bool ExtensionsSupported   = CheckDeviceExtensionSupport(Device);

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

	FORCEINLINE void VKWindow::CreateLogicalDevice() {

		QueueFamilyIndices Indices = FindQueueFamilies(Vulkan.PhysicalDevice);

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

		CreateInfo.enabledExtensionCount = static_cast<uint32_t>(Vulkan.DeviceExtensions.size());
		CreateInfo.ppEnabledExtensionNames = Vulkan.DeviceExtensions.data();

		if (Vulkan.EnableValidationLayers) {
			CreateInfo.enabledExtensionCount = static_cast<uint32_t>(Vulkan.ValidationLayers.size());
			CreateInfo.ppEnabledLayerNames = Vulkan.ValidationLayers.data();
		}
		else {
			CreateInfo.enabledLayerCount = 0;
		}

		Vulkan.Device = Vulkan.PhysicalDevice.createDevice(CreateInfo);

		Vulkan.GraphicsQueue = Vulkan.Device.getQueue(Indices.GraphicsFamily, 0);
		Vulkan.PresendQueue  = Vulkan.Device.getQueue(Indices.PresentFamily,  0);

	}

	//============================================
	//Vulakn Swap Chain Creation
	//============================================

	FORCEINLINE vk::SurfaceFormatKHR VKWindow::ChooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& AvailableFormats) {
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

	FORCEINLINE vk::PresentModeKHR VKWindow::ChooseSwapPresentMode(const std::vector<vk::PresentModeKHR>& AvailablePresentModes) {
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

	FORCEINLINE vk::Extent2D VKWindow::ChooseSwapExtent(const vk::SurfaceCapabilitiesKHR& Capablilities) {
		if (Capablilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
			return Capablilities.currentExtent;
		}
		else {
			vk::Extent2D ActualExtent = { static_cast<uint32_t>(m_Width), static_cast<uint32_t>(m_Height) };

			ActualExtent.width = std::max(Capablilities.minImageExtent.width, std::min(Capablilities.maxImageExtent.width, ActualExtent.width));
			ActualExtent.height = std::max(Capablilities.minImageExtent.height, std::min(Capablilities.maxImageExtent.height, ActualExtent.height));

			return ActualExtent;
		}
	}

	FORCEINLINE void VKWindow::CreateSwapChain() {
		SwapChainSupportDetails SwapChainSupport = QuerySwapChainSupport(Vulkan.PhysicalDevice);

		vk::SurfaceFormatKHR SurfaceFormat = ChooseSwapSurfaceFormat(SwapChainSupport.Formats);
		vk::PresentModeKHR PresentMode = ChooseSwapPresentMode(SwapChainSupport.PresentModes);
		vk::Extent2D Extent = ChooseSwapExtent(SwapChainSupport.Capabilities);

		uint32_t ImageCount = SwapChainSupport.Capabilities.minImageCount + 1;
		if (SwapChainSupport.Capabilities.maxImageCount > 0 && ImageCount > SwapChainSupport.Capabilities.maxImageCount) {
			ImageCount = SwapChainSupport.Capabilities.maxImageCount;
		}

		vk::SwapchainCreateInfoKHR CreateInfo = {};
		CreateInfo.surface = Vulkan.Surface;

		CreateInfo.minImageCount = ImageCount;
		CreateInfo.imageFormat = SurfaceFormat.format;
		CreateInfo.imageColorSpace = SurfaceFormat.colorSpace;
		CreateInfo.imageExtent = Extent;
		CreateInfo.imageArrayLayers = 1;
		CreateInfo.imageUsage = vk::ImageUsageFlagBits::eColorAttachment;

		QueueFamilyIndices Indices = FindQueueFamilies(Vulkan.PhysicalDevice);
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

		Vulkan.SwapchainFormat = SurfaceFormat.format;
		Vulkan.SwapChainExtent = Extent;

		Vulkan.SwapChain = Vulkan.Device.createSwapchainKHR(CreateInfo);

		Vulkan.SwapChainImages = Vulkan.Device.getSwapchainImagesKHR(Vulkan.SwapChain);

	}

	//============================================
	//Vulakn Clean up
	//============================================

	FORCEINLINE void VKWindow::VulkanCleanUp() {
		if (Vulkan.EnableValidationLayers) {
			DestroyDebugReportCallbackEXT(Vulkan.Instance, Vulkan.ValidationCallback, nullptr);
		}

		Vulkan.Device.destroySwapchainKHR(Vulkan.SwapChain);
		Vulkan.Device.destroy();
		Vulkan.Instance.destroySurfaceKHR(Vulkan.Surface);
		Vulkan.Instance.destroy();

	}
}