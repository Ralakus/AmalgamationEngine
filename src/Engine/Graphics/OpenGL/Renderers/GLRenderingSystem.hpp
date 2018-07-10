#pragma once

#include <Core/Scene/System.hpp>
#include <Engine/Scene/TransformComponent.hpp>
#include <Engine/Scene/MeshComponent.hpp>

namespace Amalgamation {

	class GLRenderingSystem : public ISystem {

	public:

		 GLRenderingSystem();
		~GLRenderingSystem();

	};

}

#include "GLRenderingSystem.inl"