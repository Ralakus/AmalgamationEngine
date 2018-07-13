
namespace Amalgamation {

	void AEVKInstance::Create() {

		if (ValidationLayersEnabled && !CheckValidationLayerSupport()) {
			throw std::runtime_error("Vulkan validation layers requested but not supported!");
		}

		vk::ApplicationInfo AppInfo = {};
		AppInfo.pApplicationName = "Amalgamation";
		AppInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
		AppInfo.pEngineName = "No Engine";
		AppInfo.engineVersion = VK_MAKE_VERSION(1, 1, 0);
		AppInfo.apiVersion = VK_API_VERSION_1_1;

		vk::InstanceCreateInfo InstanceCreateInfo = {};
		InstanceCreateInfo.pApplicationInfo = &AppInfo;

		auto Extensions = GetRequiredExtensions();
		InstanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(Extensions.size());
		InstanceCreateInfo.ppEnabledExtensionNames = Extensions.data();

		if (ValidationLayersEnabled) {
			InstanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(ValidationLayers.size());
			InstanceCreateInfo.ppEnabledLayerNames = ValidationLayers.data();
		}
		else {
			InstanceCreateInfo.enabledLayerCount = 0;
		}

		VulkanInstance = vk::createInstance(InstanceCreateInfo);

		if (!ValidationLayersEnabled) return;

		vk::DebugReportCallbackCreateInfoEXT DebugCreateInfo;
		DebugCreateInfo.flags = vk::DebugReportFlagBitsEXT::eError | vk::DebugReportFlagBitsEXT::eWarning | vk::DebugReportFlagBitsEXT::ePerformanceWarning;
		DebugCreateInfo.pfnCallback = DebugCallback;

		//ValidationCallback =  Instance.createDebugReportCallbackEXT(CreateInfo);

		if (CreateDebugReportCallbackEXT(VulkanInstance, DebugCreateInfo, nullptr, ValidationCallback) != vk::Result::eSuccess) {
			throw std::runtime_error("Failed to create debug callback!");
		}

	}

	void AEVKInstance::Destroy() {

		if (ValidationLayersEnabled) {
			DestroyDebugReportCallbackEXT(VulkanInstance, ValidationCallback, nullptr);
		}

		VulkanInstance.destroy();

	}

	FORCEINLINE std::vector<const char*> AEVKInstance::GetRequiredExtensions()
	{
		uint32_t GLFWExtensionCount = 0;
		const char** GLFWExtensions = glfwGetRequiredInstanceExtensions(&GLFWExtensionCount);

		std::vector<const char*> Extensions(GLFWExtensions, GLFWExtensions + GLFWExtensionCount);

		if (ValidationLayersEnabled) {
			Extensions.emplace_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		}

		return Extensions;
	}

	FORCEINLINE bool AEVKInstance::CheckValidationLayerSupport() {
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

	inline vk::Result AEVKInstance::CreateDebugReportCallbackEXT(vk::Instance & Instance, const vk::DebugReportCallbackCreateInfoEXT & CreateInfo, const vk::Optional<vk::AllocationCallbacks>& Allocator, vk::DebugReportCallbackEXT & Callback)
	{
		auto func = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(Instance.getProcAddr("vkCreateDebugReportCallbackEXT"));
		if (func != nullptr) {
			return vk::Result(func(Instance, &static_cast<VkDebugReportCallbackCreateInfoEXT>(CreateInfo),
				reinterpret_cast<const VkAllocationCallbacks*>(Allocator.operator vk::AllocationCallbacks *()), reinterpret_cast<VkDebugReportCallbackEXT*>(&Callback)));
		}
		else {
			return vk::Result::eErrorExtensionNotPresent;
		}

	}

	FORCEINLINE void AEVKInstance::DestroyDebugReportCallbackEXT(vk::Instance& Instance, vk::DebugReportCallbackEXT & Callback, const vk::AllocationCallbacks & Allocator) {
		auto func = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(Instance.getProcAddr("vkDestroyDebugReportCallbackEXT"));
		if (func != nullptr) {
			func(Instance, Callback, &static_cast<VkAllocationCallbacks>(Allocator));
		}

	}

}