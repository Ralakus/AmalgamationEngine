#pragma once

#include "Component.hpp"

namespace Amalgamation {

	class ISystem {
	protected:
		std::vector<uint32> m_ComponentTypes;
	public:

		ISystem(const std::vector<uint32>& ComponentTypes) : m_ComponentTypes(ComponentTypes) {}

		virtual void UpdateComponents(float Delta, IComponent** Components) {}

		const std::vector<uint32>& GetComponentTypes() const { return m_ComponentTypes; }
	};

}

#include "System.inl"