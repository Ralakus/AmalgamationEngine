
namespace Amalgamation {

	bool AEVK::CreateVKInstance(vk::Instance & Instance, const char* Name) {
		vk::ApplicationInfo AppInfo = {};
		AppInfo.pApplicationName = Name;
		AppInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
		AppInfo.apiVersion = VK_API_VERSION_1_1;

		vk::InstanceCreateInfo CreateInfo = {};
		CreateInfo.pApplicationInfo = &AppInfo;

		std::vector<const char*> RequiredExtensions = GetRequiredExtensions();
		CreateInfo.enabledExtensionCount = static_cast<uint32_t>(RequiredExtensions.size());
		CreateInfo.ppEnabledExtensionNames = RequiredExtensions.data();

		Instance = vk::createInstance(CreateInfo, nullptr);

		return true;;
	}

	FORCEINLINE std::vector<const char*> AEVK::GetRequiredExtensions() {
			uint32_t glfwExtensionCount = 0;
			const char** glfwExtensions;
			glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

			std::vector<const char*> Extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

			return Extensions;
	}

}