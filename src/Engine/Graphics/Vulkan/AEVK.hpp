#pragma once

#include <Core/Platform/HelperMacros.hpp>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

namespace Amalgamation {

	class AEVK {

	public:

		static bool CreateVKInstance(vk::Instance& Instance, const char* Name = "AEVK");

		static std::vector<const char*> GetRequiredExtensions();


	};

}

#ifndef AE_NO_IMPL
	#include "AEVK.inl"
#endif