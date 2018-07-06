#pragma once

#include <Core/Graphics/GLFWWindow.hpp>
#include "VKInstance.hpp"
#include "VKDevice.hpp"

namespace Amalgamation {

    class VKWindow : public GLFWWindow {

	public:

		 VKWindow();
		~VKWindow();

    };

}

#if !defined(AE_NO_IMPL)
    #include "VKWindow.inl"
#endif