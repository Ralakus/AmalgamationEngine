
#include "GLRenderingSystem.hpp"

namespace Amalgamation {

	GLRenderingSystem::GLRenderingSystem()
		: ISystem({ TransformComponent::ID, MeshComponent::ID })
	{}

	FORCEINLINE GLRenderingSystem::~GLRenderingSystem() {}

}